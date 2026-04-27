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

#ifndef __DSDA_GAME_CONTROLLER__
#define __DSDA_GAME_CONTROLLER__

// Must match SDL
typedef enum {
  DSDA_CONTROLLER_BUTTON_A=1,
  DSDA_CONTROLLER_BUTTON_B=2,
  DSDA_CONTROLLER_BUTTON_X=3,
  DSDA_CONTROLLER_BUTTON_Y=4,
  DSDA_CONTROLLER_BUTTON_BACK=7,
  DSDA_CONTROLLER_BUTTON_START=0,
  DSDA_CONTROLLER_BUTTON_LEFTSHOULDER=5,
  DSDA_CONTROLLER_BUTTON_RIGHTSHOULDER=6,
  DSDA_CONTROLLER_BUTTON_DPAD_UP=11,
  DSDA_CONTROLLER_BUTTON_DPAD_DOWN=14,
  DSDA_CONTROLLER_BUTTON_DPAD_LEFT=18,
  DSDA_CONTROLLER_BUTTON_DPAD_RIGHT=12,
  DSDA_CONTROLLER_BUTTON_TRIGGERLEFT=8,
  DSDA_CONTROLLER_BUTTON_TRIGGERRIGHT=9,
} dsda_game_controller_button_t;

const char* dsda_GameControllerButtonName(int button);
void dsda_PollGameController(void);
void dsda_PollGameControllerButtons(void);
void dsda_InitGameController(void);

#endif
