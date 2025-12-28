# FILE CORRECTED BY ~CHATGPT~ *buzzer* ~CLAUDE~ *buzzer* ~DEEPSEEK~ *buzzer* by *GEMINI*
# BY SENDING THE FULL `Makefile.old` FILE (and going back and forth for at less than 10 msgs).
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
# TARGET E DIRECTORY
#---------------------------------------------------------------------------------
TARGET      :=  $(notdir $(CURDIR))
BUILD       :=  build
SOURCES     := source source/dsda source/heretic source/hexen source/MUSIC source/SDL source/STUBS source/NINTENDO_3DS
SOURCES     += source/dsda/gl source/dsda/hud_components source/dsda/mapinfo source/dsda/mapinfo/doom source/dsda/doom source/dsda/utility 

INCLUDES    :=  $(SOURCES)
GRAPHICS    :=  gfx
ROMFS       :=  romfs
GFXBUILD    :=  $(ROMFS)/gfx

#---------------------------------------------------------------------------------
# OPZIONI DI GENERAZIONE CODICE
#---------------------------------------------------------------------------------
ARCH    :=  -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft -mword-relocations

CFLAGS  :=  -g -Wall -O0 \
            -ffunction-sections \
            $(ARCH)

CFLAGS  +=  $(INCLUDE) -D__3DS__ -DHAVE_CONFIG_H -D_GNU_SOURCE -std=c99

CXXFLAGS    := $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11

ASFLAGS :=  -g $(ARCH)
LDFLAGS =   -specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

LIBS    := -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2 -lpng -ljpeg -lz -lopusfile
LIBS    += -lopus -logg -lvorbisidec -logg -lFLAC -lmodplug -lxmp -lmad -lmpg123 -lpicaGL -lcitro2d -lcitro3d -lctru -lm

LIBDIRS := $(CTRULIB) $(PORTLIBS)

#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT   :=  $(CURDIR)/$(TARGET)
export TOPDIR   :=  $(CURDIR)
export DEPSDIR  :=  $(CURDIR)/$(BUILD)

CFILES      :=  $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
CPPFILES    :=  $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.cpp))
SFILES      :=  $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.s))
PICAFILES   :=  $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.v.pica))
SHLISTFILES :=  $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.shlist))
GFXFILES    :=  $(foreach dir,$(GRAPHICS),$(wildcard $(dir)/*.t3s))
BINFILES    :=  $(foreach dir,$(DATA),$(wildcard $(dir)/*.*))

ifeq ($(strip $(CPPFILES)),)
    export LD   :=  $(CC)
else
    export LD   :=  $(CXX)
endif

ifeq ($(GFXBUILD),$(BUILD))
export T3XFILES :=  $(GFXFILES:.t3s=.t3x)
else
export ROMFS_T3XFILES   :=  $(patsubst %.t3s, $(GFXBUILD)/%.t3x, $(GFXFILES))
export T3XHFILES        :=  $(patsubst %.t3s, $(BUILD)/%.h, $(GFXFILES))
endif

export OFILES_SOURCES   :=  $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export OFILES_BIN   :=  $(addsuffix .o,$(BINFILES)) \
            $(PICAFILES:.v.pica=.shbin.o) $(SHLISTFILES:.shlist=.shbin.o) \
            $(addsuffix .o,$(T3XFILES))

export OFILES := $(OFILES_BIN) $(OFILES_SOURCES)

export HFILES   :=  $(PICAFILES:.v.pica=_shbin.h) $(SHLISTFILES:.shlist=_shbin.h) \
            $(addsuffix .h,$(subst .,_,$(BINFILES))) \
            $(GFXFILES:.t3s=.h)

export INCLUDE  :=  $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
            $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
            -I$(CURDIR)/$(BUILD)

export LIBPATHS :=  $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

export _3DSXDEPS    :=  $(if $(NO_SMDH),,$(OUTPUT).smdh)

ifeq ($(strip $(ICON)),)
    icons := $(wildcard *.png)
    ifneq (,$(findstring $(TARGET).png,$(icons)))
        export APP_ICON := $(TOPDIR)/$(TARGET).png
    else
        ifneq (,$(findstring icon.png,$(icons)))
            export APP_ICON := $(TOPDIR)/icon.png
        endif
    endif
else
    export APP_ICON := $(TOPDIR)/$(ICON)
endif

ifeq ($(strip $(NO_SMDH)),)
    export _3DSXFLAGS += --smdh=$(CURDIR)/$(TARGET).smdh
endif

ifneq ($(ROMFS),)
    export _3DSXFLAGS += --romfs=$(CURDIR)/$(ROMFS)
endif

.PHONY: all clean

# Rimosso $(BUILD) dalle dipendenze per evitare il loop circolare
all: $(GFXBUILD) $(ROMFS_T3XFILES) $(T3XHFILES)
	@[ -d $(BUILD) ] || mkdir -p $(BUILD)
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

ifneq ($(GFXBUILD),$(BUILD))
$(GFXBUILD):
	@mkdir -p $@
endif

clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).3dsx $(TARGET).smdh $(TARGET).elf $(GFXBUILD)

$(GFXBUILD)/%.t3x   $(BUILD)/%.h    :   %.t3s
	@echo $(notdir $<)
	@mkdir -p $(dir $@)
	@tex3ds -i $< -H $(BUILD)/$*.h -d $(DEPSDIR)/$*.d -o $(GFXBUILD)/$*.t3x

#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------

VPATH := $(TOPDIR)

$(OUTPUT).3dsx  :   $(OUTPUT).elf $(_3DSXDEPS)

$(OFILES_SOURCES) : $(HFILES)

$(OUTPUT).elf   :   $(OFILES)

%.o: %.c
	@echo "$<"
	@mkdir -p $(dir $@)
	@$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(CFLAGS) -c $< -o $@

%.o: %.cpp
	@echo "$<"
	@mkdir -p $(dir $@)
	@$(CXX) -MMD -MP -MF $(DEPSDIR)/$*.d $(CXXFLAGS) -c $< -o $@

%.o: %.s
	@echo "$<"
	@mkdir -p $(dir $@)
	@$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(ASFLAGS) -c $< -o $@

%.bin.o %_bin.h : %.bin
	@echo $(notdir $<)
	@mkdir -p $(dir $@)
	@$(bin2o)

.PRECIOUS   :   %.t3x %.shbin

%.t3x.o %_t3x.h : %.t3x
	@echo $(notdir $<)
	@mkdir -p $(dir $@)
	@$(bin2o)

%.shbin.o %_shbin.h : %.shbin
	@echo $(notdir $<)
	@mkdir -p $(dir $@)
	@$(bin2o)

-include $(OFILES:.o=.d)

endif