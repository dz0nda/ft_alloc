#include "show.h"

void	ft_putstr(const char *s)
{
    while (*s)
    {
        write(1, s, 1);
        s++;
    }
}

void  ft_show_alloc_addr(FT_ALLOC_UINT ptr, FT_ALLOC_UINT size, t_bool free)
{
  ft_puthexa(ptr);
  ft_putstr(" - ");
  ft_puthexa(ptr + size);
  ft_putstr(" : ");
  ft_putnbr(size);
  ft_putstr(" bytes");
  if (free == FALSE)
    ft_putstr(" - used");
  else if (free == TRUE)
    ft_putstr(" - freed");
  ft_putstr("\n");
}

 void 	ft_show_alloc_arena(t_aarena *arena)
{
  t_achunk  *chunk;

  if (arena == NULL || (chunk = arena->head) == NULL)
    return ;
  ft_putstr("    - ");
  ft_show_alloc_addr((FT_ALLOC_UINT)chunk, chunk->size, chunk->free);
  while ((chunk = chunk->next) != arena->head)
  {
    ft_putstr("    - ");
    ft_show_alloc_addr((FT_ALLOC_UINT)chunk, chunk->size, chunk->free);
  }
}

void  ft_show_alloc_detail(const char *s, FT_ALLOC_UINT nb, t_bool dl)
{
  ft_putstr(s);
  ft_putnbr(nb);
	ft_putstr(" bytes ");
	if (dl == TRUE)
		ft_putstr("\n");
}