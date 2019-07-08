TOPDIR  := ./
SRCDIR  := $(TOPDIR)BP/
OBJDIR  := $(TOPDIR)obj/
BINDIR  := $(TOPDIR)bin/
NAME    := bp
EXE     := $(BINDIR)$(NAME)

SFILES  := cpp
OFILES  := o
CC      := g++
CFLAGS  := -c -Wall -IBP -std=gnu++11 -pedantic -g

SOURCES := $(shell find $(SRCDIR) -name "*.$(SFILES)")
OBJECTS := $(patsubst $(SRCDIR)%.$(SFILES), $(OBJDIR)%.$(OFILES), $(SOURCES))

ALLFILES := $(SOURCES)

.PHONY: all clean

all:    $(EXE)

$(EXE): $(OBJECTS)
	@$(CC) $^ -o $@

$(OBJDIR)%$(OFILES):    $(SRCDIR)%$(SFILES)
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(OBJECTS) $(EXE)
