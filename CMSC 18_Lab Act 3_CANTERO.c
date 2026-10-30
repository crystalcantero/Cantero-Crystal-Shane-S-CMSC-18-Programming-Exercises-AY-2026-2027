// CANTERO - M-1L //
/* ============================================================
    G R O C E R Y   G U R U   -   Point of Sale Terminal
     "Ringing up your groceries, one discount at a time!"
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Clears leftover characters in the input buffer after a bad scanf() read, so the program doesn't get stuck in a loop. //
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard //
    }
}

int main(void) {
    // Variable that stores the running total cost of the customer's groceries. Starts at zero and gets updated every time an item is added. //
    float total_cost = 0;

    char product_name[100];
    int quantity;
    float price;
    char more_items;
    int customer_status;
    char status_label[30];
    float discount_amount = 0;
    float final_total;

    printf("==================================================\n");
    printf("   WELCOME TO GROCERY GURU POINT OF SALE SYSTEM\n");
    printf("==================================================\n");

    /* ------------------------------------------------------------
       STEP 1: Repeatedly ask for products until the clerk is done
       ------------------------------------------------------------ */
    do {
        // Ask for the product name. Keep asking if left blank. //
        do {
            printf("\nEnter product name: ");
            fgets(product_name, sizeof(product_name), stdin);
            // Remove the trailing newline character fgets() keeps. //
            product_name[strcspn(product_name, "\n")] = '\0';

            if (strlen(product_name) == 0) {
                printf("Product name cannot be empty. Please try again.\n");
            }
        } while (strlen(product_name) == 0);

        // Ask for the quantity being purchased, with error handling in case the clerk types something that isn't a whole number. //
        int validQty = 0;
        do {
            printf("Enter quantity of %s: ", product_name);
            if (scanf("%d", &quantity) != 1) {
                printf("Invalid input. Please enter a whole number (e.g., 3).\n");
                clearInputBuffer();
            } else if (quantity <= 0) {
                printf("Quantity must be a positive whole number.\n");
                clearInputBuffer();
            } else {
                validQty = 1;
                clearInputBuffer();
            }
        } while (!validQty);

        // Ask for the price of a single unit of the product, with error handling in case the clerk types something that isn't a number. //
        int validPrice = 0;
        do {
            printf("Enter price of %s: ", product_name);
            if (scanf("%f", &price) != 1) {
                printf("Invalid input. Please enter a valid number (e.g., 25.50).\n");
                clearInputBuffer();
            } else if (price < 0) {
                printf("Price cannot be negative.\n");
                clearInputBuffer();
            } else {
                validPrice = 1;
                clearInputBuffer();
            }
        } while (!validPrice);

        // Update the customer's total cost based on price and quantity. //
        total_cost += price * quantity;
        printf("Added: %d x %s @ %.2f each\n", quantity, product_name, price);

        // Ask the clerk if there are more items for this customer. //
        int validAnswer = 0;
        do {
            printf("\nAdd another item? (Y/N): ");
            scanf(" %c", &more_items);
            clearInputBuffer();
            more_items = (char) toupper((unsigned char) more_items);
            if (more_items == 'Y' || more_items == 'N') {
                validAnswer = 1;
            } else {
                printf("Please enter Y or N.\n");
            }
        } while (!validAnswer);

    } while (more_items == 'Y');

    /* ------------------------------------------------------------
       STEP 2: Ask about the customer's status for discount purposes
       ------------------------------------------------------------ */
    printf("\nCustomer status options:\n");
    printf("  1 - PWD (Person with Disability)\n");
    printf("  2 - Senior Citizen\n");
    printf("  3 - Pregnant\n");
    printf("  4 - None of the above\n");

    int validStatus = 0;
    do {
        printf("Select customer status (1-4): ");
        if (scanf("%d", &customer_status) != 1) {
            printf("Invalid input. Please enter a number from 1 to 4.\n");
            clearInputBuffer();
        } else if (customer_status < 1 || customer_status > 4) {
            printf("Please enter a number from 1 to 4.\n");
            clearInputBuffer();
        } else {
            validStatus = 1;
            clearInputBuffer();
        }
    } while (!validStatus);

    /* ------------------------------------------------------------
       STEP 3: Apply the discount based on the customer's status
       ------------------------------------------------------------ */
    switch (customer_status) {
        case 1:
            strcpy(status_label, "PWD");
            discount_amount = total_cost * 0.05f;   // 5% discount //
            break;
        case 2:
            strcpy(status_label, "Senior Citizen");
            discount_amount = total_cost * 0.20f;   // 20% discount //
            break;
        case 3:
            strcpy(status_label, "Pregnant");
            discount_amount = 30.00f;               // flat P30.00 discount //
            // Make sure the flat discount never makes the total negative. //
            if (discount_amount > total_cost) {
                discount_amount = total_cost;
            }
            break;
        default:
            strcpy(status_label, "None of the above");
            discount_amount = 0;                    // no discount //
            break;
    }

    final_total = total_cost - discount_amount;

    /* ------------------------------------------------------------
       STEP 4: Output the receipt (customer status and total cost)
       ------------------------------------------------------------ */
    printf("\n==================================================\n");
    printf("                    RECEIPT\n");
    printf("==================================================\n");
    printf("Customer Status : %s\n", status_label);
    printf("Subtotal        : %.2f\n", total_cost);
    printf("Discount Applied: %.2f\n", discount_amount);
    printf("TOTAL TO PAY    : %.2f\n", final_total);
    printf("==================================================\n");
    printf(   "Thank you for shopping with Grocery Guru!\n");
    printf("==================================================\n");

    return 0;
}