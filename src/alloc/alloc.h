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
# define FT_ALLOC_SIZE_NODE     32
# define FT_ALLOC_ALIGNMENT     sizeof(FT_ALLOC_UINT)

# define FT_ALLOC_PAGESIZE      (getpagesize())
# define FT_ALLOC_TINY          (FT_ALLOC_PAGESIZE / 16)
# define FT_ALLOC_SMALL         (FT_ALLOC_PAGESIZE / 2)
# define FT_ALLOC_N             (FT_ALLOC_PAGESIZE * 10)
# define FT_ALLOC_M             (FT_ALLOC_PAGESIZE * 10)

typedef enum	e_free {
	TRUE,
	FALSE
}				t_free;

typedef enum	e_alloc_arena {
	ALLOC_TINY,
	ALLOC_SMALL,
	ALLOC_LARGE,
	ALLOC_NONE
}				t_alloc_arena;

typedef struct			s_node {
	size_t			size;
	t_free			free;
	struct s_node	*next;
	struct s_node	*prev;
}						t_node;

typedef struct			s_allocinfo {
	t_node			*arena[ALLOC_NONE];
}						t_allocinfo;

extern				t_allocinfo g_allocinfo;

int						ft_alloc_arena(t_node **head, size_t size);
int						ft_alloc_arena_split(t_node *node, size_t size);

size_t				ft_alloc_get_size_aligned(size_t offset, size_t align);
size_t				ft_alloc_get_size_arena(size_t size);
t_node  			**ft_alloc_get_arena(size_t size);

t_node				*ft_alloc_search(t_node **head, size_t size);

#endif
