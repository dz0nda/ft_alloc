#include "alloc.h"

int     ft_alloc_concat(t_anode *node)
{
	int exit;

	exit = EXIT_FAILURE;
  if (ft_alloc_concat_prev(node) == EXIT_SUCCESS)
    exit = EXIT_SUCCESS;
  if (ft_alloc_concat_next(node) == EXIT_SUCCESS)
    exit = EXIT_SUCCESS;
	return (exit);
}

int     ft_alloc_concat_next(t_anode *node)
{
	if (!((node->next->free == TRUE) && (node->next > node)))
    return (EXIT_FAILURE);
  node->size += node->next->size + FT_ALLOC_SIZE_META;
  node->next = node->next->next;
  node->next->prev = node;
  ft_alloc_info_free(FT_ALLOC_SIZE_META, TRUE);
  return (EXIT_SUCCESS);
}

int     ft_alloc_concat_prev(t_anode *node)
{
	if (!((node->prev->free == TRUE) && (node->prev < node)))
    return (EXIT_FAILURE);
  node->prev->size += node->size + FT_ALLOC_SIZE_META;
  node->prev->next = node->next;
  node->next->prev = node->prev;
  node = node->prev;
  ft_alloc_info_free(FT_ALLOC_SIZE_META, TRUE);
  return (EXIT_SUCCESS);
}