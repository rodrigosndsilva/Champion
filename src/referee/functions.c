#include "functions.h"
#include "main.h"

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
  char PIPE[50];
  int fd;
  Tournment send;
  send.action = SERVER_SHUTDOWN;

  for (int i = 0; i < t.activePlayers; i++) {
    sprintf(PIPE, "../src/player/PLAYER_PIPE-> %d", t.players[i].pid);
    fd = open(PIPE, O_WRONLY);
    write(fd, &send, sizeof(send));
    close(fd);
  }

  printf("Referee Terminated!\n");
  unlink(REFEREE_PIPE);
  pthread_kill(pthread_self(), 0);
  exit(0);
}

void readingArguments(int argc, char *argv[]) {
  if (argc != 3) {
    printf("The arguments read from the command line are wrong!\nAssigning "
           "default arguments\n");
    t.timeChampionship = TIMECHAMPIONSHIP;
    t.waitingTime = WAITINGTIME;

    printf("Duration Champion: %d\nWaiting Time: %d\n", t.timeChampionship,
           t.waitingTime);
  } else {
    t.timeChampionship = atoi(argv[1]);
    t.waitingTime = atoi(argv[2]);
    printf("Duration Champion: %d\nWaiting Time: %d\n", t.timeChampionship,
           t.waitingTime);
  }
}

void readingenvvars() {
  unsigned int value_uint = 0U;
  if (getenv("MAXPLAYERS")) {
    if (sscanf(getenv("MAXPLAYERS"), "%u", &value_uint) != 1) {
      printf("MaxPlayers Environment Variable should be a nule or a positive "
             "number.\nSetting default Environment Variable\n");
      t.maxPlayers = MAXPLAYERS;
    } else {
      t.maxPlayers = atoi(getenv("MAXPLAYERS"));
    }
  } else {
    t.maxPlayers = MAXPLAYERS;
  }

  if (getenv("GAMEDIR")) {
    strcpy(t.gameDir, getenv("GAMEDIR"));
  } else {
    strcpy(t.gameDir, GAMEDIR);
  }
  printf("Max Players: %d\nDIR of Game: %s\n", t.maxPlayers, t.gameDir);
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

int isNamePlayerOnTheList(char *username) {
  for (int i = 0; i < t.activePlayers; i++) {
    if (strcmp(t.players[i].username, username) == 0) {
      return 1;
    }
  }
  return 0;
}

int handleLogin(Tournment r) {
  if (t.activePlayers != t.maxPlayers) {
    if (isNamePlayerOnTheList(r.p.username) != 1) {

      t.players[t.activePlayers].pid = r.p.pid;
      strcpy(t.players[t.activePlayers].username, r.p.username);
      printf("Player-> %d\tUsername: %s\tAdded to Logged Players list!\n",
             t.players[t.activePlayers].pid,
             t.players[t.activePlayers].username);
      t.activePlayers++;
      return 1;
    } else {
      printf("This name is already taken\n");
      return 2;
    }

  } else {
    printf("Number of players exceeded! Max: %d\n", t.maxPlayers);
    return 3;
  }
}
void delete_user_from_array(int pid) {
  for (int i = 0; i < t.activePlayers; i++) {
    if (t.players[i].pid == pid) {
      for (int j = i; j < t.activePlayers; j++) {
        t.players[j] = t.players[j + 1];
      }
    }
    t.activePlayers--;
  }
}

void listAllPlayersLogged() {
  if (t.activePlayers == 0) {
    printf("No players logged\n");
  }     
  for (int i = 0; i < t.activePlayers; i++) {
    printf("Player-> %d\tUsername: %s\n", t.players[i].pid,
           t.players[i].username);
  }
}

void *receiver() {
  Tournment receive, send;
  char PIPE[50];
  int flag;

  int fd_receive = open(REFEREE_PIPE, O_RDONLY);
  if (fd_receive == -1) {
    printf("Error opening FIFO of Referee. Leaving...\n");
    shutdown();
  }
  do {
    read(fd_receive, &receive, sizeof(receive));
    sprintf(PIPE, "../src/player/PLAYER_PIPE-> %d", receive.p.pid);
    int fd_send = open(PIPE, O_WRONLY);

    switch (receive.action) {
    case CLIENT_SHUTDOWN:
      delete_user_from_array(receive.p.pid);
      printf("The user with the PID %d has left the program!\n", receive.p.pid);
      break;
    case LOGIN:
      flag = handleLogin(receive);
      if (flag == 1) {
        strcpy(send.message, "Successfully logged in!\n");
        send.action = LOGGED;
      }
      if (flag == 2) {
        strcpy(send.message, "This name is already taken!\n");
        send.action = NOTLOGGED;
      }
      if (flag == 3) {
        strcpy(send.message, "Number of players exceeded!\n");
        send.action = NOTLOGGED;
      }
      write(fd_send, &send, sizeof(send));
      break;
    default:

      break;
    }
    receive.action = EMPTY;
    send.action = EMPTY;
  } while (1);
  close(fd_receive);
}
