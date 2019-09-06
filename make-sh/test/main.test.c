#include <sys/time.h> 
#include <sys/resource.h>
#include <unistd.h>
# include "string.h"

# include "./src/test.h"

int main(void) 
{
    printf("\n\n===== Test Start =====\n\n");

    t_block *base = malloc(32);
    t_block *b = base;
    t_block *start = NULL;


    // printf("%p - %p", base, b);

 test_malloc();

  

//    struct rlimit rlp;
//    getrlimit(RLIMIT_MEMLOCK, &rlp);

//    printf("souple %ld - max %ld \n", rlp.rlim_cur, rlp.rlim_max);

    printf("\n\n===== Test End =====\n\n");
    return 0;
}
