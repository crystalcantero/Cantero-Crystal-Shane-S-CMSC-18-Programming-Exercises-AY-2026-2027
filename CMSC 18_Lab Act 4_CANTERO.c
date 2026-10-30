// CANTERO - M-1L //

#include <stdio.h>

#define TOTAL_STUDENTS 10   // number of students //
#define PASSING_SCORE  60   // passing score //
#define MIN_SCORE      0
#define MAX_SCORE      100

// Clears leftover characters in the input buffer (used after bad input) //
void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard characters //
    }
}

// Asks for ONE score and keeps asking until the input is valid. Returns the valid score, or -1 if the input stream is closed (EOF). //
int getValidScore(int studentNumber) {
    int score;
    int result;

    while (1) {
        printf("Enter the score of Student %d (%d-%d): ",
               studentNumber, MIN_SCORE, MAX_SCORE);

        result = scanf("%d", &score);

        // Error handling 1: input stream closed, cannot continue //
        if (result == EOF) {
            return -1;
        }

        // Error handling 2: input is not a number (letters, symbols, etc.) //
        if (result != 1) {
            printf("Invalid input. Please enter a whole number.\n");
            clearBuffer();
            continue;
        }

        clearBuffer(); // remove the leftover newline //

        // Error handling 3: number is outside the allowed range //
        if (score < MIN_SCORE || score > MAX_SCORE) {
            printf("Score must be between %d and %d.\n", MIN_SCORE, MAX_SCORE);
            continue;
        }

        return score; // valid score //
    }
}

int main(void) {
    int scores[TOTAL_STUDENTS];   // scores of all 10 students //
    int passed[TOTAL_STUDENTS];   // scores of students who passed //
    int failed[TOTAL_STUDENTS];   // scores of students who did not pass //
    int passedID[TOTAL_STUDENTS]; // student numbers of those who passed //
    int failedID[TOTAL_STUDENTS]; // student numbers of those who did not pass //

    int passedCount = 0;
    int failedCount = 0;
    int total = 0;
    int highest, lowest;
    double average;
    int i;

    // --- 1. INPUT: store 10 scores in the array --- //
    for (i = 0; i < TOTAL_STUDENTS; i++) {
        scores[i] = getValidScore(i + 1);

        if (scores[i] == -1) {
            printf("\nInput ended unexpectedly. Program stopped.\n");
            return 1; // exit with error //
        }
    }

    // --- 2. PROCESS: total, highest, lowest, passed/failed --- //
    highest = scores[0];
    lowest  = scores[0];

    for (i = 0; i < TOTAL_STUDENTS; i++) {
        total += scores[i];

        if (scores[i] > highest) highest = scores[i];
        if (scores[i] < lowest)  lowest  = scores[i];

        // Sort each student into the passed or failed array //
        if (scores[i] >= PASSING_SCORE) {
            passed[passedCount]   = scores[i];
            passedID[passedCount] = i + 1;
            passedCount++;
        } else {
            failed[failedCount]   = scores[i];
            failedID[failedCount] = i + 1;
            failedCount++;
        }
    }

    average = (double) total / TOTAL_STUDENTS;

    // --- 3. OUTPUT --- //
    printf("\n===== ALL SCORES ENTERED =====\n");
    for (i = 0; i < TOTAL_STUDENTS; i++) {
        printf("Student %d: %d\n", i + 1, scores[i]);
    }

    printf("\nAverage Score: %.2f\n", average);
    printf("Highest Score: %d\n", highest);
    printf("Lowest Score:  %d\n", lowest);

    printf("\n===== STUDENTS WHO PASSED (%d and above) =====\n", PASSING_SCORE);
    if (passedCount == 0) {
        printf("None\n");
    } else {
        for (i = 0; i < passedCount; i++) {   // traversal of the passed array //
            printf("Student %d: %d\n", passedID[i], passed[i]);
        }
    }

    printf("\n===== STUDENTS WHO DID NOT PASS (below %d) =====\n", PASSING_SCORE);
    if (failedCount == 0) {
        printf("None\n");
    } else {
        for (i = 0; i < failedCount; i++) {   // traversal of the failed array //
            printf("Student %d: %d\n", failedID[i], failed[i]);
        }
    }

    return 0;
}