/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

/* Implementation of a set. */

#include <glib.h>
#include <stdbool.h>

typedef GHashTable set_t;
set_t *set(void);
void set_insert(set_t *s, const char *item);
bool set_contains(set_t *s, const char *item);
void set_union(set_t *a, set_t *b);
void set_destroy(set_t *s);

typedef GHashTableIter set_iter_t;
void set_iter(set_t *s, set_iter_t *i);
const char *set_iter_next(set_iter_t *i);

void set_foreach(set_t *s, void (*f)(void *value));
