#include "functions.h"

void SIGhandler(int signo) {
  switch (signo) {
    // case /* constant-expression */:
    //   /* code */
    //   break;

  default:
    fprintf(stderr, "Sinal recebido: <%d>.\n", signo);
    shutdown();
    break;
  }
}

void shutdown() {
  unlink(REFEREE_PIPE);
  printf("Programa terminado\n");
  exit(0);
}

void readingArguments(int argc, char *argv[], Tournment *t) {
  if (argc != 3) {
    printf("Leitura dos argumentos de linha de comandos errada!\nAtribuida "
           "argumentos default \n");
    t->timeChampion = TIMECHAMPION;
    t->waitingTime = WAITINGTIME;
    printf("Duration Champion: %d\nWaiting Time: %d\n", t->timeChampion,
           t->waitingTime);
  } else {
    t->timeChampion = atoi(argv[1]);
    t->waitingTime = atoi(argv[2]);
    printf("Duration Champion: %d\nWaiting Time: %d\n", t->timeChampion,
           t->waitingTime);
  }
}

void readingenvvars(Tournment *t) {
  unsigned int value_uint = 0U;
  if (getenv("MAXPLAYERS")) {
    if (sscanf(getenv("MAXPLAYERS"), "%u", &value_uint) != 1) {
      printf(
          "Variável de ambiente deve indicar um número nulo ou "
          "positivo.\nA colocar variavel de ambiente MAXPLAYERS a Default\n");
      t->maxPlayers = MAXPLAYERS;
    } else {
      t->maxPlayers = atoi(getenv("MAXPLAYERS"));
    }
  } else {
    t->maxPlayers = MAXPLAYERS;
  }

  if (getenv("GAMEDIR")) {
    strcpy(t->gameDir, getenv("GAMEDIR"));
  } else {
    strcpy(t->gameDir, GAMEDIR);
  }
  printf("Maximo de Jogadores: %d\nDiretoria do jogo: %s\n", t->maxPlayers,
         t->gameDir);
}

int creatingRefereePipe() {
  if (access(REFEREE_PIPE, F_OK) == 0) { // verifica se já existe o PIPE
    printf("Já se encontra um Referee em execução. A sair...\n");
    shutdown();
  }
  if (mkfifo(REFEREE_PIPE, S_IRWXU) < 0) { // cria o pipe
    printf("Erro ao criar PIPE. A sair...\n");
    shutdown();
  }

  // vai abrir o pipe para leitura/escrita
  int fd_pipe = open(REFEREE_PIPE, O_RDWR);
  if (fd_pipe == -1) {
    printf("Erro ao abrir pipe do Referee. A sair...\n");
    shutdown();
  }
  return fd_pipe;
}

bool login(Tournment *t) { return true; }

void receiver(Tournment *t) {
  Tournment receive, send;
  int fd, fd_send;
  char PIPE[30];

  do {
    read(t->r.fd, &receive, sizeof(receive));
    sprintf(PIPE, "../PLAYER_PIPE->%d", receive.player.pid);
    fd_send = open(PIPE, O_WRONLY, 0600);

    switch (receive.action) {
    case LOGIN:
      break;
    }
  } while (1);
}
