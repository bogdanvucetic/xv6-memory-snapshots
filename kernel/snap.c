#include "defs.h"
#include "stat.h"
#include "proc.h"
#include "param.h"

int
snap_take(int slot)
{
    pde_t *cpy;
    struct proc *curproc = myproc();
    uint size = curproc->sz;

    if(slot < 0 || slot >= NSNAP)
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
    struct proc *curproc = myproc();

    if(slot < 0 || slot >= NSNAP)
        return -2;

    if(!(curproc->snaps[slot].used))
        return -1;

    freevm(curproc->snaps[slot].pgdir);

    curproc->snaps[slot].pgdir = 0;
    curproc->snaps[slot].size = 0;
    curproc->snaps[slot].used = 0;

    return 0;
}

int
snap_status(int slot, struct snap_info *si)
{
    return 5;
}

int
snap_empty(void)
{
    struct proc *curproc = myproc();

    for(int i = 0; i < NSNAP; i++)
        if (!(curproc->snaps[i].used))
            return i;

    return -1;
}
