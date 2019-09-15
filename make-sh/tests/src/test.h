#ifndef FT_TEST_H
# define FT_TEST_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> 
# include <sys/resource.h>
# include <stdint.h>
# include <sys/mman.h>

# include "../../../liballoc.h"

typedef struct s_block
{
  size_t  data;
  struct s_block *next;
  struct s_block *prev;
}               t_block;

void    test_malloc(void);
void hexDump(char *desc, void *addr, int len) ;
#endif


