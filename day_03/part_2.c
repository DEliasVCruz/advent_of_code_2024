#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int result;
  int state;
} mulres;

int mulengine(char *input, int state, char *first, char *second);
int dontEngine(char *input, int state);
int doEngine(char *input, int state);

bool arrincludes(char *arr[], int len, char *value);

mulres mulmachine(char *input, int state, char *first, char *second);

char *numbers[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

int main() {
  FILE *file = fopen("./input.txt", "r");

  if (file == NULL) {
    fprintf(stderr, "There was a problem opening the file\n");

    exit(1);
  }

  char line[3480];
  unsigned long long total = 0;
  bool mulOn = true;

  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
      continue;
    }

    int charPos = 0;
    char input = line[charPos];

    int mulState = 0;
    int doState = 0;
    int dontState = 0;

    char firstStrNumber[4] = "";
    char secondStrNumber[4] = "";

    while (input != '\0') {
      if (mulOn) {
        dontState = dontEngine(&input, dontState);

        if (dontState == 7) {
          mulOn = false;

          doState = 0;

          charPos++;
          input = line[charPos];

          continue;
        }

        if (dontState == 0) {
          dontState = dontEngine(&input, dontState);
        }

        mulres mulRes =
            mulmachine(&input, mulState, firstStrNumber, secondStrNumber);

        total = total + mulRes.result;
        mulState = mulRes.state;
      } else {
        doState = doEngine(&input, doState);

        if (doState == 4) {
          mulOn = true;

          dontState = 0;
          mulState = 0;

          firstStrNumber[0] = '\0';
          secondStrNumber[0] = '\0';
        }

        if (doState == 0) {
          doState = doEngine(&input, doState);
        }
      }

      charPos++;
      input = line[charPos];
    }
  }

  printf("The total is %llu\n", total);

  return 0;
}

mulres mulmachine(char *input, int state, char *first, char *second) {
  mulres res;

  res.state = mulengine(input, state, first, second);
  res.result = 0;
  // printf("The state right afeter %d\n", state);

  if (res.state == 12) {
    res.result = (atoi(first) * atoi(second));

    res.state = 0;
    first[0] = '\0';
    second[0] = '\0';

    return res;
  }

  if (res.state == 0) {
    first[0] = '\0';
    second[0] = '\0';

    res.state = mulengine(input, state, first, second);
  }

  return res;
}

bool arrincludes(char *arr[], int len, char *value) {
  for (int i = 0; i < len; i++) {
    if (strncmp(arr[i], value, 1) == 0) {
      return true;
    }
  }

  return false;
}

int doEngine(char *input, int state) {
  if (state == 0 && (strncmp(input, "d", 1) == 0)) {
    return 1;
  }

  if (state == 1 && (strncmp(input, "o", 1) == 0)) {
    return 2;
  }

  if (state == 2 && (strncmp(input, "(", 1) == 0)) {
    return 3;
  }

  if (state == 3 && (strncmp(input, ")", 1) == 0)) {
    return 4;
  }

  return 0;
}

int dontEngine(char *input, int state) {
  if (state == 0 && (strncmp(input, "d", 1) == 0)) {
    return 1;
  }

  if (state == 1 && (strncmp(input, "o", 1) == 0)) {
    return 2;
  }

  if (state == 2 && (strncmp(input, "n", 1) == 0)) {
    return 3;
  }

  if (state == 3 && (strncmp(input, "'", 1) == 0)) {
    return 4;
  }

  if (state == 4 && (strncmp(input, "t", 1) == 0)) {
    return 5;
  }

  if (state == 5 && (strncmp(input, "(", 1) == 0)) {
    return 6;
  }

  if (state == 6 && (strncmp(input, ")", 1) == 0)) {
    return 7;
  }

  return 0;
}

int mulengine(char *input, int state, char *first, char *second) {
  // printf("This is the input inside %s\n", input);
  // printf("The state inside %d\n", state);
  if (state == 0 && (strncmp(input, "m", 1) == 0)) {
    // printf("We return here\n");
    return 1;
  }

  if (state == 1 && (strncmp(input, "u", 1) == 0)) {
    return 2;
  }

  if (state == 2 && (strncmp(input, "l", 1) == 0)) {
    return 3;
  }

  if (state == 3 && (strncmp(input, "(", 1) == 0)) {
    return 4;
  }

  if (state == 4 && arrincludes(numbers, 10, input)) {
    // printf("We are concating 1 of 1\n");
    strncat(first, input, 1);

    return 5;
  }

  if (state == 5 && arrincludes(numbers, 10, input)) {
    // printf("We are concating 2 of 1\n");
    strncat(first, input, 1);

    return 6;
  }

  if (state == 6 && arrincludes(numbers, 10, input)) {
    // printf("We are concating 3 of 1\n");
    strncat(first, input, 1);

    return 7;
  }

  if ((state == 5 || state == 6 || state == 7) &&
      (strncmp(input, ",", 1) == 0)) {
    return 8;
  }

  if (state == 8 && arrincludes(numbers, 10, input)) {
    // printf("We are concating 1 of 2\n");
    strncat(second, input, 1);

    return 9;
  }

  if (state == 9 && arrincludes(numbers, 10, input)) {
    // printf("We are concating 2 of 2\n");
    strncat(second, input, 1);

    return 10;
  }

  if (state == 10 && arrincludes(numbers, 10, input)) {
    // printf("We are concating 3 of 2\n");
    strncat(second, input, 1);

    return 11;
  }

  if ((state == 9 || state == 10 || state == 11) &&
      (strncmp(input, ")", 1) == 0)) {
    // printf("We have the full thing\n");
    return 12;
  }

  return 0;
}
