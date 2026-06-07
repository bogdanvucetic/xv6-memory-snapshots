#include "user.h"

int
main()
{
    int slot = 0;

    if (snap_take(slot) != 0)
        printf("Neuspesno pravljenje snapshot-a");

    printf("Broj rdonly stranica: %d\n", snap_count_readonly(slot));
    exit();
}
