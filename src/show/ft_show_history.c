#include "ft_show.h"

void ft_show_alloc_history(void)
{
	const char	*anames[ALLOC_NONE] = { "TINY : ", "SMALL : ", "LARGE : " };
  t_aindex aindex;
  t_ahist *history;
  int i;
  int j;

  aindex = -1;
  history = g_alloc.history;
  i = FT_ALLOC_HIST;
  j = -1;
  while (--i > -1)
    if (history[i].addr > 0)
    {
      ft_putnbr(++j);
      ft_putstr(". ");
      ft_putstr(anames[history[i].index]);
      ft_show_alloc_addr(history[i].addr, history[i].size, history[i].free);
    }
}