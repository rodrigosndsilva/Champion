#include "functions.h"

void SIGhandler(int signo) {
  fprintf(stderr, "Sinal recebido: <%d>.\n", signo);
  shutdown();
}

void shutdown() {
  char PIPE[30];
  sprintf(PIPE, "PLAYER_PIPE-> %d", getpid());
  unlink(PIPE);
  printf("Programa terminado\n");
  exit(0);
}

int creatingPlayerPipe() {
  char PIPE[30];
  int fd_pipe;
  sprintf(PIPE, "PLAYER_PIPE-> %d", getpid());
  if (mkfifo(REFEREE_PIPE, S_IRWXU) < 0) { // cria o pipe
    printf("Erro ao criar PIPE. A sair...\n");
    shutdown();
  }

  // vai abrir o pipe para leitura/escrita
  fd_pipe = open(PIPE, O_RDWR);
  if (fd_pipe == -1) {
    printf("Erro ao abrir pipe do Player. A sair...\n");
    shutdown();
  }
  return fd_pipe;
}
void checkIfRefereeIsOn() {
  if (access(REFEREE_PIPE, F_OK) != 0) { // verifica se já existe o PIPE
    printf("O Referee nao esta iniciado. A sair...\n");
    shutdown();
  }
}
