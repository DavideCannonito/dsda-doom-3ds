//
// Copyright(C) 2022 by Ryan Krafnick
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	DSDA Game Controller
//

#include <SDL/SDL.h>

#include "d_event.h"
#include "d_main.h"
#include "lprintf.h"

#include "dsda/args.h"
#include "dsda/configuration.h"

#include "game_controller.h"

static int use_game_controller;
static SDL_Joystick *game_controller;

typedef enum N3DSAxis {
  STICK_LEFTX = 0,
  STICK_LEFTY = 1,
  CSTICK_X = 2,
  CSTICK_Y = 3
} N3DSAxis;

typedef struct {
  N3DSAxis axis;
  int deadzone;
  int sensitivity;
} axis_t;

static axis_t left_analog_x = {STICK_LEFTX};
static axis_t left_analog_y = {STICK_LEFTY};
static axis_t right_analog_x = {CSTICK_X};
static axis_t right_analog_y = {CSTICK_Y};

static int swap_analogs;

static const char *button_names[] = {
    [DSDA_CONTROLLER_BUTTON_A] = "A",
    [DSDA_CONTROLLER_BUTTON_B] = "B",
    [DSDA_CONTROLLER_BUTTON_X] = "X",
    [DSDA_CONTROLLER_BUTTON_Y] = "Y",
    [DSDA_CONTROLLER_BUTTON_BACK] = "SELECT",
    [DSDA_CONTROLLER_BUTTON_START] = "START",
    [DSDA_CONTROLLER_BUTTON_LEFTSHOULDER] = "L",
    [DSDA_CONTROLLER_BUTTON_RIGHTSHOULDER] = "R",
    [DSDA_CONTROLLER_BUTTON_DPAD_UP] = "DPAD UP",
    [DSDA_CONTROLLER_BUTTON_DPAD_DOWN] = "DPAD DOWN",
    [DSDA_CONTROLLER_BUTTON_DPAD_LEFT] = "DPAD LEFT",
    [DSDA_CONTROLLER_BUTTON_DPAD_RIGHT] = "DPAD RIGHT",
    [DSDA_CONTROLLER_BUTTON_TRIGGERLEFT] = "ZL",
    [DSDA_CONTROLLER_BUTTON_TRIGGERRIGHT] = "ZR",
};

const char *dsda_GameControllerButtonName(int button) {
  if (button >= sizeof(button_names) || !button_names[button])
    return "misc";

  return button_names[button];
}

static float dsda_AxisValue(axis_t *axis) {
  Sint16 value;

  value = SDL_JoystickGetAxis(game_controller, axis->axis);

  // the positive axis max is 1 less
  if (value > (axis->deadzone - 1))
    value -= (axis->deadzone - 1);
  else if (value < -axis->deadzone)
    value += axis->deadzone;
  else
    value = 0;

  return (float)value * axis->sensitivity / (32768 - axis->deadzone);
}

static void dsda_PollLeftStick(void) {
  event_t ev;

  ev.type = swap_analogs ? ev_look_analog : ev_move_analog;
  ev.data1.f = dsda_AxisValue(&left_analog_x);
  ev.data2.f = -dsda_AxisValue(&left_analog_y);

  if (ev.data1.f || ev.data2.f)
    D_PostEvent(&ev);
}

static void dsda_PollRightStick(void) {
  event_t ev;

  ev.type = swap_analogs ? ev_move_analog : ev_look_analog;
  ev.data1.f = dsda_AxisValue(&right_analog_x);
  ev.data2.f = -dsda_AxisValue(&right_analog_y);

  if (ev.data1.f || ev.data2.f)
    D_PostEvent(&ev);
}

