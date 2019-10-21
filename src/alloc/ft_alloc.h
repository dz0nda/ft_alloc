/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 20:57:59 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 21:41:03 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_ALLOC_H
# define FT_ALLOC_H

# include <unistd.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include <pthread.h>
# include "../libft/ft_libft.h"

# define EXIT_SUCCESS			(int)0
# define EXIT_FAILURE			(int)1

# define FT_AUINT		size_t
# define FT_AALIGN	sizeof(FT_AUINT) * 2

# define FT_ATINY		(FT_AUINT)256
# define FT_ASMALL		(FT_AUINT)2048
# define FT_AN				(FT_AUINT)110
# define FT_AM				(FT_AUINT)110

# define FT_AHIST		(int)150

typedef struct rlimit		t_limit;
typedef pthread_mutex_t		t_mutex;

typedef enum				e_bool {
	FT_TRUE = 0,
	FT_FALSE
}							t_bool;

typedef enum				e_alloc_ft {
	FT_MALLOC,
	FT_FREE,
	FT_REALLOC,
	FT_NONE
}							t_alloc_ft;

typedef enum				e_alloc_mutex {
	FT_UNINITIALIZED = 0,
	FT_UNLOCKED,
	FT_LOCKED,
	FT_LOCKED_BY_ALLOC
}							t_amutex;

typedef enum				e_alloc_index {
	FT_ALLOC_TINY,
	FT_ALLOC_SMALL,
	FT_ALLOC_LARGE,
	FT_ALLOC_AINDEX_MAX
}							t_aindex;

typedef struct				s_alloc_chunk {
	FT_AUINT				size;
	t_bool					free;
	struct s_alloc_chunk	*next;
	struct s_alloc_chunk	*prev;
}							t_achunk;

typedef struct				s_alloc_arena
{
	FT_AUINT				size;
	t_aindex				aindex;
	t_achunk				*head;
	struct s_alloc_arena	*next;
	struct s_alloc_arena	*prev;
}							t_aarena;

typedef struct				s_alloc_info
{
	FT_AUINT			rlim_cur;
	FT_AUINT			rlim_max;
	FT_AUINT			pagesize;
	FT_AUINT			size_chunk;
	FT_AUINT			size_arena;
	FT_AUINT			tiny_size_request;
	FT_AUINT			small_size_request;
	FT_AUINT			tiny_size_map;
	FT_AUINT			small_size_map;
}							t_ainfo;

typedef struct				s_alloc_hist
{
	FT_AUINT			addr;
	FT_AUINT			size;
	t_bool				free;
	t_aindex			index;
	t_alloc_ft			aft;
}							t_ahist;

typedef struct				s_alloc_state
{
	FT_AUINT			mmap[FT_ALLOC_AINDEX_MAX];
	FT_AUINT			nbrchunks[FT_ALLOC_AINDEX_MAX];
	FT_AUINT			nbrarenas[FT_ALLOC_AINDEX_MAX];
	FT_AUINT			used[FT_ALLOC_AINDEX_MAX];
	FT_AUINT			freed[FT_ALLOC_AINDEX_MAX];
	FT_AUINT			ovhead[FT_ALLOC_AINDEX_MAX];
}							t_astate;

typedef struct				s_alloc {
	t_amutex			mutex;
	t_ainfo					info;
	t_astate				state;
	t_aarena				*arena[FT_ALLOC_AINDEX_MAX];
	t_ahist					history[FT_AHIST];
}							t_alloc;

extern t_alloc				g_alloc;
extern t_mutex				g_mutex;

t_aarena					**ft_alloc_get_arena_by_size(size_t size);
t_aindex					ft_alloc_get_aindex_by_size(size_t size);
t_achunk					*ft_alloc_arena_new(size_t size);
int							ft_alloc_arena_del(t_achunk *chunk);

t_achunk					*ft_alloc_chunk_concat(t_achunk *chunk);
t_achunk					*ft_alloc_chunk_split(t_achunk *chunk, size_t size);

void						ft_alloc_history(t_achunk *chunk, t_aindex index, t_alloc_ft aft);

size_t						ft_alloc_init_size(size_t offset, size_t align);
int							ft_alloc_init(void);

int							ft_alloc_pthread_lock(void);
int							ft_alloc_pthread_lock_by_alloc(void);
int							ft_alloc_pthread_unlock(void);
int							ft_alloc_pthread_unlock_by_alloc(void);

t_aarena					**ft_alloc_search_arena_by_address(void *ptr);
t_achunk					*ft_alloc_search_chunk_by_address(void *ptr);
t_achunk					*ft_alloc_search_chunk_by_size(size_t size);

#endif
