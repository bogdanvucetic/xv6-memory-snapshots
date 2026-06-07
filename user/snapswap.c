#include "user.h"

int
main()
{
    int va = 55;
    printf("Ispis nakon promena: %d\n", snap_swap_pages(0, 1, va));
    exit();
}