static inline int PollButton(dsda_game_controller_button_t button) {
  if (button >= DSDA_CONTROLLER_BUTTON_DPAD_UP &&
      button <= DSDA_CONTROLLER_BUTTON_DPAD_LEFT) {
    // this is because the DPAD numbers are shifted by 10 to not clash with
    // other buttons
Uint8 hatState = SDL_JoystickGetHat(game_controller, 0);
    int pressed = 0;

    // Check the specific direction bit
    if (button == DSDA_CONTROLLER_BUTTON_DPAD_UP)    pressed = (hatState & SDL_HAT_UP);
    if (button == DSDA_CONTROLLER_BUTTON_DPAD_DOWN)  pressed = (hatState & SDL_HAT_DOWN);
    if (button == DSDA_CONTROLLER_BUTTON_DPAD_LEFT)  pressed = (hatState & SDL_HAT_LEFT);
    if (button == DSDA_CONTROLLER_BUTTON_DPAD_RIGHT) pressed = (hatState & SDL_HAT_RIGHT);

    // Return a clean 1 or 0 shifted to the correct bit position
    return (pressed ? 1 : 0) << button;
  }
  // This depends on enums having same values
  return SDL_JoystickGetButton(game_controller, button) << button;
}
/* TODO:
  - [X] Read how it works and how are inputs processed
  - [X] See how to remap controls - LOOK m_misc.c:388
  - [X] Create a control scheme for O3DS - LOOK m_misc.c:388
*/
void dsda_PollGameControllerButtons(void) {
  event_t ev;
  float trigger;

  if (!game_controller)
    return;

  ev.type = ev_joystick;
  ev.data1.i = PollButton(DSDA_CONTROLLER_BUTTON_A) |
               PollButton(DSDA_CONTROLLER_BUTTON_B) |
               PollButton(DSDA_CONTROLLER_BUTTON_X) |
               PollButton(DSDA_CONTROLLER_BUTTON_Y) |
               PollButton(DSDA_CONTROLLER_BUTTON_BACK) |
               PollButton(DSDA_CONTROLLER_BUTTON_START) |
               PollButton(DSDA_CONTROLLER_BUTTON_LEFTSHOULDER) |
               PollButton(DSDA_CONTROLLER_BUTTON_RIGHTSHOULDER) |
               PollButton(DSDA_CONTROLLER_BUTTON_TRIGGERLEFT) |
               PollButton(DSDA_CONTROLLER_BUTTON_TRIGGERRIGHT) |
               PollButton(DSDA_CONTROLLER_BUTTON_DPAD_UP) |
               PollButton(DSDA_CONTROLLER_BUTTON_DPAD_DOWN) |
               PollButton(DSDA_CONTROLLER_BUTTON_DPAD_LEFT) |
               PollButton(DSDA_CONTROLLER_BUTTON_DPAD_RIGHT);

  D_PostEvent(&ev);
}

void dsda_PollGameController(void) {
  if (!game_controller)
    return;

  dsda_PollGameControllerButtons();
  dsda_PollLeftStick();
  dsda_PollRightStick();
}

void dsda_InitGameControllerParameters(void) {
  left_analog_x.deadzone = dsda_IntConfig(dsda_config_left_analog_deadzone);
  left_analog_x.sensitivity =
      dsda_IntConfig(dsda_config_left_analog_sensitivity_x);
  left_analog_y.deadzone = left_analog_x.deadzone;
  left_analog_y.sensitivity =
      dsda_IntConfig(dsda_config_left_analog_sensitivity_y);

  right_analog_x.deadzone = dsda_IntConfig(dsda_config_right_analog_deadzone);
  right_analog_x.sensitivity =
      dsda_IntConfig(dsda_config_right_analog_sensitivity_x);
  right_analog_y.deadzone = right_analog_x.deadzone;
  right_analog_y.sensitivity =
      dsda_IntConfig(dsda_config_right_analog_sensitivity_y);

  swap_analogs = dsda_IntConfig(dsda_config_swap_analogs);
}

void dsda_InitGameController(void) {
  int num_joysticks;

  game_controller = NULL;
  use_game_controller = true;

  if (!use_game_controller)
    return;

  dsda_InitGameControllerParameters();
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);

  num_joysticks = SDL_NumJoysticks();

  if (use_game_controller > num_joysticks) {
    lprintf(LO_WARN, "dsda_InitGameController: invalid joystick %d\n",
            use_game_controller);
    return;
  }

  game_controller = SDL_JoystickOpen(use_game_controller - 1);

  if (!game_controller) {
    lprintf(LO_ERROR,
            "dsda_InitGameController: error opening game controller %d\n",
            use_game_controller);
    return;
  }

  

  lprintf(LO_DEBUG, "Opened game controller %s\n",
          SDL_JoystickName(SDL_JoystickIndex(game_controller)));
}
