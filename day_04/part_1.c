#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shforward(int curx, int len, char *bline);
int shbackward(int curx, char *bline);
int svbackward(int cury, int curx, char *buffer[140]);
int svforward(int cury, int curx, char *buffer[140]);
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

  for (int cury = 0; cury < 140; cury++) {

    int len = strlen(buffer[cury]);

    for (int curx = 0; curx < len; curx++) {

      // char comb[3] = {0, 0, 0};
      // char combBuf[2] = {0, 0};

      // char mBuf = 0;

      // bool hasMBefore = false;

      if (strncmp(&buffer[cury][curx], "X", 1) != 0) {
        // printf(".");

        continue;
      }

      total = total + shforward(curx, len, buffer[cury]);
      total = total + shbackward(curx, buffer[cury]);
      total = total + svforward(cury, curx, buffer);
      total = total + svbackward(cury, curx, buffer);

      total = total + sduforward(cury, curx, len, buffer);
      total = total + sddforward(cury, curx, len, buffer);
      total = total + sdubackward(cury, curx, len, buffer);
      total = total + sddbackward(cury, curx, len, buffer);

      // printf("%c", buffer[cury][curx]);
      // for (int i = curx + 1; i < len; i++) {
      //   if (strncmp(&buffer[cury][i], "M", 1) == 0) {
      //     hasMBefore = true;

      //     mBuf++;
      //   }

      //   if (strncmp(&buffer[cury][i], "A", 1) == 0 && hasMBefore) {

      //     combBuf[0] = combBuf[0] + mBuf;
      //     combBuf[1] = combBuf[1] + 1;

      //     mBuf = 0;
      //   }

      //   if (strncmp(&buffer[cury][i], "S", 1) == 0 && combBuf[0] != 0 &&
      //       combBuf[1] != 0) {

      //     comb[0] = comb[0] + combBuf[0];
      //     comb[1] = comb[1] + combBuf[1];
      //     comb[2] = comb[2] + 1;

      //     combBuf[0] = 0;
      //     combBuf[1] = 0;
      //   }
      // }

      // int count = comb[0] * comb[1] * comb[2];

      // total = total + count;
    }

    // printf("\n");
  }

  printf("The total is %d\n", total);

  return 0;
}

int shbackward(int curx, char *bline) {
  if (curx < 3) {
    return 0;
  }

  int hasM = strncmp(&bline[curx - 1], "M", 1);
  int hasA = strncmp(&bline[curx - 2], "A", 1);
  int hasX = strncmp(&bline[curx - 3], "S", 1);

  if (hasM == 0 && hasA == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}

int shforward(int curx, int len, char *bline) {
  if (curx > len - 4) {
    return 0;
  }

  int hasM = strncmp(&bline[curx + 1], "M", 1);
  int hasA = strncmp(&bline[curx + 2], "A", 1);
  int hasX = strncmp(&bline[curx + 3], "S", 1);

  if (hasM == 0 && hasA == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}

int svforward(int cury, int curx, char *buffer[140]) {
  if (cury < 3) {
    return 0;
  }

  int hasM = strncmp(&buffer[cury - 1][curx], "M", 1);
  int hasA = strncmp(&buffer[cury - 2][curx], "A", 1);
  int hasX = strncmp(&buffer[cury - 3][curx], "S", 1);

  if (hasM == 0 && hasA == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}

int svbackward(int cury, int curx, char *buffer[140]) {
  if (cury > 136) {
    return 0;
  }

  int hasM = strncmp(&buffer[cury + 1][curx], "M", 1);
  int hasA = strncmp(&buffer[cury + 2][curx], "A", 1);
  int hasX = strncmp(&buffer[cury + 3][curx], "S", 1);

  if (hasM == 0 && hasA == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}

int sduforward(int cury, int curx, int len, char *buffer[140]) {
  if (cury < 3 || curx > len - 4) {
    return 0;
  }

  int hasM = strncmp(&buffer[cury - 1][curx + 1], "M", 1);
  int hasA = strncmp(&buffer[cury - 2][curx + 2], "A", 1);
  int hasX = strncmp(&buffer[cury - 3][curx + 3], "S", 1);

  if (hasM == 0 && hasA == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}

int sddforward(int cury, int curx, int len, char *buffer[140]) {
  if (cury > 136 || curx > len - 4) {
    return 0;
  }

  int hasM = strncmp(&buffer[cury + 1][curx + 1], "M", 1);
  int hasA = strncmp(&buffer[cury + 2][curx + 2], "A", 1);
  int hasX = strncmp(&buffer[cury + 3][curx + 3], "S", 1);

  if (hasM == 0 && hasA == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}

int sdubackward(int cury, int curx, int len, char *buffer[140]) {
  if (cury < 3 || curx < 3) {
    return 0;
  }

  int hasM = strncmp(&buffer[cury - 1][curx - 1], "M", 1);
  int hasA = strncmp(&buffer[cury - 2][curx - 2], "A", 1);
  int hasX = strncmp(&buffer[cury - 3][curx - 3], "S", 1);

  if (hasM == 0 && hasA == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}

int sddbackward(int cury, int curx, int len, char *buffer[140]) {
  if (cury > 136 || curx < 3) {
    return 0;
  }

  int hasM = strncmp(&buffer[cury + 1][curx - 1], "M", 1);
  int hasA = strncmp(&buffer[cury + 2][curx - 2], "A", 1);
  int hasX = strncmp(&buffer[cury + 3][curx - 3], "S", 1);

  if (hasM == 0 && hasA == 0 && hasX == 0) {
    return 1;
  }

  return 0;
}
