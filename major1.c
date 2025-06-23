#include "major1.h"

int main() {
    int option;
    uint32_t number, amount;

    while (1) {
        printf("\nEnter the menu option for the operation to perform:\n");
        printf("    1. Rotate-right\n");
        printf("    2. Parity\n");
        printf("    3. EXIT\n");
        printf("--> ");
        scanf("%d", &option);

        if (option == 3) {
            printf("Goodbye.\n");
            break;
        }

        if (option < 1 || option > 3) {
            printf("Invalid option.\n");
            continue;
        }

        do {
            printf("Enter a 32-bit number (>= 1 and <= 4294967295, inclusively): ");
            scanf("%u", &number);
        } while (number < 1 || number > 4294967295);

        if (option == 1) {
            do {
                printf("Enter the number of positions to rotate-right (0–31): ");
                scanf("%u", &amount);
            } while (amount > 31);

            uint32_t result = rotate_right(number, amount);
            printf("%u rotated by %u gives: %u\n", number, amount, result);
        } else if (option == 2) {
            printf("Parity of %u is %s\n", number, parity(number) ? "odd (1)" : "even (0)");
        }
    }

    return 0;
}
