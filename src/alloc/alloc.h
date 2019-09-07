/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alloc.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/05 03:43:01 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/05 03:51:45 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_ALLOC_H
# define FT_ALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <stdint.h>
# include <sys/mman.h>
# include "../alloc_lib/alloc_lib.h"

# define FT_ALLOC_UINT      		size_t
# define FT_ALLOC_SIZE_NODE     32
# define FT_ALLOC_ALIGNMENT     sizeof(FT_ALLOC_UINT)

# define FT_ALLOC_PAGESIZE      (getpagesize())
# define FT_ALLOC_TINY          (FT_ALLOC_PAGESIZE / 16)
# define FT_ALLOC_SMALL         (FT_ALLOC_PAGESIZE / 2)
# define FT_ALLOC_N             (FT_ALLOC_PAGESIZE * 10)
# define FT_ALLOC_M             (FT_ALLOC_PAGESIZE * 10)

typedef enum	e_bool {
	TRUE,
	FALSE
}				t_bool;

typedef enum	e_alloc_arena {
	ALLOC_TINY,
	ALLOC_SMALL,
	ALLOC_LARGE,
	ALLOC_NONE
}				t_alloc_arena;

typedef enum	e_alloc_error {
	AE_RALL,
	AE_RALL_MMAP,
	AE_UNDEFINED
}				t_aerror;


typedef struct			s_node {
	size_t			size;
	t_bool			free;
	struct s_node	*next;
	struct s_node	*prev;
}						t_node;

typedef struct s_alloc_info
{
	FT_ALLOC_UINT	rlim_cur;
	FT_ALLOC_UINT rlim_max;
	FT_ALLOC_UINT rall_mmap;
	FT_ALLOC_UINT rall_inuse[ALLOC_NONE];
	FT_ALLOC_UINT rall_freed[ALLOC_NONE];
}							t_alloc_info;

typedef struct			s_alloc_state {
	t_alloc_info	alloc_info;
	t_node			 *alloc_arena[ALLOC_NONE];
}						t_alloc_state;

extern				t_alloc_state g_alloc_state;

int   				ft_alloc_init();
int						ft_alloc_arena(t_node **head, size_t size);
int						ft_alloc_arena_split(t_node *node, size_t size);

size_t				ft_alloc_get_size_aligned(size_t offset, size_t align);
size_t				ft_alloc_get_size_arena(size_t size);
t_node  			**ft_alloc_get_arena(size_t size);

t_node				*ft_alloc_search(t_node **head, size_t size);

int   				ft_alloc_init_modifier();

int 					ft_alloc_error(t_aerror err);


#endif
