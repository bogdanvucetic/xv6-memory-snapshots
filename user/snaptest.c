#include "user.h"
#include "kernel/stat.h"

static char intro[] =
    "-----------------------------------------\n"
    "      TESTIRANJE SNAPSHOT MEHANIZMA      \n";

static char menu[] =
    "-----------------------------------------\n"
    "  1. snap_take()\n"
    "  2. snap_restore()\n"
    "  3. snap_diff()\n"
    "  4. snap_release()\n"
    "  5. snap_status()\n"
    "  6. snap_empty()\n"
    "  7. Promeni test memoriju\n"
    "  8. Prikazi test memoriju\n"
    "  9. Izlazak\n"
    "-----------------------------------------\n"
    "Izaberite opciju: ";

static int
choose_slot()
{
    char input[16];
    printf("Izaberite slot [0-3]: ");
    gets(input, sizeof(input));

    if(input[0] < '0' || input[0] > '9')
        return -1;

    return atoi(input);
}

int
main()
{
    char input[16];
    int choice;
    int helper1, helper2;
    char *testmem = sbrk(4096);
    struct snap_info si;

    printf("%s", intro);

    while(1){
        printf("%s", menu);
        gets(input, sizeof(input));
        choice = atoi(input);

        switch(choice){
            case 1:
                if((helper1 = choose_slot()) == -1){
                    printf("Neispravan unos\n");
                    break;
                }

                printf("Povratna vrednost: %d\n", snap_take(helper1));
                break;
            case 2:
                if((helper1 = choose_slot()) == -1){
                    printf("Neispravan unos\n");
                    break;
                }

                printf("Povratna vrednost: %d\n", snap_restore(helper1));
                break;
            case 3:
                if((helper1 = choose_slot()) == -1){
                    printf("Neispravan unos\n");
                    break;
                }

                if((helper2 = choose_slot()) == -1){
                    printf("Neispravan unos\n");
                    break;
                }

                printf("Povratna vrednost: %d\n", snap_diff(helper1, helper2));
                break;
            case 4:
                if((helper1 = choose_slot()) == -1){
                    printf("Neispravan unos\n");
                    break;
                }

                printf("Povratna vrednost: %d\n", snap_release(helper1));
                break;
            case 5:
                if((helper1 = choose_slot()) == -1){
                    printf("Neispravan unos\n");
                    break;
                }

                helper2 = snap_status(helper1, &si);
                printf("Povratna vrednost: %d\n", helper2);

                if(helper2 == 0)
                    printf("Velicina: %d; broj stranica: %d\n", si.size, si.num_pages);
                break;
            case 6:
                printf("Povratna vrednost: %d\n", snap_empty());
                break;
            case 7:
                printf("Unesite indeks [0-4095]: ");
                gets(input, sizeof(input));
                helper1 = atoi(input);
                if(helper1 < 0 || helper1 >= 4096){
                    printf("Neispravan unos\n");
                    break;
                }
                printf("Unesite karakter: ");
                gets(input, sizeof(input));
                testmem[helper1] = input[0];
                printf("testmem[%d] = %c\n", helper1, testmem[helper1]);
                break;
            case 8:
                if(testmem == 0){
                    printf("Test memorija nije alocirana\n");
                    break;
                }
                printf("Unesite indeks [0-4095]: ");
                gets(input, sizeof(input));
                helper1 = atoi(input);
                if(helper1 < 0 || helper1 >= 4096){
                    printf("Neispravan unos\n");
                    break;
                }
                printf("testmem[%d] = %c (%d)\n", helper1, testmem[helper1], testmem[helper1]);
                break;
            case 9:
                exit();
            default:
                printf("Neispravan unos\n");
        }
    }

    exit();
}
