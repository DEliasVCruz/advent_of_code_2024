#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strsplit(char *string, char *delimter, char *buffer[], int size);
bool issafe(char *numbers[], int lineSize, int skip[1]);
void arrreplace(char *numbers[], int lineSize, int removeIdx, char *number);
void arrcopy(char *numbers[], int lineSize, char *copyarr[]);

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
    int skip[1] = {-1};

    isSafe = issafe(strNumbers, lineSize, skip);
    if (isSafe) {
      safeCount++;

      continue;
    }

    char *originalNumbers[10];
    arrcopy(strNumbers, lineSize, originalNumbers);

    char *skipped = strNumbers[skip[0]];
    arrreplace(strNumbers, lineSize, skip[0], NULL);

    isSafe = issafe(strNumbers, lineSize - 1, NULL);
    if (isSafe) {
      safeCount++;

      continue;
    }

    arrreplace(strNumbers, lineSize - 1, skip[0], skipped);

    isSafe = issafe(strNumbers, lineSize - 1, NULL);
    if (isSafe) {
      safeCount++;

      continue;
    }

    if (skip[0] > 0) {
      skip[0] = skip[0] - 1;
    }

    arrreplace(originalNumbers, lineSize, skip[0], NULL);

    isSafe = issafe(originalNumbers, lineSize - 1, NULL);
    if (!isSafe) {
      continue;
    }

    safeCount++;
  }

  fclose(file);

  printf("The safe number: %d\n", safeCount);

  return 0;
}

void arrcopy(char *numbers[], int lineSize, char *copyarr[]) {
  for (int i = 0; i < lineSize; i++) {
    copyarr[i] = numbers[i];
  }
}

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

bool issafe(char *numbers[], int lineSize, int skip[1]) {
  bool isSafe = true;
  int orderState = 0;
  int previousState = 0;

  for (int i = 0; i < lineSize - 1; i++) {
    int first = atoi(numbers[i]);
    int second = atoi(numbers[i + 1]);

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

      if (skip != NULL) {
        skip[0] = i;
      }

      break;
    }

    if (difference < 1 || difference > 3) {
      isSafe = false;

      if (skip != NULL) {
        skip[0] = i;
      }

      break;
    }
  }

  return isSafe;
}

void arrreplace(char *numbers[], int lineSize, int removeIdx, char *number) {
  int size = lineSize;

  if (number == NULL) {
    size = lineSize - 1;
  }

  for (int i = 0; i < size; i++) {
    if (i < removeIdx) {
      numbers[i] = numbers[i];

      continue;
    }

    if (number != NULL && i == removeIdx) {
      numbers[i] = number;

      continue;
    }

    if (number == NULL) {
      numbers[i] = numbers[i + 1];
    } else if (i >= removeIdx) {
      numbers[i] = numbers[i];
    }
  }
}
