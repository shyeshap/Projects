#include <stdlib.h>
#include <assert.h>

#include "./../include/heapify.h" /* heapify API */

void Swap(void **ptr1, void **ptr2)
{
	void *tmp = NULL;

	assert(NULL != ptr1);
	assert(NULL != ptr2);

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;	
}

void HeapifyUp(void *arr, size_t size, size_t index, size_t element_size,
                                             compare_func_ptr cmp, void *param)
{
	void **new_data = (char *)arr + (index * element_size);
	void **parent = (char *)arr + (((index - 1 )/ 2) * element_size);

	assert(NULL != arr);
	assert(NULL != cmp);

	while (0 < index && 0 < cmp(*new_data, *parent, param))
	{
		Swap(parent, new_data); 
		index = (index - 1 )/ 2;
		new_data = parent;
		parent = (char *)arr + (index * element_size);

	}
}

void HeapifyDown(void *arr, size_t size, size_t index, size_t element_size,
                                               compare_func_ptr cmp, void *param)
{
	size_t left_child_indx = (((index + 1) * 2) - 1);
	size_t right_child_indx = ((index + 1) * 2);

	void **left_child = (char **)&arr + ((((index + 1) * 2) - 1) * element_size);
	void **right_child = (char **)&arr + (((index + 1) * 2) * element_size);
	void **parent = (char **)arr + (index * element_size);

	assert(NULL != arr);
	assert(NULL != cmp);

	while (left_child)
	{
		if (right_child && 0 < cmp(right_child, left_child, param))
		{
			if (0 < cmp(right_child, parent, param))
			{
				Swap(right_child, parent);
				parent = right_child;
				index = right_child_indx;
			}
		}
		
		else if (0 < cmp(left_child, parent, param))
		{
			Swap(left_child, parent);
			parent = left_child;
			index = left_child_indx;
		}
	
		right_child_indx = ((index + 1) * 2) * element_size;
		left_child_indx = (((index + 1) * 2) - 1) * element_size;

		right_child = (char **)arr + right_child_indx;
		left_child = (char **)arr + left_child_indx;
	}
}