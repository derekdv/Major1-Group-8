#include "major1.h"

int main() {
    int option;
    uint32_t number;
    while (1) {
        printf("\nEnter the menu option for the operation to perform:\n");
        printf("\t1. Parity\n");
        printf("\t2. EXIT\n");
        printf("--> ");
        scanf("%d", &option);

        if (option == 2) {
            printf("Program terminating. Goodbye...\n");
            break;
        } else if (option == 1) {
            do {
                printf("Enter a 32-bit number (>= 1 and <= 4294967295, inclusively): ");
                scanf("%u", &number);
            } while (number < 1 || number > 4294967295);

            int result = parity(number);
            printf("Parity of %u is %d\n", number, result);
        } else {
            printf("Error: Invalid option. Please try again.\n");
        }
    }
    return 0;
}
