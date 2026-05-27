#include "defs.h"
#include "mmu.h"
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

	if((cpy = copyuvm(curproc->pgdir, size)) == 0)
		return -1;

	curproc->snaps[slot].pgdir = cpy;
	curproc->snaps[slot].size = size;
	curproc->snaps[slot].used = 1;

	return 0;
}

int
snap_restore(int slot)
{
    pde_t *cpy, *old;
    struct proc *curproc = myproc();

    if(slot < 0 || slot >= NSNAP)
        return -2;

    if(!(curproc->snaps[slot].used))
        return -1;

    if((cpy = copyuvm(curproc->snaps[slot].pgdir, curproc->snaps[slot].size)) == 0)
		return -3;

    old = curproc->pgdir;

    curproc->pgdir = cpy;
    curproc->sz = curproc->snaps[slot].size;

    switchuvm(curproc);
    freevm(old);

    return 0;
}

int
snap_diff(int slot1, int slot2)
{
    pde_t *pgdir1, *pgdir2;
    struct proc *curproc = myproc();
    int count;

    if((slot1 < 0 || slot1 >= NSNAP) || (slot2 < 0 || slot2 >= NSNAP))
        return -2;

    if(!curproc->snaps[slot1].used || !curproc->snaps[slot2].used)
        return -1;

    pgdir1 = curproc->snaps[slot1].pgdir;
    pgdir2 = curproc->snaps[slot2].pgdir;

    count = cmppages(pgdir1, pgdir2, curproc->snaps[slot1].size, curproc->snaps[slot2].size);

    return count;
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
    struct proc *curproc = myproc();
    int cursize;

    if(slot < 0 || slot >= NSNAP)
        return -2;

    if(!(curproc->snaps[slot].used))
        return -1;

    cursize = curproc->snaps[slot].size;

    si->size = cursize;
    si->num_pages = PGROUNDUP(cursize) / PGSIZE;

    return 0;
}

int
snap_empty(void)
{
    struct proc *curproc = myproc();

    for(int i = 0; i < NSNAP; i++)
        if(!(curproc->snaps[i].used))
            return i;

    return -1;
}
