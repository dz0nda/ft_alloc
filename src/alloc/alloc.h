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
# define FT_ALLOC_SIZE_META     (FT_ALLOC_UINT)32
# define FT_ALLOC_SIZE_NODE     (FT_ALLOC_UINT)(FT_ALLOC_SIZE_META * 2)
# define FT_ALLOC_ALIGNMENT     sizeof(FT_ALLOC_UINT)

# define FT_ALLOC_PAGESIZE      (getpagesize())
# define FT_ALLOC_TINY          (FT_ALLOC_UINT)(FT_ALLOC_PAGESIZE / 16)
# define FT_ALLOC_SMALL         (FT_ALLOC_UINT)(FT_ALLOC_PAGESIZE / 2)
# define FT_ALLOC_N             (FT_ALLOC_UINT)(FT_ALLOC_PAGESIZE * 10)
# define FT_ALLOC_M             (FT_ALLOC_UINT)(FT_ALLOC_PAGESIZE * 10)

typedef struct rlimit 	t_limit;

typedef enum	e_bool {
	FALSE,
	TRUE
}				t_bool;

typedef enum	e_alloc_arena {
	ALLOC_TINY,
	ALLOC_SMALL,
	ALLOC_LARGE,
	ALLOC_NONE
}				t_aarena;

typedef enum	e_alloc_error {
	AE_INIT,
	AE_RALL,
	AE_a_mmap,
	AE_UNDEFINED
}				t_aerror;


typedef struct			s_alloc_node {
	size_t			size;
	t_bool			free;
	struct s_alloc_node	*next;
	struct s_alloc_node	*prev;
}						t_anode;

typedef struct			s_alloc_noder {

}						t_anoder;

typedef struct s_alloc_info
{
	FT_ALLOC_UINT	rlim_cur;
	FT_ALLOC_UINT rlim_max;
	FT_ALLOC_UINT a_mmap;
	FT_ALLOC_UINT a_used[ALLOC_NONE];
	FT_ALLOC_UINT a_free[ALLOC_NONE];
	FT_ALLOC_UINT a_addr[ALLOC_NONE];

}							t_alloc_info;

typedef struct			s_alloc_state {
	t_bool			init;
	t_alloc_info	alloc_info;
	t_anode				*alloc_arena[ALLOC_NONE];
}						t_alloc_state;

extern					t_alloc_state g_alloc_state;

t_anode 				*ft_alloc_arena(size_t size);

int     				ft_alloc_concat(t_anode *node);
int     				ft_alloc_concat_next(t_anode *node);
int    				  ft_alloc_concat_prev(t_anode *node);

int 						ft_alloc_error(t_aerror err);

size_t					ft_alloc_get_size_aligned(size_t offset, size_t align);
t_aarena  			ft_alloc_get_arena_index_by_size(size_t size);
size_t					ft_alloc_get_arena_size_by_size(size_t size);
t_anode  				**ft_alloc_get_arena_by_size(size_t size);

int   					ft_alloc_info_free(size_t size, t_bool free);
int   					ft_alloc_info_used_free(size_t size, t_bool free);
int   					ft_alloc_info_mmap(size_t size, t_bool free);
int		   				ft_alloc_info_address(FT_ALLOC_UINT ptr, size_t size);

int   					ft_alloc_init(void);

t_anode       	*ft_alloc_search_by_size(size_t size);
t_anode					*ft_alloc_search_by_address(void *ptr);

int							ft_alloc_split(t_anode *node, size_t size);

#endif
