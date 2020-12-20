#
# Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#
default: prune

ifeq (0${V},0)
Q := @
else
Q :=
endif

CFLAGS += -W -Wall -Wextra -Wno-switch -Wno-unused-parameter -std=gnu1x

# Glib. The user is expected to have already set CFLAGS to contain any
# LLVM-required stuff.
CFLAGS += $(shell pkg-config --cflags --libs glib-2.0)

prune: cfg.o dict.o main.o set.o
	@echo " [LD] $@"
	${Q}${CC} -o $@ $^ ${CFLAGS} -lclang

cfg.o: dict.h
dict.o: dict.h
main.o: set.h
set.o: set.h

%.o: %.c
	@echo " [CC] $@"
	${Q}${CC} ${CFLAGS} -c -o $@ $<

clean:
	@echo " [CLEAN] prune *.o"
	${Q}rm -f prune *.o
