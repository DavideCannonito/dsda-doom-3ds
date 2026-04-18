#ifndef SDLMIXERPLAYER_H
#define SDLMIXERPLAYER_H

#include "musicplayer.h"
#include <SDL/SDL_mixer.h>
extern const music_player_t sdl_mixer_player;

typedef struct sm_player_state{
    SDL_RWops* data_rw;
    void* raw_data;
    size_t outbuf_len;


    Mix_Music* music_handle;
}sm_player_state;



// descriptive name of the player, such as "OPL2 Synth"
const char *sm_name(void);
// samplerate is in hz.  return is 1 for success
int sm_init(int samplerate);

// deallocate structures, cleanup, ...
void sm_shutdown(void);

// set volume, 0 = off, 15 = max
void sm_setvolume(int v);

// pause currently running song.
void sm_pause(void);

// undo pause
void sm_resume(void);

// return a player-specific handle, or NULL on failure.
// data does not belong to player, but it will persist as long as unregister is not called
const void *sm_registersong(const void *data, unsigned len);

// deallocate structures, etc.  data is no longer valid
void sm_unregistersong(const void *handle);

void sm_play(const void *handle, int looping);

// stop
void sm_stop(void);

// s16 stereo, with samplerate as specified in init.  player needs to be able to handle
// just about anything for nsamp.  render can be called even during pause+stop.
void sm_render(void *dest, unsigned nsamp);

#endif
