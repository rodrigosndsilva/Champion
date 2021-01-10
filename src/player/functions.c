#include "functions.h"
#include "main.h"

int logged = 0;

void SIGhandler(int signo) {
  switch (signo) {
    // case /* constant-expression */:
    //   /* code */
    //   break;

  default:
    fprintf(stderr, "\nSignal received: <%d>.\n", signo);
    shutdown();
    break;
  }
}

void shutdown() {
  char PIPE[PATH_MAX];
  int fd;
  Tournment send;

  sprintf(PIPE, "../src/player/PLAYER_PIPE-> %d", getpid());

  if (logged == 1) {
    send.p.pid = getpid();
    send.action = CLIENT_SHUTDOWN;
    fd = open(REFEREE_PIPE, O_WRONLY);
    write(fd, &send, sizeof(send));
  }

  close(fd);
  unlink(PIPE);
  printf("PLAYER_PIPE-> %d terminated\n", getpid());
  pthread_cancel(t.p.thread);
  exit(0);
}

void serverShutdown() {
  char PIPE[PATH_MAX];
  sprintf(PIPE, "../src/player/PLAYER_PIPE-> %d", getpid());
  unlink(PIPE);
  printf("PLAYER_PIPE-> %d terminated\n", getpid());
  pthread_cancel(t.p.thread);
  exit(0);
}

void creatingPlayerPipe() {
  char PIPE[PATH_MAX];
  sprintf(PIPE, "../src/player/PLAYER_PIPE-> %d", getpid());
  if (mkfifo(PIPE, S_IRWXU) < 0) { // cria o pipe
    printf("Error creating FIFO of Player. Leaving...\n");
    shutdown();
  }
}
void checkIfRefereeIsOn() {
  if (access(REFEREE_PIPE, F_OK) != 0) { // verifica se já existe o PIPE
    printf("Server is not iniciated! Leaving...\n");
    shutdown();
  }
}

void login(Tournment t) {
  int fd = open(REFEREE_PIPE, O_WRONLY);
  if (fd == -1) {
    printf("Error opening FIFO of Referee. Leaving...\n");
    shutdown();
  }

  while (logged == 0) {
    printf("Enter your name: ");
    scanf("%s", t.p.username);
    checkIfRefereeIsOn();
    t.action = LOGIN;
    t.p.pid = getpid();
    write(fd, &t, sizeof(t));
    sleep(1);
    close(fd);
  }
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
  sprintf(PIPE, "../src/player/PLAYER_PIPE-> %d", getpid());
  fd_receive = open(PIPE, O_RDONLY);
  if (fd_receive == -1) {
    printf("Error opening FIFO of Player. Leaving...\n");
    shutdown();
  }
  do {
    read(fd_receive, &receive, sizeof(receive));

    switch (receive.action) {
    case SERVER_SHUTDOWN: // SERVIDOR TERMINOU
      printf("The server has been shut down!\n\n");
      serverShutdown();
      break;
    case LOGGED:
      logged = 1;
      printf("%s", receive.message);
      break;
    case GAMESHUTDOWN:
      printf("\nYour game was shutdown!\nGame-> %d\n\n", t.p.Gamepid);
      t.p.Gamepid = receive.p.Gamepid;
      break;

    case NOTLOGGED:
      printf("%s", receive.message);
      break;
    case GAMEPID:
      t.p.Gamepid = receive.g.pid;
      printf("Your game is Game-> %d\n\n", t.p.Gamepid);
      break;
    }
    receive.action = EMPTY;
    // send.action = EMPTY;
  } while (1);
}
