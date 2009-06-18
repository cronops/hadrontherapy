# $Id: GNUmakefile,v 1.6 2008/06/15 17:28:20 cirrone Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := Hadrontherapy
G4TARGET := $(name)
G4EXLIB := true

ifdef G4ROOTANALYSIS_USE
G4ANALYSIS_USE=0
endif

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/architecture.gmk

ifdef G4ANALYSIS_USE
CPPFLAGS += -DANALYSIS_USE
endif
ifdef G4ROOTANALYSIS_USE
CPPFLAGS += -DANALYSIS_USE -DG4ROOTANALYSIS_USE
CPPFLAGS += $(shell root-config --cflags)
LDFLAGS  += $(shell root-config --glibs)
endif

include $(G4INSTALL)/config/binmake.gmk

ifdef G4ANALYSIS_USE 
endif
