#include "alloc.h"

t_alloc				g_alloc;
t_mutex				g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void			*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;
	unsigned char	set;

	s = (unsigned char *)b;
	set = (unsigned char)c;
	while (len-- > 0)
	{
		*s = set;
		s++;
	}
	return (b);
}

static int			ft_alloc_init_info()
{
	t_limit			rlp;
	t_ainfo			*info;

	ft_memset(&rlp, 0, sizeof(t_limit));
	info = &(g_alloc).info;
	if (getrlimit(RLIMIT_MEMLOCK, &rlp) == -1)
		return (EXIT_FAILURE);
	info->rlim_cur = (FT_ALLOC_UINT)rlp.rlim_cur;
	info->rlim_max = (FT_ALLOC_UINT)rlp.rlim_max;
	info->size_chunk = ft_alloc_get_size_aligned(sizeof(t_achunk), FT_ALLOC_ALIGNMENT);
	info->size_arena = ft_alloc_get_size_aligned(sizeof(t_aarena), FT_ALLOC_ALIGNMENT);
	if ((info->pagesize = getpagesize()) == 0)
		return (EXIT_FAILURE);
	info->tiny_size_request = ft_alloc_get_size_aligned(FT_ALLOC_TINY, FT_ALLOC_ALIGNMENT);
	info->small_size_request = ft_alloc_get_size_aligned(FT_ALLOC_SMALL, FT_ALLOC_ALIGNMENT);
	info->tiny_size_map = (info->tiny_size_request * FT_ALLOC_N) + (info->size_chunk * (FT_ALLOC_N)) + info->size_arena;
	info->small_size_map = (info->small_size_request * FT_ALLOC_M) + (info->size_chunk * (FT_ALLOC_M)) + info->size_arena;
	return (EXIT_SUCCESS);
}

int					ft_alloc_init(void)
{
	if (ft_alloc_init_info() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
