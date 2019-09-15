#include "alloc.h"

t_alloc       g_alloc;

static void	*ft_memset(void *b, int c, size_t len)
{
    size_t i;

    i = 0;
    while (i < len)
        ((char *)b)[i++] = c;
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
    if ((info->pagesize = getpagesize()) == 0)
        return (EXIT_FAILURE);
    info->tiny_size_request = info->pagesize / 16;
    info->small_size_request = info->pagesize / 2;
    info->tiny_size_arena = info->pagesize * 10;
    info->small_size_arena = info->pagesize * 10;
    return (EXIT_SUCCESS);
}
 
int		            ft_alloc_init(void)
{
    if (ft_alloc_init_info() == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}