#include "user.h"

static char meni[] = "<meni>\n";

int
main(void)
{
    char input[16];
    int choice;

    while(1){
        printf("%s", meni);
        gets(input, sizeof(input));
        choice = atoi(input);

        switch(choice){
            case 1:
                printf("Test 1\n");
                break;
            case 2:
                printf("Test 2\n");
                break;
            case 3:
                printf("Test 3\n");
                break;
            case 4:
                printf("Test 4\n");
                break;
            case 5:
                printf("Test 5\n");
                break;
            case 6:
                printf("Test 6\n");
                break;
            case 7:
                exit();
            default:
                printf("Neispravna opcija\n");
        }
    }

}
