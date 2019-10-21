// /* ************************************************************************** */
// /*                                                          LE - /            */
// /*                                                              /             */
// /*   ft_realloc.c                                     .::    .:/ .      .::   */
// /*                                                 +:+:+   +:    +:  +:+:+    */
// /*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
// /*                                                 #+#   #+    #+    #+#      */
// /*   Created: 2019/10/11 21:16:55 by dzonda       #+#   ##    ##    #+#       */
// /*   Updated: 2019/10/11 21:17:01 by dzonda      ###    #+. /#+    ###.fr     */
// /*                                                         /                  */
// /*                                                        /                   */
// /* ************************************************************************** */

#include "ft_realloc.h"

static void     *ft_realloc_by_concat(t_achunk *chunk, void *ptr, size_t size)
{
	t_aindex	aindex_req;
	t_aindex	aindex_chunk;

	aindex_req = ft_alloc_get_aindex_by_size(size);
	aindex_chunk = ft_alloc_get_aindex_by_size(chunk->size);
	if (aindex_req != aindex_chunk)
		return (NULL);
	if (size > chunk->size)
		chunk = ft_alloc_chunk_concat(chunk);
	chunk = ft_alloc_chunk_split(chunk, size);
	if (size > chunk->size)
		return (NULL);
    ft_memcpy((void *)(chunk + 1), ptr, size);
	// ft_alloc_history(chunk, aindex, FT_REALLOC);
	return ((void *)(chunk + 1));
}

static void		*ft_realloc_by_mmap(t_achunk *chunk, void *ptr, size_t size)
{
	void		*new;

	new = NULL;
	ft_alloc_pthread_lock_by_alloc();
	new = malloc(size);
	ft_alloc_pthread_unlock_by_alloc();
	if (new == NULL)
		return (NULL);
    if (ptr != NULL && chunk != NULL)
    {
        ft_memcpy(new, ptr, (chunk->size >= size) ? size : chunk->size);
        ft_alloc_pthread_lock_by_alloc();
        free(ptr);
        ft_alloc_pthread_unlock_by_alloc();
    }
	return (new);
}

static void		*ft_realloc(void *ptr, size_t size)
{
	void		*new;
	t_achunk	*chunk;

	new = NULL;
	chunk = NULL;
	size = ft_alloc_init_size(size, FT_AALIGN);
	if (ptr == NULL) 
        new = ft_realloc_by_mmap(chunk, ptr, size);
	else if ((chunk = ft_alloc_search_chunk_by_address(ptr)) != NULL)
		if ((new = ft_realloc_by_concat(chunk, ptr, size)) == NULL)
			new = ft_realloc_by_mmap(chunk, ptr, size);
	return (new);
}

void			*realloc(void *ptr, size_t size)
{
	void		*new;

	new = NULL;
	if (ft_alloc_pthread_lock() == EXIT_FAILURE)
		return (NULL);
	if (ft_alloc_init() == EXIT_SUCCESS)
		new = ft_realloc(ptr, size);
	if (ft_alloc_pthread_unlock() == EXIT_FAILURE)
		return (NULL);
	return (new);
}
