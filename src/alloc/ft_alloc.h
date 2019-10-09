/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_alloc.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 04:47:46 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/27 02:05:43 by dzonda      ###    #+. /#+    ###.fr     */
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

# define EXIT_SUCCESS			(int)0
# define EXIT_FAILURE			(int)1

# define FT_AUINT		size_t
# define FT_AALIGNMENT	sizeof(FT_AUINT) * 2

# define FT_ATINY		(FT_AUINT)256
# define FT_ASMALL		(FT_AUINT)2048
# define FT_AN				(FT_AUINT)110
# define FT_AM				(FT_AUINT)110

# define FT_AHIST		(int)150

typedef struct rlimit		t_limit;
typedef pthread_mutex_t		t_mutex;

typedef enum				e_bool {
	FT_FALSE,
	FT_TRUE
}							t_bool;

typedef enum				e_alloc_ft {
	FT_MALLOC,
	FT_FREE,
	FT_REALLOC,
	FT_NONE
}							t_alloc_ft;

typedef enum				e_mutex_status {
	UNINITIALIZED,
	UNLOCKED,
	LOCKED,
	LOCKED_BY_PARENT
}							t_mutex_status;

typedef enum				e_alloc_index {
	ALLOC_TINY,
	ALLOC_SMALL,
	ALLOC_LARGE,
	ALLOC_NONE
}							t_aindex;

typedef struct				s_alloc_chunk {
	size_t					size;
	t_bool					free;
	struct s_alloc_chunk	*next;
	struct s_alloc_chunk	*prev;
}							t_achunk;

typedef struct				s_alloc_arena
{
	FT_AUINT			size;
	t_aindex				aindex;
	t_achunk				*head;
	struct s_alloc_arena	*next;
	struct s_alloc_arena	*prev;
}							t_aarena;

typedef struct				s_alloc_info
{
	FT_AUINT			rlim_cur;
	FT_AUINT			rlim_max;
	FT_AUINT			size_chunk;
	FT_AUINT			size_arena;
	FT_AUINT			pagesize;
	FT_AUINT			tiny_size_request;
	FT_AUINT			small_size_request;
	FT_AUINT			tiny_size_map;
	FT_AUINT			small_size_map;
}							t_ainfo;

typedef struct 				s_alloc_hist
{
		FT_AUINT		addr;
		FT_AUINT		size;
		t_bool					free;
		t_aindex				index;
		t_alloc_ft aft;
}											t_ahist;

typedef struct				s_alloc_state
{
	FT_AUINT			mmap[ALLOC_NONE];
	FT_AUINT			nbrchunks[ALLOC_NONE];
	FT_AUINT			nbrarenas[ALLOC_NONE];
	FT_AUINT			used[ALLOC_NONE];
	FT_AUINT			freed[ALLOC_NONE];
	FT_AUINT			ovhead[ALLOC_NONE];
}							t_astate;

typedef struct				s_alloc {
	t_mutex_status			mutex;
	t_ainfo					info;
	t_astate				state;
	t_aarena				*arena[ALLOC_NONE];
	t_ahist					history[FT_AHIST];
}							t_alloc;

extern t_alloc				g_alloc;
extern t_mutex				g_mutex;

t_achunk					*ft_alloc_arena_new(t_aarena **arena, size_t size);
int							ft_alloc_arena_del(t_aarena **arena);

int							ft_alloc_chunk_concat(t_aarena *arena, t_achunk *node);
void						*ft_alloc_chunk_copy(void *dest, const void *src, size_t n);
int							ft_alloc_chunk_split(t_aarena *arena, t_achunk *node, size_t size);

t_aarena					**ft_alloc_get_arena_by_size_request(size_t size);
t_aindex					ft_alloc_get_arena_index_by_size_request(size_t size);
size_t						ft_alloc_get_map_size_by_size_request(size_t size);
size_t						ft_alloc_get_size_aligned(size_t offset, size_t align);

void         			ft_alloc_history(t_achunk *chunk, t_aindex index, t_alloc_ft aft);

int							ft_alloc_init(void);

void						*ft_alloc_memset(void *b, int c, size_t len);
void						*ft_alloc_memcpy(void *dest, const void *src, size_t n);

int							ft_alloc_pthread_lock(void);
int							ft_alloc_pthread_lock_by_parent(void);
int							ft_alloc_pthread_unlock(void);
int							ft_alloc_pthread_unlock_by_parent(void);

t_aarena					**ft_alloc_search_arena_by_address(void *ptr);
t_achunk					*ft_alloc_search_chunk_by_address(t_aarena *arena, void *ptr);
t_achunk					*ft_alloc_search_chunk_by_size(t_aarena *arena, size_t size);

int							ft_alloc_state_mmap(t_aindex aindex, size_t size, t_bool mmap);
int							ft_alloc_state_nbrarenas(t_aindex aindex, t_bool add);
int							ft_alloc_state_nbrchunks(t_aindex aindex, t_bool add);

int							ft_alloc_state_freed(t_aindex aindex, size_t size, t_bool free);
int							ft_alloc_state_swap(t_aindex aindex, size_t size, t_bool free);
int							ft_alloc_state_used(t_aindex aindex, size_t size, t_bool free);
int							ft_alloc_state_ovhead(t_aindex aindex, size_t size, t_bool free);

#endif
