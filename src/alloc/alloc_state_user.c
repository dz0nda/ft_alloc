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

int   ft_alloc_state_ovhead(t_aindex aindex, size_t size, t_bool free)
{
  t_astate  *state;

  state = &(g_alloc).state;
  if (free == TRUE)
    state->ovhead[aindex] -= size;
  else
    state->ovhead[aindex] += size;
  return (EXIT_SUCCESS);
}