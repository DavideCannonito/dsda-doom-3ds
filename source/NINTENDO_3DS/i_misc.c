#include "lprintf.h"
#include <3ds.h>
void I_GoSpinningLoop(void) {
  lprintf(LO_INFO, "Press START+SELECT to quit...\n");

  // TODO: Hook the inputs to DOOM's one, if possible? (ig the input subsystem
  // shuts down?)
  while (aptMainLoop()) {
    hidScanInput();

    u32 kDown = hidKeysDown();
    u32 kHeld = hidKeysHeld();

    if (kDown & KEY_START && kDown & KEY_SELECT) {
      return;
    }
  }
}