#include "functions.h"

void SIGhandler(int signo) {
  if (signo == SIGINT) {
    printf("\nReceived SIGINT\n");
  }
  if (signo == SIGHUP) {
    printf("\nReceived SIGHUP\n");
  }
  if (signo == SIGQUIT) {
    printf("\nReceived SIGQUIT\n");
  }
  shutdown();
}

void shutdown() {
  unlink(PIPE_REFEREE);
  printf("Programa terminado\n");
  exit(0);
}

void readingArguments(int argc, char *argv[], tournment *t) {
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

void readingenvvars(tournment *t) {
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

void creatingRefereePipe() {
  int fd_pipe;
  if (access(PIPE_REFEREE, F_OK) == 0) { // verifica se já existe o PIPE
    printf("Já se encontra um Referee em execução. A sair...\n");
    shutdown();
  }
  if (mkfifo(PIPE_REFEREE, S_IRWXU) < 0) { // cria o pipe
    printf("Erro ao criar PIPE. A sair...\n");
    shutdown();
  }

  // vai abrir o pipe para leitura/escrita
  fd_pipe = open(PIPE_REFEREE, O_RDWR);
  if (fd_pipe == -1) {
    printf("Erro ao abrir pipe do Referee. A sair...\n");
    shutdown();
  }
  printf("\nServidor iniciado!\n\n");
}
