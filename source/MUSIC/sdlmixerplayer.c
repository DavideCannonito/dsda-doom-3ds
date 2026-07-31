#include "MUSIC/sdlmixerplayer.h"
#include "musicplayer.h"
#include <SDL/SDL_mixer.h>

const music_player_t sdl_mixer_player = {
    sm_name,  sm_init,   sm_shutdown,     sm_setvolume,
    sm_pause, sm_resume, sm_registersong, sm_unregistersong,
    sm_play,  sm_stop,   sm_render};

static sm_player_state player_state = {0};

// descriptive name of the player, such as "OPL2 Synth"
const char *sm_name(void) { return "SDL_Mixer 1.2.15-9 devkitpro"; }

// samplerate is in hz.  return is 1 for success
int sm_init(int samplerate) {
  // the Mix subsystem is inited already in i_sound.c:896 i'll return if it was
  // inited already this function will return 0 if the audio device wasn't
  // opened for any reason, even though it's already taken care of
  return Mix_QuerySpec(NULL, NULL, NULL);
}

// deallocate structures, cleanup, ...
void sm_shutdown(void) {
  sm_stop();
  sm_unregistersong(player_state.music_handle);
}

// set volume, 0 = off, 15 = max
void sm_setvolume(int v) {
  int converted_vol = 0;
  const uint8_t mix_upperbound = 128;
  const uint8_t doom_upperbound = 15;

  // conversion formula `15:15=x:128` but truncated
  converted_vol = (v * mix_upperbound) / doom_upperbound;

  // Mix_VolumeMusic has a range from 0-128, whereas dsda-doom has 0-15.
  Mix_VolumeMusic(converted_vol);
}

// pause currently running song.
void sm_pause(void) { Mix_PauseMusic(); }

// undo pause
void sm_resume(void) { Mix_ResumeMusic(); }

// return a player-specific handle, or NULL on failure.
// data does not belong to player, but it will persist as long as unregister is
// not called
// edit all your base are belong to us
const void *sm_registersong(const void *data, unsigned len) {
  int looping = 1;
  SDL_RWops *music = SDL_RWFromMem(data, len);
  player_state.data_rw = music;
  player_state.outbuf_len = len;
  player_state.music_handle = Mix_LoadMUS_RW(music);

  return player_state.music_handle;
}

// deallocate structures, etc.  data is no longer valid
void sm_unregistersong(const void *handle) {
  sm_stop();
  Mix_FreeMusic(handle);

  player_state.music_handle = NULL;
  player_state.data_rw = NULL;
  player_state.outbuf_len = 0;
}

void sm_play(const void *handle, int looping) {
  Mix_PlayMusic(player_state.music_handle, looping?-1:0);
}

// stop
void sm_stop(void) { Mix_HaltMusic(); }

// s16 stereo, with samplerate as specified in init.  player needs to be able to
// handle just about anything for nsamp.  render can be called even during
// pause+stop.
void sm_render(void *dest, unsigned nsamp) {}