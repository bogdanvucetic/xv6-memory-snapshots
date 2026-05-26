#include "user.h"
#include "kernel/stat.h"

static char menu[] = "<meni>\n";

int
main(void)
{
    char input[16];
    int choice;
    struct snap_info si;

    while(1){
        printf("%s", menu);
        gets(input, sizeof(input));
        choice = atoi(input);

        switch(choice){
            case 1:
                printf("Test 1\n");
                printf("%d\n", snap_take(0));
                break;
            case 2:
                printf("Test 2\n");
                printf("%d\n", snap_restore(0));
                break;
            case 3:
                printf("Test 3\n");
                printf("%d\n", snap_diff(0, 1));
                break;
            case 4:
                printf("Test 4\n");
                printf("%d\n", snap_release(0));
                break;
            case 5:
                printf("Test 5\n");
                printf("%d\n", snap_status(0, &si));
                break;
            case 6:
                printf("Test 6\n");
                printf("%d\n", snap_empty());
                break;
            case 7:
                exit();
            default:
                printf("Neispravna opcija\n");
        }
    }

    exit();
}
