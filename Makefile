# FILE CORRECTED BY CHATGPT BY SENDING THE FULL `Makefile.old` FILE.
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
MAKEFLAGS := --jobs=$(shell nproc)

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITARM)/3ds_rules
#---------------------------------------------------------------------------------
TARGET      := $(notdir $(CURDIR))
BUILD       := build
SOURCES     := source source/dsda source/heretic source/hexen source/MUSIC source/SDL source/STUBS
SOURCES 	+= source/dsda/gl source/dsda/hud_components source/dsda/mapinfo source/dsda/mapinfo/doom source/dsda/doom source/dsda/utility 
INCLUDES    := $(SOURCES)
GRAPHICS    := gfx
ROMFS       := romfs
GFXBUILD    := $(ROMFS)/gfx
#---------------------------------------------------------------------------------

ARCH    := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft -mword-relocations

CFLAGS  := -g -Wall -O0 -ffunction-sections $(ARCH)
CFLAGS  += $(INCLUDE) -D__3DS__ -DHAVE_CONFIG_H -D_GNU_SOURCE -std=c99
CXXFLAGS:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11
ASFLAGS := -g $(ARCH)
LDFLAGS := -specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)
LIBS	:= -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2 -lpng -ljpeg -lz -lopusfile
LIBS	+= -lopus -logg -lvorbisidec -logg -lFLAC -lmodplug -lxmp -lmad -lmpg123 -lpicaGL -lcitro2d -lcitro3d -lctru -lm


LIBDIRS := $(CTRULIB) $(PORTLIBS)

#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT  := $(CURDIR)/$(TARGET)
export TOPDIR  := $(CURDIR)

export DEPSDIR := $(CURDIR)/$(BUILD)

# --- FIX: keep paths, do NOT use notdir (prevents double compilation) ---
CFILES      := $(foreach d,$(SOURCES),$(wildcard $(d)/*.c))
CPPFILES    := $(foreach d,$(SOURCES),$(wildcard $(d)/*.cpp))
SFILES      := $(foreach d,$(SOURCES),$(wildcard $(d)/*.s))
PICAFILES   := $(foreach d,$(SOURCES),$(wildcard $(d)/*.v.pica))
SHLISTFILES := $(foreach d,$(SOURCES),$(wildcard $(d)/*.shlist))
GFXFILES    := $(foreach d,$(GRAPHICS),$(wildcard $(d)/*.t3s))

export VPATH := $(CURDIR)

ifeq ($(strip $(CPPFILES)),)
export LD := $(CC)
else
export LD := $(CXX)
endif

export OFILES_SOURCES := \
	$(CFILES:%.c=$(BUILD)/%.o) \
	$(CPPFILES:%.cpp=$(BUILD)/%.o) \
	$(SFILES:%.s=$(BUILD)/%.o)

ifeq ($(GFXBUILD),$(BUILD))
export T3XFILES := $(GFXFILES:.t3s=.t3x)
else
export ROMFS_T3XFILES := $(GFXFILES:%.t3s=$(GFXBUILD)/%.t3x)
export T3XHFILES      := $(GFXFILES:%.t3s=$(BUILD)/%.h)
endif

export OFILES := $(OFILES_SOURCES) $(addsuffix .o,$(T3XFILES))

export INCLUDE := \
	$(foreach d,$(INCLUDES),-I$(CURDIR)/$(d)) \
	$(foreach d,$(LIBDIRS),-I$(d)/include) \
	-I$(CURDIR)/$(BUILD)

export LIBPATHS := $(foreach d,$(LIBDIRS),-L$(d)/lib)

export _3DSXDEPS := $(if $(NO_SMDH),,$(OUTPUT).smdh)

.PHONY: all clean

all: $(BUILD) $(GFXBUILD)
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

$(BUILD):
	@mkdir -p $@

$(GFXBUILD):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD) $(TARGET).3dsx $(OUTPUT).smdh $(TARGET).elf $(GFXBUILD)

#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------

$(OUTPUT).3dsx : $(OUTPUT).elf $(_3DSXDEPS)

$(OUTPUT).elf : $(OFILES)

$(BUILD)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD)/%.o : %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD)/%.o : %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

$(GFXBUILD)/%.t3x $(BUILD)/%.h : %.t3s
	@mkdir -p $(dir $(GFXBUILD)/$*)
	@mkdir -p $(dir $(BUILD)/$*)
	tex3ds -i $< -H $(BUILD)/$*.h -o $(GFXBUILD)/$*.t3x

-include $(DEPSDIR)/**/*.d

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
