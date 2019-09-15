#include "alloc.h"

int   ft_alloc_state_freed(t_aindex aindex, size_t size, t_bool free)
{
  t_astate  *state;

  state = &(g_alloc).state;
  if (free == TRUE)
    state->freed[aindex] += size;
  else
    state->freed[aindex] -= size;
  return (EXIT_SUCCESS);
}

int   ft_alloc_state_mmap(t_aindex aindex, size_t size, t_bool mmap)
{
  t_astate *state;

  state = &(g_alloc).state;
  if (mmap == TRUE)
    state->mmap[aindex] += size;
  else
    state->mmap[aindex] -= size;
  return (EXIT_SUCCESS);
}

int   ft_alloc_state_swap(t_aindex aindex, size_t size, t_bool free)
{
  t_astate  *state;

  state = &(g_alloc).state;
  if (free == TRUE)
  {
    state->freed[aindex] += size;
    state->used[aindex] -= size;
  }
  else
  {
    state->freed[aindex] -= size;
    state->used[aindex] += size;
  }
  return (EXIT_SUCCESS);
}

int   ft_alloc_state_used(t_aindex aindex, size_t size, t_bool free)
{
  t_astate  *state;

  state = &(g_alloc).state;
  if (free == TRUE)
    state->used[aindex] -= size;
  else
    state->used[aindex] += size;
  return (EXIT_SUCCESS);
}