#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strsplit(char *string, char *delimter, char *buffer[], int size) {
  int written = 0;
  for (int i = 0; i < size; i++) {
    char *stringValue;

    if (i == 0) {
      stringValue = string;
    } else {
      stringValue = NULL;
    }

    char *value = strtok(stringValue, delimter);
    if (value == NULL) {
      continue;
    }

    buffer[i] = value;

    written++;
  }

  return written;
}

int main() {
  FILE *file = fopen("./input.txt", "r");

  if (file == NULL) {
    fprintf(stderr, "There was a problem openning the file\n");

    exit(1);
  }

  char line[30];
  int safeCount = 0;
  char *strNumbers[10];

  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
      continue;
    }

    int lineSize = strsplit(line, " ", strNumbers, 10);

    if (lineSize == 0) {
      continue;
    }

    bool isSafe = true;
    int orderState = 0;
    int previousState = 0;

    for (int i = 0; i < lineSize - 1; i++) {
      int first = atoi(strNumbers[i]);

      int second = atoi(strNumbers[i + 1]);

      int difference;
      if (first < second) {
        difference = second - first;
        previousState = orderState;
        orderState = 1;
      } else {
        difference = first - second;
        previousState = orderState;
        orderState = 2;
      }

      if (previousState != 0 && (previousState != orderState)) {
        isSafe = false;
        break;
      }

      if (difference < 1 || difference > 3) {
        isSafe = false;
        break;
      }
    }

    if (!isSafe) {
      continue;
    }

    safeCount++;
  }

  fclose(file);

  printf("The safe number: %d\n", safeCount);

  return 0;
}
