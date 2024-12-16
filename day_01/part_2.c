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

    int similarityFactors[1000];

    for (int leftIdx = 0; leftIdx < 1000; leftIdx++) {
        similarityFactors[leftIdx] = 0;

        for (int rightIdx = 0; rightIdx < 1000; rightIdx++) {
            if (leftNumbers[leftIdx] == rightNumbers[rightIdx]) {
                similarityFactors[leftIdx]++;
            }
        }
    }

    int totalSimilarities = 0;
    for (int idx = 0; idx < 1000; idx++) {
        totalSimilarities = totalSimilarities + (similarityFactors[idx] * leftNumbers[idx]);
    }

    printf("The difference %d\n", totalSimilarities);

    return 0;
}