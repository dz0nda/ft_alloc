#include "alloc.h"

t_alloc       g_alloc;

static void	        *ft_memset(void *b, int c, size_t len)
{
    unsigned char *s;
    unsigned char set;

    s = (unsigned char *)b;
    set = (unsigned char)c;
    while (len-- > 0)
    {
        *s = set;
        s++;
    }
    return (b);
}

static int          ft_alloc_init_info()
{
    t_limit         rlp;
    t_ainfo         *info;

    ft_memset(&rlp, 0, sizeof(t_limit));
    info = &(g_alloc).info;
    if (getrlimit(RLIMIT_MEMLOCK, &rlp) == -1)
        return (EXIT_FAILURE);
    info->rlim_cur = (FT_ALLOC_UINT)rlp.rlim_cur;
    info->rlim_max = (FT_ALLOC_UINT)rlp.rlim_max;
    info->size_chunk = ft_alloc_get_size_aligned(sizeof(t_achunk), FT_ALLOC_ALIGNMENT);
    info->size_arena = ft_alloc_get_size_aligned(sizeof(t_aarena) + info->size_chunk, FT_ALLOC_ALIGNMENT);
    if ((info->pagesize = getpagesize()) == 0)
        return (EXIT_FAILURE);
    info->tiny_size_request = info->pagesize / FT_ALLOC_TINY;
    info->small_size_request = info->pagesize / FT_ALLOC_SMALL;
    info->tiny_size_arena = info->pagesize * FT_ALLOC_N;
    info->small_size_arena = info->pagesize * FT_ALLOC_M;
    return (EXIT_SUCCESS);
}
 
int		            ft_alloc_init(void)
{
    if (ft_alloc_init_info() == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}