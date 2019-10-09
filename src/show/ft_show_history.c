#include "ft_show.h"

void ft_show_alloc_history(void)
{
	const char	*anames[ALLOC_NONE] = { "TINY", "SMALL", "LARGE" };
  const char  *ftnames[FT_NONE] = { "MALLOC", "FREE", "REALLOC" };
  t_aindex aindex;
  t_ahist *history;
  int i;
  int j;

  aindex = -1;
  history = g_alloc.history;
  i = FT_AHIST;
  j = 0;
	ft_putstr("|| show_alloc_history ||\n\n");
  while (--i > -1)
    if (history[i].addr > 0)
    {
      ft_putnbr(++j);
      ft_putstr(". ");
      ft_putstr(anames[history[i].index]);
      ft_putstr("\t");
      ft_putstr(ftnames[history[i].aft]);
      ft_putstr("\t\t");
      ft_show_alloc_addr(history[i].addr, history[i].size, history[i].free);
    }
}