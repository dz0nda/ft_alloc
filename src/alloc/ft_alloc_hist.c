#include "ft_alloc.h"

void         ft_alloc_history_add(t_achunk *chunk, t_aindex index)
{
  int i;
  t_ahist   *history;
  t_ahist   newhistory;
  t_ahist   nexthistory;

  i = -1;
  history = g_alloc.history;
  newhistory.addr = (FT_ALLOC_UINT)chunk + sizeof(t_achunk);
  newhistory.size = chunk->size;
  newhistory.free = chunk->free;
  newhistory.index = index;
  while (++i < FT_ALLOC_HIST)
  {
    ft_alloc_memcpy(&nexthistory, &history[i], sizeof(t_ahist));
    ft_alloc_memcpy(&history[i], &newhistory, sizeof(t_ahist));
    ft_alloc_memcpy(&newhistory, &nexthistory, sizeof(t_ahist));
  }
}
