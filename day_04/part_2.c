#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sduforward(int cury, int curx, int len, char *buffer[140]);
int sddforward(int cury, int curx, int len, char *buffer[140]);
int sdubackward(int cury, int curx, int len, char *buffer[140]);
int sddbackward(int cury, int curx, int len, char *buffer[140]);

int main() {
  FILE *file = fopen("./input.txt", "r");

  if (file == NULL) {
    fprintf(stderr, "There was a problem opening the file\n");

    exit(1);
  }

  char line[142];
  char *buffer[140];

  int bufferIdx = 0;
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
      continue;
    }

    buffer[bufferIdx] = strdup(line);
    bufferIdx++;
  }

  int total = 0;

  for (int cury = 1; cury < 139; cury++) {

    int len = strlen(buffer[cury]);

    for (int curx = 1; curx < len - 1; curx++) {

      if (strncmp(&buffer[cury][curx], "A", 1) != 0) {
        continue;
      }

      int temp = sduforward(cury, curx, len, buffer);
      temp = temp + sddforward(cury, curx, len, buffer);
      temp = temp + sdubackward(cury, curx, len, buffer);
      temp = temp + sddbackward(cury, curx, len, buffer);

      if (temp < 2) {
        continue;
      }

      total++;
    }
  }

  printf("The total is %d\n", total);

  return 0;
}

int sduforward(int cury, int curx, int len, char *buffer[140]) {
  int hasM = strncmp(&buffer[cury - 1][curx - 1], "M", 1);
  int hasX = strncmp(&buffer[cury + 1][curx + 1], "S", 1);

  if (hasM == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}

int sddforward(int cury, int curx, int len, char *buffer[140]) {
  int hasM = strncmp(&buffer[cury + 1][curx - 1], "M", 1);
  int hasX = strncmp(&buffer[cury - 1][curx + 1], "S", 1);

  if (hasM == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}

int sdubackward(int cury, int curx, int len, char *buffer[140]) {
  int hasM = strncmp(&buffer[cury - 1][curx + 1], "M", 1);
  int hasX = strncmp(&buffer[cury + 1][curx - 1], "S", 1);

  if (hasM == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}

int sddbackward(int cury, int curx, int len, char *buffer[140]) {
  int hasM = strncmp(&buffer[cury + 1][curx + 1], "M", 1);
  int hasX = strncmp(&buffer[cury - 1][curx - 1], "S", 1);

  if (hasM == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}
