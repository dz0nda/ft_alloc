#ifndef FT_SHOW_H
# define FT_SHOW_H

# include "../alloc/alloc.h"

void    ft_show_alloc_info(void);
void    ft_show_alloc_state(void);

void		ft_puthexa(FT_ALLOC_UINT nb);
void		ft_putnbr(int nb);

void    show_alloc_mem(void);
void    show_alloc_mem_free(void);

void    ft_putstr(const char *s);
void    ft_show_alloc_addr(FT_ALLOC_UINT ptr, FT_ALLOC_UINT size);
void 	  ft_show_alloc_arena(t_aarena *arena, t_bool free);

#endif
