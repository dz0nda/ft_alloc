#include "alloc.h"

static int ft_alloc_chunk_concat_info(t_aindex aindex, t_achunk *node)
{
  if (node->free == FALSE)
  {
    ft_alloc_state_used(aindex, FT_ALLOC_SIZE_CHUNK, FALSE);
    ft_alloc_state_swap(aindex, node->size, FALSE);
  }
  else
    ft_alloc_state_freed(aindex, FT_ALLOC_SIZE_CHUNK, TRUE);
  return (EXIT_SUCCESS);
}

static int		ft_alloc_chunk_split_info(t_aindex aindex, t_achunk *node, size_t size)
{
  if (!(node->size > (size + FT_ALLOC_SIZE_CHUNK)))
    return (EXIT_FAILURE);
  if (node->free == FALSE)
  {
    ft_alloc_state_used(aindex, FT_ALLOC_SIZE_CHUNK, TRUE);
    ft_alloc_state_swap(aindex, node->size - (FT_ALLOC_SIZE_CHUNK + size), TRUE);
  }
  else
    ft_alloc_state_freed(aindex, FT_ALLOC_SIZE_CHUNK, FALSE);
  return (EXIT_SUCCESS);
}

int     ft_alloc_chunk_concat(t_aarena *arena, t_achunk *node)
{
	if ((node->next->free == TRUE) && (node->next > node))
  {
    ft_alloc_chunk_concat_info(arena->aindex, node);
    node->size += node->next->size + FT_ALLOC_SIZE_CHUNK;
    node->next = node->next->next;
    node->next->prev = node;
  }
  if ((node->prev->free == TRUE) && (node->prev < node))
  {
    ft_alloc_chunk_concat_info(arena->aindex, node);
    node->prev->size += node->size + FT_ALLOC_SIZE_CHUNK;
    node->prev->free = node->free;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    ft_alloc_chunk_copy((void *)(node->prev + 1), (void *)(node + 1), node->size);
    node = node->prev;
  }
}

void		*ft_alloc_chunk_copy(void *dest, const void *src, size_t n)
{
	unsigned char *d;
	unsigned char *s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n-- > 0)
	{
		*d = *s;
		d++;
		s++;
	}
	return (dest);
}

int		ft_alloc_chunk_split(t_aarena *arena, t_achunk *node, size_t size)
{
	t_achunk *new;

	new = NULL;
  if (ft_alloc_chunk_split_info(arena->aindex, node, size) == EXIT_FAILURE)
    return (EXIT_FAILURE);
	new = (t_achunk *)((FT_ALLOC_UINT)node + FT_ALLOC_SIZE_CHUNK + size);
	new->size = node->size - (FT_ALLOC_SIZE_CHUNK + size);
	new->free = TRUE;
	node->size = size;
	new->next = node->next;
	new->prev = node;
	node->next->prev = new;
	node->next = new;
	return (EXIT_SUCCESS);
}