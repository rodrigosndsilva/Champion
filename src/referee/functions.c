#include "functions.h"

void SIGhandler(int signo) {
  switch (signo) {
    // case /* constant-expression */:
    //   /* code */
    //   break;

  default:
    printf("\nSignal received: <%d>.\n", signo);
    shutdown();
    break;
  }
}

void shutdown() {
  printf("Server Terminated\n");
  unlink(REFEREE_PIPE);
  pthread_kill(pthread_self(), 0);
  exit(0);
}

void readingArguments(int argc, char *argv[], Tournment *t) {
  if (argc != 3) {
    printf("The arguments read from the command line are wrong!\nAssigning "
           "default arguments\n");
    t->timeChampionship = TIMECHAMPIONSHIP;
    t->waitingTime = WAITINGTIME;

    printf("Duration Champion: %d\nWaiting Time: %d\n", t->timeChampionship,
           t->waitingTime);
  } else {
    t->timeChampionship = atoi(argv[1]);
    t->waitingTime = atoi(argv[2]);
    printf("Duration Champion: %d\nWaiting Time: %d\n", t->timeChampionship,
           t->waitingTime);
  }
}

void readingenvvars(Tournment *t) {
  unsigned int value_uint = 0U;
  if (getenv("MAXPLAYERS")) {
    if (sscanf(getenv("MAXPLAYERS"), "%u", &value_uint) != 1) {
      printf("MaxPlayers Environment Variable should be a nule or a positive "
             "number.\nSetting default Environment Variable\n");
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
  printf("Max Players: %d\nDIR of Game: %s\n", t->maxPlayers, t->gameDir);
}

void creatingRefereePipe() {
  if (access(REFEREE_PIPE, F_OK) == 0) { // verifica se já existe o PIPE
    printf("Theres already a FIFO online. Leaving...\n");
    shutdown();
  }
  if (mkfifo(REFEREE_PIPE, S_IRWXU) < 0) { // cria o pipe
    printf("Error creating FIFO of Referee. Leaving...\n");
    shutdown();
  }
  printf("Referee FIFO Created\n");
}

void handleLogin(Tournment *t, Tournment r) {
  printf("Player-> %d\tUsername: %s\tAdded to Logged Players list!\n",
         r.player.pid, r.player.username);
}

void *receiver(Tournment *t) {
  Tournment receive;
  char PIPE[50];

  int fd_receive = open(REFEREE_PIPE, O_RDONLY);
  if (fd_receive == -1) {
    printf("Error opening FIFO of Referee. Leaving...\n");
    shutdown();
  }
  do {
    read(fd_receive, &receive, sizeof(receive));
    sprintf(PIPE, "../src/player/PLAYER_PIPE-> %d", receive.player.pid);
    int fd_send = open(PIPE, O_WRONLY);

    switch (receive.action) {
    case LOGIN:
      handleLogin(t, receive);
      break;
    }
    close(fd_send);
  } while (1);
  close(fd_receive);
}
