#ifndef _SORTS_H_
#define _SORTS_H_

#include <stddef.h>

typedef int (*cmp_func_t)(const void *, const void *, const void *param);

void *BinarySearch(void *arr, size_t elm_size, size_t num_of_elm, cmp_func_t cmp, const void *data, const void *param);

void *JumpSearch(void *arr, size_t elm_size, size_t num_of_elm, cmp_func_t cmp, const void *data, const void *param);

#endif
