# this file belongs to `bitify` http://github.com/amery/bitify
#
# Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
# All rights reserved. See COPYING for details.

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

$(ALIASES): $(APP)
	ln -s $^ $@

install:
	@mkdir -p $(DESTDIR)$(BINDIR)/
	@cp -v $(TARGETS) $(DESTDIR)$(BINDIR)/

clean:
	@rm -vf $(TARGETS) *.o *~
