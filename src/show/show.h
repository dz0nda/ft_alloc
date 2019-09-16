#ifndef FT_SHOW_H
# define FT_SHOW_H

# include "../alloc/alloc.h"

void		ft_puthexa(FT_ALLOC_UINT nb);
void		ft_putnbr(int nb);

static void ft_show_alloc(t_bool details);
void    show_alloc_mem(void);
void    show_alloc_info(void);
void    show_alloc_state(void);

void    ft_putstr(const char *s);
void    ft_show_alloc_addr(FT_ALLOC_UINT ptr, FT_ALLOC_UINT size, t_bool free);
void 	  ft_show_alloc_arena(t_aarena *arena);
void    ft_show_alloc_detail(const char *s, FT_ALLOC_UINT nb, t_bool dl);

#endif
