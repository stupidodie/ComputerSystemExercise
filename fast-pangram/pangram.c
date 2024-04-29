#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool ispangram(char *s) {
  uint32_t bs = 0;
  char c;
  while ((c = *s++) != '\0') {
    if (c < '@')
      continue;
    bs |= 1 << (c & 0x1f);
  }
  return (bs & 0x07fffffe) == 0x07fffffe;
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
