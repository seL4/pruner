/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

/* Implementation of a dictionary. */

#include <glib.h>
#include <stdbool.h>

typedef GHashTable dict_t;

dict_t *dict(void (*value_destroyer)(void *value));
void dict_set(dict_t *d, const char *key, void *value);
void *dict_get(dict_t *d, const char *key);
bool dict_contains(dict_t *d, const char *key);
void dict_destroy(dict_t *d);
