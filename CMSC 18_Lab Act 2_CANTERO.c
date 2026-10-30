#include <stdio.h>

int main() {
    // 1. Fix the errors and rename any technically legal but unconventional variavle names.
 
    int count = 5;
    float my_variable = 3.14;
    char letter = 'a';
    int value = 10;
    char dollars = 'H';
    int number = 100;

    // 2. Print all previous data into one string in Mad Lib.

    printf("My Mad Lib: I have %d items, a value of %.2f, and the letter %c."" My number is %d, my special character is %c, and another value is %d.\n\n", count, my_variable, letter, value, dollars, number);

    // 3. Initialize a string variable, assign a value to that variable through user input, and output the value in the console.

    char user_input[100];

    printf("Enter a word for the Mad Lib: ");
    fgets(user_input, sizeof(user_input), stdin);

    printf("You entered %s", user_input);
    
    
    return 0;
}
