/* fake_malloc.h */
#include "fff.h"

DECLARE_FAKE_VALUE_FUNC(void *, malloc, size_t);
DECLARE_FAKE_VOID_FUNC(free, void *);
