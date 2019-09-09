#include "alloc.h"

static int ft_alloc_init_info()
{
    t_limit rlp;
    t_alloc_info  *alloc_info;

    ft_memset(&rlp, 0, sizeof(t_limit));
    alloc_info = &(g_alloc_state).alloc_info;
    if (getrlimit(RLIMIT_AS, &rlp) == -1)
        return (ft_alloc_error(AE_INIT));
    alloc_info->rlim_cur = (FT_ALLOC_UINT)rlp.rlim_cur;
    alloc_info->rlim_max = (FT_ALLOC_UINT)rlp.rlim_max;
    return (EXIT_SUCCESS);
}

int		ft_alloc_init(void)
{
    if (ft_alloc_init_info() == EXIT_FAILURE)
        return (EXIT_FAILURE);
    g_alloc_state.init = TRUE;
    return (EXIT_SUCCESS);
}