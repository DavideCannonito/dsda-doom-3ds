#include "i_scanwad.h"
#include "lprintf.h"
#include <3ds.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Function modified by Gemini for the correct printing logic
void I_ScanWADFiles(const char *path, int *argc, char **argv) {
  const char blacklistednames[3][15] = {".", "..", "dsda-doom.wad"};
  char **foundwads = malloc(ARG_MAX * sizeof(char *));
  uint8_t foundwadscount = 0;
  uint8_t userchoice = 0;
  struct dirent *entry = NULL;
  DIR *dp = opendir(path);

  if (dp == NULL) {
    I_Error("Cannot open the folder %s", path);
  }
  if (foundwads == NULL) {
    I_Error("Memory allocation failed");
  }

  // Clear the pointer array
  memset(foundwads, 0, ARG_MAX * sizeof(char *));

  while ((entry = readdir(dp)) != NULL) {
    bool isblacklisted = false;
    for (uint8_t i = 0; i < 3; i++) {
      if (strcmp(entry->d_name, blacklistednames[i]) == 0) {
        isblacklisted = true;
        break;
      }
    }

    if (!isblacklisted && strcasestr(entry->d_name, ".wad")) {
      asprintf(&foundwads[foundwadscount], "%s%s", path, entry->d_name);
      foundwadscount++;
    }
  }
  closedir(dp);

  if (foundwadscount == 0) {
    I_Error("No IWADs for this folder");
  }

  // FIX 1: Clear screen and Draw the initial list correctly
  lprintf(LO_INFO, "\x1b[2J"); // Clear screen
  for (uint8_t i = 0; i < foundwadscount; i++) {
    lprintf(LO_INFO, "\x1b[%d;1H", i + 1); // Move to Row (i+1), Col 1
    if (i == userchoice) {
      lprintf(LO_INFO, "\x1b[7m%s\x1b[27m", foundwads[i]); // Highlight
    } else {
      lprintf(LO_INFO, "%s", foundwads[i]);
    }
  }

  while (aptMainLoop()) {
    hidScanInput();
    u32 kDown = hidKeysDown();

    if (kDown & KEY_DDOWN) {
      if (userchoice + 1 < foundwadscount) {
        // Remove highlight from old choice
        lprintf(LO_INFO, "\x1b[%d;1H\x1b[27m%s", userchoice + 1,
                foundwads[userchoice]);
        userchoice++;
        // Add highlight to new choice
        lprintf(LO_INFO, "\x1b[%d;1H\x1b[7m%s\x1b[27m", userchoice + 1,
                foundwads[userchoice]);
      }
    }

    if (kDown & KEY_DUP) {
      if (userchoice > 0) {
        // Remove highlight from old choice
        lprintf(LO_INFO, "\x1b[%d;1H\x1b[27m%s", userchoice + 1,
                foundwads[userchoice]);
        userchoice--;
        // Add highlight to new choice
        lprintf(LO_INFO, "\x1b[%d;1H\x1b[7m%s\x1b[27m", userchoice + 1,
                foundwads[userchoice]);
      }
    }

    if (kDown & KEY_A) {
      // Azahar sets argc to 0, whereas Homebrew Launcher sets to 1, with 0
      // being the path to the game. Hopefully this is safe (aka won't bite me back)
      argv[0] = strdup("-iwad");
      argv[1] = strdup(foundwads[userchoice]);
      *argc += 2;
      break;
    }
  }

  // Clean up
  for (uint8_t i = 0; i < foundwadscount; i++) {
    free(foundwads[i]);
  }
  free(foundwads);
}