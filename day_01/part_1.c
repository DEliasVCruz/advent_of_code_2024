#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE* file = fopen("./input.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "There was an error opening the file\n");

        exit(1);
    }

    char line[14];

    int leftNumbers[1000];
    int rightNumbers[1000];

    int idx = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            continue;
        }

        char *leftNumber, *rightNumber;

        leftNumber = strtok(line, "   ");
        rightNumber = strtok(NULL, "   ");

        leftNumbers[idx] = atoi(leftNumber);
        rightNumbers[idx] = atoi(rightNumber);

        idx++;
    }
    
    fclose(file);

    for (int step = 0; step < 1000; step++) {
        for (int elemIdx = 0; elemIdx < (1000 - 1 - step); elemIdx++) {
            if (leftNumbers[elemIdx] <= leftNumbers[elemIdx+1]) {
                continue;
            }

            int tempElem = leftNumbers[elemIdx];
            leftNumbers[elemIdx] = leftNumbers[elemIdx+1];
            leftNumbers[elemIdx+1] = tempElem;
        }
    }
    
    for (int step = 0; step < 1000; step++) {
        for (int elemIdx = 0; elemIdx < (1000 - 1 - step); elemIdx++) {
            if (rightNumbers[elemIdx] <= rightNumbers[elemIdx+1]) {
                continue;
            }

            int tempElem = rightNumbers[elemIdx];
            rightNumbers[elemIdx] = rightNumbers[elemIdx+1];
            rightNumbers[elemIdx+1] = tempElem;
        }
    }

    int totalDifference = 0;

    for (idx = 0; idx < 1000; idx++) {
        int difference;
        int left = leftNumbers[idx];
        int right = rightNumbers[idx];

        if (left < right) {
            difference = right - left;
        } else {
            difference = left - right;
        }
        
        totalDifference = totalDifference + difference;
    }

    printf("The difference %d\n", totalDifference);

    return 0;
}