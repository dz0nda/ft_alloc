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

# define FT_ALLOC_UINT      		size_t
# define FT_ALLOC_ALIGNMENT     sizeof(FT_ALLOC_UINT) * 2

# define FT_ALLOC_TINY          (FT_ALLOC_UINT)16
# define FT_ALLOC_SMALL         (FT_ALLOC_UINT)2
# define FT_ALLOC_N             (FT_ALLOC_UINT)10
# define FT_ALLOC_M             (FT_ALLOC_UINT)10

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

typedef struct			s_alloc_chunk {
	size_t			size;
	t_bool			free;
	struct s_alloc_chunk	*next;
	struct s_alloc_chunk	*prev;
}						t_achunk;

typedef struct s_alloc_arena
{
	FT_ALLOC_UINT size;
	t_aindex			aindex; 
	t_achunk			*head;
	struct s_alloc_arena *next;
	struct s_alloc_arena *prev;
}							t_aarena;

typedef struct 	s_alloc_info
{
	FT_ALLOC_UINT	rlim_cur;
	FT_ALLOC_UINT rlim_max;
	FT_ALLOC_UINT size_chunk;
	FT_ALLOC_UINT size_arena;
	FT_ALLOC_UINT	pagesize;
	FT_ALLOC_UINT tiny_size_request;
	FT_ALLOC_UINT small_size_request;
	FT_ALLOC_UINT tiny_size_arena;
	FT_ALLOC_UINT small_size_arena;
}								t_ainfo;

typedef struct 	s_alloc_state
{
	FT_ALLOC_UINT mmap[ALLOC_NONE];
	FT_ALLOC_UINT used[ALLOC_NONE];
	FT_ALLOC_UINT freed[ALLOC_NONE];
	FT_ALLOC_UINT	ovhead[ALLOC_NONE];
	t_aarena			*arena[ALLOC_NONE];

}								t_astate;

typedef struct			s_alloc {
	t_ainfo			info;
	t_astate		state;
}						t_alloc;

extern					t_alloc g_alloc;

t_achunk 				*ft_alloc_arena_new(t_aarena **arena, size_t size);
int							ft_alloc_arena_del(t_aarena *arena);

int     				ft_alloc_chunk_concat(t_aarena *arena, t_achunk *node);
void						*ft_alloc_chunk_copy(void *dest, const void *src, size_t n);
int							ft_alloc_chunk_split(t_aarena *arena, t_achunk *node, size_t size);

t_aarena  			**ft_alloc_get_arena_by_size(size_t size);
t_aindex  			ft_alloc_get_arena_index_by_size_request(size_t size);
size_t					ft_alloc_get_arena_size_by_size_request(size_t size);
size_t					ft_alloc_get_size_aligned(size_t offset, size_t align);

int   					ft_alloc_state_freed(t_aindex aindex, size_t size, t_bool free);
int   					ft_alloc_state_mmap(t_aindex aindex, size_t size, t_bool mmap);
int   					ft_alloc_state_swap(t_aindex aindex, size_t size, t_bool free);
int   					ft_alloc_state_used(t_aindex aindex, size_t size, t_bool free);
int   					ft_alloc_state_ovhead(t_aindex aindex, size_t size, t_bool free);

int   					ft_alloc_init(void);

t_aarena    		*ft_alloc_search_arena_by_address(void *ptr);
t_achunk    		*ft_alloc_search_chunk_by_address(t_aarena *arena, void *ptr);
t_achunk       	*ft_alloc_search_chunk_by_size(t_aarena *arena, size_t size);

#endif
