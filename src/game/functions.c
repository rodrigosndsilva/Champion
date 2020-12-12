#include "functions.h"

void shutdown() {
  char PIPE[PATH_MAX];

  sprintf(PIPE, "../src/game/Game-> %d", getpid());
  unlink(PIPE);
  printf("Game-> %d terminated\n", getpid());
  pthread_kill(pthread_self(), SIGINT);
  exit(0);
}

void serverShutdown() {
  char PIPE[PATH_MAX];
  sprintf(PIPE, "../src/game/Game-> %d", getpid());
  unlink(PIPE);
  printf("Game-> %d terminated\n", getpid());
  pthread_kill(pthread_self(), SIGINT);
  exit(0);
}

void creatingGamePipe() {
  char PIPE[PATH_MAX];
  sprintf(PIPE, "../src/game/Game-> %d", getpid());
  if (mkfifo(PIPE, S_IRWXU) < 0) { // cria o pipe
    printf("Error creating FIFO of Game. Leaving...\n");
    shutdown();
  }
  int fd = open(REFEREE_PIPE, O_WRONLY);
  if (fd == -1) {
    printf("Error opening FIFO of Referee. Leaving...\n");
    shutdown();
  }
  t.action = GAMEPID;
  t.g.pid = getpid();
  write(fd, &t, sizeof(t));
  close(fd);
}

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

void *receiver() {
  Tournment receive;
  int fd_receive, fd_send;
  char PIPE[PATH_MAX];

  fd_send = open(REFEREE_PIPE, O_WRONLY);
  if (fd_send == -1) {
    printf("Error opening FIFO of Referee. Leaving...\n");
    shutdown();
  }

  sprintf(PIPE, "../src/game/Game-> %d", getpid());
  fd_receive = open(PIPE, O_RDONLY);

  if (fd_receive == -1) {
    printf("Error opening FIFO of Game. Leaving...\n");
    shutdown();
  }

  do {
    read(fd_receive, &receive, sizeof(receive));

    switch (receive.action) {
    case SERVER_SHUTDOWN: // SERVIDOR TERMINOU
      printf("The server has been shut down!\n");
      serverShutdown();
      break;
    }
  } while (1);
}
