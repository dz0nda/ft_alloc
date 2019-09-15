#include "show.h"

void	ft_putstr(const char *s)
{
    while (*s)
    {
        write(1, s, 1);
        s++;
    }
}

void  ft_show_alloc_addr(FT_ALLOC_UINT ptr, FT_ALLOC_UINT size)
{
  ft_putstr("[ ");
  ft_puthexa(ptr);
  ft_putstr(" - ");
  ft_puthexa(ptr + size);
  ft_putstr(" ] : ");
  ft_putnbr(size);
  ft_putstr(" bytes \n");
}

 void 	ft_show_alloc_arena(t_aarena *arena, t_bool free)
{
  t_achunk  *chunk;

  chunk = NULL;
  if (free == -1)
  {
    while (arena != NULL)
    {
      ft_show_alloc_addr((FT_ALLOC_UINT)arena->head, arena->size - g_alloc.info.size_arena);
      arena = arena->next;
    }
  }
  else
  {
    if (arena == NULL || (chunk = arena->head) == NULL)
      return ;
    if (chunk->free == free)
        ft_show_alloc_addr((FT_ALLOC_UINT)chunk, chunk->size);
    while ((chunk = chunk->next) != arena->head)
		  if (chunk->free == free)
        ft_show_alloc_addr((FT_ALLOC_UINT)chunk, chunk->size);
  }
}