#include "alloc.h"

static int ft_alloc_chunk_concat_info(t_aarena *arena, t_achunk *node)
{
  if (node->free == FALSE)
  {
    ft_alloc_info_used(arena, FT_ALLOC_SIZE_CHUNK, FALSE);
    ft_alloc_info_total(arena, node->size, FALSE);
  }
  else
    ft_alloc_info_freed(arena, FT_ALLOC_SIZE_CHUNK, TRUE);
  return (EXIT_SUCCESS);
}

static int		ft_alloc_chunk_split_info(t_aarena *arena, t_achunk *node, size_t size)
{
  if (!(node->size > (size + FT_ALLOC_SIZE_CHUNK)))
    return (EXIT_FAILURE);
  if (node->free == FALSE)
  {
    ft_alloc_info_used(arena, FT_ALLOC_SIZE_CHUNK, TRUE);
    ft_alloc_info_total(arena, node->size - (FT_ALLOC_SIZE_CHUNK + size), TRUE);
  }
  else
    ft_alloc_info_freed(arena, FT_ALLOC_SIZE_CHUNK, FALSE);
  return (EXIT_SUCCESS);
}

int     ft_alloc_chunk_concat(t_aarena *arena, t_achunk *node)
{
	if ((node->next->free == TRUE) && (node->next > node))
  {
    ft_alloc_chunk_concat_info(arena, node);
    node->size += node->next->size + FT_ALLOC_SIZE_CHUNK;
    node->next = node->next->next;
    node->next->prev = node;
  }
  if ((node->prev->free == TRUE) && (node->prev < node))
  {
    ft_alloc_chunk_concat_info(arena, node);
    node->prev->size += node->size + FT_ALLOC_SIZE_CHUNK;
    node->prev->free = node->free;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    ft_memcpy((void *)(node->prev + 1), (void *)(node + 1), node->size);
    node = node->prev;
  }
}

int		ft_alloc_chunk_split(t_aarena *arena, t_achunk *node, size_t size)
{
	t_achunk *new;

	new = NULL;
  if (ft_alloc_chunk_split_info(arena, node, size) == EXIT_FAILURE)
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