CC = gcc

CFLAGS = -W -Wall -std=c99
CFLAGS += -O2

APP = bitify
ALIASES = unbitify

TARGETS = $(APP) $(ALIASES)

.PHONY: all clean

all: $(TARGETS)

$(ALIASES):
	ln -snf $(APP) $@

clean:
	@rm -vf $(TARGETS) *.o *~
