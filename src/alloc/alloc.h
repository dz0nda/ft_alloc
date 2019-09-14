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
# define FT_ALLOC_SIZE_ARENA    (FT_ALLOC_UINT)32
# define FT_ALLOC_SIZE_CHUNK    (FT_ALLOC_UINT)32
# define FT_ALLOC_SIZE_NODE     (FT_ALLOC_UINT)(FT_ALLOC_SIZE_CHUNK * 2)
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

typedef enum	e_alloc_index {
	ALLOC_TINY,
	ALLOC_SMALL,
	ALLOC_LARGE,
	ALLOC_NONE
}				t_aindex;

typedef enum	e_alloc_error {
	AE_INIT,
	AE_RALL,
	AE_a_mmap,
	AE_UNDEFINED
}				t_aerror;


typedef struct			s_alloc_chunk {
	size_t			size;
	t_bool			free;
	struct s_alloc_chunk	*next;
	struct s_alloc_chunk	*prev;
}						t_achunk;

typedef struct 	s_alloc_info
{
	FT_ALLOC_UINT	rlim_cur;
	FT_ALLOC_UINT rlim_max;
	FT_ALLOC_UINT a_mmap;
	FT_ALLOC_UINT a_used[ALLOC_NONE];
	FT_ALLOC_UINT a_freed[ALLOC_NONE];
}								t_ainfo;

typedef struct s_alloc_arena
{
	FT_ALLOC_UINT size;
	t_achunk			*head;
	struct s_alloc_arena *next;
}							t_aarena;

typedef struct			s_alloc_state {
	t_bool			init;
	t_ainfo			alloc_info;
	t_aarena				*alloc_arena[ALLOC_NONE];
}						t_astate;

extern					t_astate g_alloc_state;

t_achunk 				*ft_alloc_arena_mmap(t_aarena **arena, size_t size);

int     				ft_alloc_chunk_concat(t_aarena *arena, t_achunk *node);
int							ft_alloc_chunk_split(t_aarena *arena, t_achunk *node, size_t size);

int 						ft_alloc_error(t_aerror err);

t_aarena  			**ft_alloc_get_arena_by_size(size_t size);
t_aindex  			ft_alloc_get_arena_index_by_size_arena(size_t size);
t_aindex  			ft_alloc_get_arena_index_by_size_request(size_t size);
size_t					ft_alloc_get_arena_size_by_size(size_t size);
size_t					ft_alloc_get_size_aligned(size_t offset, size_t align);

int   					ft_alloc_info_freed(t_aarena *arena, size_t size, t_bool free);
int   					ft_alloc_info_mmap(size_t size, t_bool mmap);
int   					ft_alloc_info_used(t_aarena *arena, size_t size, t_bool free);
int   ft_alloc_info_total(t_aarena *arena, size_t size, t_bool free);

int   					ft_alloc_init(void);

t_aarena    		*ft_alloc_search_arena_by_address(void *ptr);
t_achunk    		*ft_alloc_search_chunk_by_address(t_aarena *arena, void *ptr);
t_achunk       	*ft_alloc_search_chunk_by_size(t_aarena *arena, size_t size);

#endif
