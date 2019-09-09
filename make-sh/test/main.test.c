#include <sys/time.h> 
#include <sys/resource.h>
#include <unistd.h>
# include "string.h"

# include "./src/test.h"

int main(void) 
{
    printf("\n\n===== Test Start =====\n\n");

     test_malloc();

    printf("\n\n===== Test End =====\n\n");
    return 0;
}
