/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "dict.h"
#include <glib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

dict_t *dict(void (*value_destroyer)(void *value))
{
    return g_hash_table_new_full(g_str_hash, g_str_equal, NULL, value_destroyer);
}

void dict_set(dict_t *d, const char *key, void *value)
{
    g_hash_table_insert(d, (gpointer)key, value);
}

void *dict_get(dict_t *d, const char *key)
{
    return g_hash_table_lookup(d, key);
}

bool dict_contains(dict_t *d, const char *key)
{
    return g_hash_table_contains(d, key);
}

void dict_destroy(dict_t *d)
{
    g_hash_table_destroy(d);
}
