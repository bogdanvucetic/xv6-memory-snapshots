#include "stat.h"

int
snap_take(int slot)
{
    return 1;
}

int
snap_restore(int slot)
{
    return 2;
}

int
snap_diff(int slot1, int slot2)
{
    return 3;
}

int
snap_release(int slot)
{
    return 4;
}

int
snap_status(int slot, struct snap_info *si)
{
    return 5;
}

int
snap_empty(void)
{
    return 6;
}
