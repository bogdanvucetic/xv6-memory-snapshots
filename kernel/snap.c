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

/*
 * Vraćanje memorije procesa na stanje sačuvano u nekom od slotova vrši se
 * sistemskim pozivom snap_restore(int slot). Tokom ove operacije, trenutna
 * tabela stranica i fizička memorija procesa se potpuno oslobađaju, a
 * zamenjuju se kopijom onoga što se nalazi u slotu. Od velike je važnosti da
 * snap_restore ne uništi sadržaj u slotu, kako bi se isti snimak mogao
 * koristiti za višestruka vraćanja stanja.
 *
 * int snap_restore(int slot)
 Vraća memoriju procesa na stanje sačuvano u navedenom slotu. Trenutna
 tabela stranica i sve fizičke stranice procesa se oslobađaju, a proces preuzima
 kopiju memorije iz slota. Povratne vrednosti:
 0: Uspešna restauracija
 -1: Slot je prazan
 -2: Nevalidan broj slota (van opsega 0–3)
 -3: Ostale greške
 */

int
snap_restore(int slot)
{
    pde_t *cpy, *old;
    struct proc *curproc = myproc();

    if(slot < 0 || slot >= NSNAP)
        return -2;

    if(!(curproc->snaps[slot].used))
        return -1;

    if((cpy = copyuvm(curproc->snaps[slot].pgdir, curproc->snaps[slot].size)) == 0){
		return -3;
	}

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
        if(!(curproc->snaps[i].used))
            return i;

    return -1;
}
