#include "alloc.h"

int   ft_alloc_init_modifier()
{
  if (g_alloc_state.alloc_arena[ALLOC_TINY] == NULL &&
  g_alloc_state.alloc_arena[ALLOC_SMALL] == NULL &&
  g_alloc_state.alloc_arena[ALLOC_LARGE] == NULL)
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}