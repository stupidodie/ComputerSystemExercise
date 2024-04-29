#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool ispangram(char *s) {
  int counter = 0;
  int count[26] = {0};
  unsigned long size = strlen(s);
  for (unsigned long i = 0; i < size; i++) {
    if (s[i] >= 97 && s[i] <= 122) {
      int c = s[i] - 97;
      if (count[c] == 0) {
        counter++;
        if (counter == 26) {
          return true;
        }
      }
      count[c]++;
    } else if (s[i] >= 65 && s[i] <= 90) {
      int c = s[i] - 65;
      if (count[c] == 0) {
        counter++;
        if (counter == 26) {
          return true;
        }
      }
      count[c]++;
    }
  }
  return false;
}

int main() {
  size_t len;
  ssize_t read;
  char *line = NULL;
  while ((read = getline(&line, &len, stdin)) != -1) {
    if (ispangram(line))
      printf("%s", line);
  }

  if (ferror(stdin))
    fprintf(stderr, "Error reading from stdin");

  free(line);
  fprintf(stderr, "ok\n");
}
