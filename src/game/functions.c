#include "functions.h"

Tournment readFile(Tournment t) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int aux = 1;
  t.g.cont = 0;

  fp = fopen("../src/game/questions.txt", "r");
  if (fp == NULL) {
    perror("Error opening File\n");
    exit(EXIT_FAILURE);
  }

  while ((read = getline(&line, &len, fp)) != -1) {
    // remoção do \n para que na comparação dê certo
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[--len] = '\0';
    }
    if (aux % 2 == 0) {
      strcpy(t.g.qanda[t.g.cont].answer, line);
      aux++;
      t.g.cont++;
    } else {
      strcpy(t.g.qanda[t.g.cont].question, line);
      aux++;
    }
  }

  fclose(fp);
  if (line)
    free(line);
  else
    exit(EXIT_SUCCESS);
  return t;
}

void printQandA(Tournment t) {
  for (int i = 0; i < t.g.cont; i++) {
    printf("Question: %s\nAnswer: %s\n", t.g.qanda[i].question,
           t.g.qanda[i].answer);
  }
}

Tournment runGame(Tournment t) {
  char str[20];
  for (int i = 0; i < t.g.cont; i++) {
    printf("Question: %s\n", t.g.qanda[i].question);
    printf("Answer: ");
    scanf("%20[^\n]", str);
    if (strcmp(t.g.qanda[i].answer, str) == 0) {
      printf("The answer: %s is right!\n\n", str);
    } else {
      printf("The answer: %s is wrong! The answer is: %s\n\n", str,
             t.g.qanda[i].answer);
    }
    // limpa buffer
    scanf("%*[^\n]");
    scanf("%*c");
  }
  return t;
}