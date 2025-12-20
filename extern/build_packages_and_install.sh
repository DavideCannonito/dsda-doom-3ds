#!/bin/bash

# READ THIS: THIS SCRIPT WILL *AUTOMATICALLY* INSTALL THE PACKAGES.
# Thanks to Kistelini for providing PKGBUILDs and accelerated rendering!. Not sure if i'll use it in my case, but better have it than not :) 
# Check it out here: https://github.com/Kistelini/devkitpro-packages/tree/3ds-sdl2/3ds

sources=("SDL2" "SDL2_gfx" "SDL2_image" "SDL2_mixer" "SDL2_ttf")

for source in ${sources[@]};
do
    cd sdl2-sources/$source/
    makepkg -si --noconfirm
    cd ../../
done