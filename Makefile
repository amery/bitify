CC = gcc

CFLAGS = -W -Wall -std=c99
CFLAGS += -O2

APP = bitify
ALIASES = unbitify

TARGETS = $(APP) $(ALIASES)

DESTDIR =
PREFIX  = /usr/local
BINDIR  = $(PREFIX)/bin

.PHONY: all clean install

all: $(TARGETS)

$(ALIASES):
	ln -snf $(APP) $@

install:
	@mkdir -p $(DESTDIR)$(BINDIR)/
	@cp -v $(TARGETS) $(DESTDIR)$(BINDIR)/

clean:
	@rm -vf $(TARGETS) *.o *~
