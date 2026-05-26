#include "defs.h"
#include "stat.h"
#include "proc.h"

int
snap_take(int slot)
{
    pde_t *cpy;
    struct proc *curproc = myproc();
    uint size = curproc->sz;

    if(!(0 <= slot && slot <= 3))
        return -2;

    if(curproc->snaps[slot].used)
        return -3;

	if((cpy = copyuvm(curproc->pgdir, size)) == 0){
		return -1;
	}

	curproc->snaps[slot].pgdir = cpy;
	curproc->snaps[slot].size = size;
	curproc->snaps[slot].used = 1;

	return 0;
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
