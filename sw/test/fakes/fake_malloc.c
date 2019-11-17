/* fake_malloc.c */
#include "stdlib.h"
#include "stdio.h"
#include "fake_malloc.h"

DEFINE_FAKE_VALUE_FUNC(void *, malloc, size_t);
DEFINE_FAKE_VOID_FUNC(free, void *);
