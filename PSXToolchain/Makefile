PSYQ_DIR 	?= X:/PsyQ
NPSYQ_DIR 	?= X:/NPsyQ

OBJDIR		= obj
BINDIR 		?= CDSrc/0_CD_DATA/
TARGET      = DRIVER2
TYPE        = ps-exe
BUILD       = Release

SOURCES = GameSRC/Game

OVERLAYSCRIPT  ?= redriver2_overlays.ld
OVERLAYSECTION ?= .frnt .path .lead

# Main sources
SRCS = \
  $(SOURCES)/ASM/asmtest.c\
  $(SOURCES)/ASM/compres.c\
  $(SOURCES)/ASM/d2mapasm.c\
  $(SOURCES)/ASM/rnc_2.c\
  $(SOURCES)/ASM/rndrasm.c\
  $(SOURCES)/C/E3stuff.c\
  $(SOURCES)/C/ai.c\
  $(SOURCES)/C/bcoll3d.c\
  $(SOURCES)/C/bcollide.c\
  $(SOURCES)/C/bomberman.c\
  $(SOURCES)/C/camera.c\
  $(SOURCES)/C/cars.c\
  $(SOURCES)/C/cell.c\
  $(SOURCES)/C/civ_ai.c\
  $(SOURCES)/C/convert.c\
  $(SOURCES)/C/cop_ai.c\
  $(SOURCES)/C/cosmetic.c\
  $(SOURCES)/C/cutscene.c\
  $(SOURCES)/C/debris.c\
  $(SOURCES)/C/denting.c\
  $(SOURCES)/C/director.c\
  $(SOURCES)/C/dr2roads.c\
  $(SOURCES)/C/draw.c\
  $(SOURCES)/C/drivinggames.c\
  $(SOURCES)/C/envsound.c\
  $(SOURCES)/C/event.c\
  $(SOURCES)/C/felony.c\
  $(SOURCES)/C/fmvplay.c\
  $(SOURCES)/C/gamesnd.c\
  $(SOURCES)/C/glaunch.c\
  $(SOURCES)/C/handling.c\
  $(SOURCES)/C/job_fx.c\
  $(SOURCES)/C/loadsave.c\
  $(SOURCES)/C/loadview.c\
  $(SOURCES)/C/main.c\
  $(SOURCES)/C/map.c\
  $(SOURCES)/C/mc_snd.c\
  $(SOURCES)/C/mdraw.c\
  $(SOURCES)/C/mgeneric.c\
  $(SOURCES)/C/mission.c\
  $(SOURCES)/C/models.c\
  $(SOURCES)/C/motion_c.c\
  $(SOURCES)/C/objanim.c\
  $(SOURCES)/C/objcoll.c\
  $(SOURCES)/C/overlay.c\
  $(SOURCES)/C/overmap.c\
  $(SOURCES)/C/pad.c\
  $(SOURCES)/C/pause.c\
  $(SOURCES)/C/pedest.c\
  $(SOURCES)/C/players.c\
  $(SOURCES)/C/pres.c\
  $(SOURCES)/C/replays.c\
  $(SOURCES)/C/roadbits.c\
  $(SOURCES)/C/scores.c\
  $(SOURCES)/C/search.c\
  $(SOURCES)/C/shadow.c\
  $(SOURCES)/C/sky.c\
  $(SOURCES)/C/sound.c\
  $(SOURCES)/C/spool.c\
  $(SOURCES)/C/state.c\
  $(SOURCES)/C/system.c\
  $(SOURCES)/C/targets.c\
  $(SOURCES)/C/texture.c\
  $(SOURCES)/C/tile.c\
  $(SOURCES)/C/time.c\
  $(SOURCES)/C/sysclock.c\
  $(SOURCES)/C/wheelforces.c\
  $(SOURCES)/C/xaplay.c\
  $(SOURCES)/C/xmplay.c

# overlay sources
SRCS += \
  $(SOURCES)/Frontend/FEmain.c\
  $(SOURCES)/C/pathfind.c\
  $(SOURCES)/C/leadai.c

SRCS += $(PSYQ_DIR)/common/crt0/crt0.s
INCL = $(SOURCES) $(PSYQ_DIR)/include $(PSYQ_DIR)/include/sys $(NPSYQ_DIR)/include

DEFS = PSX NTSC_VERSION RELOC DEBUG_OPTIONS

NOWARNS = write-strings narrowing

CPPFLAGS += -x c++ -fno-threadsafe-statics $(addprefix -D,$(DEFS)) $(addprefix -I,$(INCL)) $(addprefix -Wno-,$(NOWARNS))

# Psy-Q libraries
LIBS = api c card etc gpu gte math mcrd pad snd spu cd

LDFLAGS += -L$(PSYQ_DIR)/lib
LDFLAGS += -Wl,--start-group
LDFLAGS += $(addprefix -l,$(LIBS))
LDFLAGS += -Wl,--end-group

include NPsyQ/common.mk