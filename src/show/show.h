#ifndef FT_SHOW_H
# define FT_SHOW_H

# include "../alloc/alloc.h"

# define FT_CRED      "\033[0;31m"
# define FT_CGREEN    "\033[0;32m"
# define FT_CYELLOW   "\033[0;33m"
# define FT_CBOLD     "\033[1m"
# define FT_CSTOP     "\033[0;m"

typedef enum  e_alloc_color
{
  COLOR_RED,
  COLOR_GREEN,
  COLOR_YELLOW,
  COLOR_BOLD
}             t_acolor;

void		ft_puthexa(FT_ALLOC_UINT nb);
void		ft_putnbr(int nb);

void    show_alloc_mem(void);
void    show_alloc_info(void);
void    show_alloc_state(void);

void    ft_putstr(const char *s);
void    ft_putstr_color(const char *s, t_acolor color);
void    ft_show_alloc_addr(FT_ALLOC_UINT ptr, FT_ALLOC_UINT size, t_bool free);
void 	  ft_show_alloc_arena(t_aarena *arena);
void    ft_show_alloc_detail(const char *s, FT_ALLOC_UINT nb, t_bool dl, t_bool free);

#endif
