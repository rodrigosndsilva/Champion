#include "functions.h"

void readFile() {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen("questions.txt", "r");
  if (fp == NULL) {
    printf("Error openning File\n");
    exit(EXIT_FAILURE);
  }

  while ((read = getline(&line, &len, fp)) != -1) {
    printf("Retrieved line of length %zu:\n", read);
    printf("%s", line);
  }
  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
}