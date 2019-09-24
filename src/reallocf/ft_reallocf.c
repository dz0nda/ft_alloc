#include "ft_reallocf.h"

void			*reallocf(void *ptr, size_t size)
{
    void    *new;

    new = NULL;
    if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return (NULL);
	ft_alloc_pthread_lock_by_parent();
    new = realloc(ptr, size);
	ft_alloc_pthread_unlock_by_parent();
    if (new == NULL)
        free(ptr);
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return (NULL);
    return (new);
}