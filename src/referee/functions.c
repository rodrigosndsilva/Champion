#include "functions.h"
#include "main.h"

void SIGhandler(int signo) {
  // case SIGUSR1:

  //   break;
  switch (signo) {

  default:
    printf("\nSignal received on Referee: <%d>.\n", signo);
    shutdown();
    break;
  }
}

void shutdown() {
  char PIPE[PATH_MAX];
  int fd;
  Tournment send;
  send.action = SERVER_SHUTDOWN;
  for (int i = 0; i < t.activeGames; i++) {
    sprintf(PIPE, "../src/game/Game-> %d", t.games[i].pid);
    fd = open(PIPE, O_WRONLY);
    write(fd, &send, sizeof(send));
    close(fd);
  }

  for (int i = 0; i < t.activePlayers; i++) {
    sprintf(PIPE, "../src/player/PLAYER_PIPE-> %d", t.players[i].pid);
    fd = open(PIPE, O_WRONLY);
    write(fd, &send, sizeof(send));
    close(fd);
  }
  printf("Referee Terminated!\n");
  unlink(REFEREE_PIPE);
  pthread_cancel(t.thread);
  pthread_mutex_destroy(&t.m1);
  // pthread_cancel(t.timer);
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
      t.players[t.activePlayers].inTournment = false;
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

void listAllPlayersLogged() {
  if (t.activePlayers == 0) {
    printf("No players logged\n");
  }
  for (int i = 0; i < t.activePlayers; i++) {
    printf("Player-> %d\tUsername: %s\t Tournment: %d\n", t.players[i].pid,
           t.players[i].username, t.players[i].inTournment);
  }
}

void listAllPlayersinTournment() {
  int aux = 0;
  if (t.running != false) {
    if (t.activePlayers == 0) {
      printf("No players logged\n");
    }
    for (int i = 0; i < t.activePlayers; i++) {
      if (t.players[i].inTournment == true) {
        printf("Username: %s\tGame-> %d\n", t.players[i].username,
               t.players[i].Gamepid);
        aux = 1;
      }
    }
    if (aux == 0) {
      printf("No Players in tournment\n");
    }
  } else {
    printf("No tournment running\n");
    return;
  }
}

void listAllGamesCreated() {
  if (t.activeGames == 0) {
    printf("No Games created\n");
  }
  for (int i = 0; i < t.activeGames; i++) {
    printf("Game-> %d\n", t.games[i].pid);
  }
}

void delete_user_from_array_by_pid(int pid) {
  for (int i = 0; i < t.activePlayers; i++) {
    if (t.players[i].pid == pid) {
      for (int j = i; j < t.activePlayers; j++) {
        t.players[j] = t.players[j + 1];
      }
    }
    t.activePlayers--;
  }
}

void delete_user_from_array_by_name(char name[]) {
  for (int i = 0; i < t.activePlayers; i++) {
    if (strcmp(name, t.players[i].username) == 0) {
      for (int j = i; j < t.activePlayers; j++) {
        t.players[j] = t.players[j + 1];
      }
      t.activePlayers--;
    }
  }
}

void delete_game_from_array_by_pid(int pid) {
  for (int i = 0; i < t.activeGames; i++) {
    if (t.games[i].pid == pid) {
      for (int j = i; j < t.activeGames; j++) {
        t.games[j] = t.games[j + 1];
      }
    }
    t.activeGames--;
  }
}
void delete_all_games_from_array_by_pid() {
  Game g[t.maxPlayers];
  t.games = g;
  t.activeGames = 0;
}

void removeAllPlayerfromTournment() {
  if (t.activePlayers == 0) {
    printf("No players logged\n");
    return;
  }
  for (int i = 0; i < t.activePlayers; i++) {
    if (t.players[i].inTournment == true) {
      t.players[i].inTournment = false;
    }
  }
}

void removingPlayerfromTournment(pid_t pid) {
  if (t.activePlayers == 0) {
    printf("No players logged\n");
  }
  for (int i = 0; i < t.activePlayers; i++) {
    if (t.players[i].pid == pid && t.players[i].inTournment == true) {
      t.players[i].inTournment = false;
      return;
    }
  }
}

void removingGamefromTournment(pid_t pid) {
  for (int i = 0; i < t.activeGames; i++) {
    if (t.games[i].pid == pid) {
      for (int j = i; j < t.activeGames; j++) {
        t.games[j] = t.games[j + 1];
      }
    }
    t.activeGames--;
  }
}

int getExitStatus(pid_t pid) {
  int status;

  if (waitpid(pid, &status, 0) == -1) {
    printf("Waitpid failed\n");
    shutdown();
  }

  if (WIFEXITED(status)) {
    int es = WEXITSTATUS(status);
    return es;
  }
  return -1;
}

Player findPlayerinArray(pid_t pid) {
  for (int i = 0; i < t.activePlayers; i++) {
    if (t.players[i].pid == pid) {
      return t.players[i];
    }
  }
  return t.p;
}

int removePlayerWithGamePID(pid_t Gamepid) {
  for (int i = 0; i < t.activePlayers; i++) {
    if (t.players[i].Gamepid == Gamepid) {
      t.players[i].inTournment = false;
      return t.players[i].pid;
    }
  }
  return -1;
}

void givePlayersOneGame() {
  Tournment send, receive;
  char PIPE[PATH_MAX];
  if (t.activePlayers >= 2) {
    for (int i = 0; i < t.activePlayers; i++) {
      createGame();

      int fd_receive = open(REFEREE_PIPE, O_RDONLY);
      read(fd_receive, &receive, sizeof(receive));
      t.g.pid = receive.g.pid;

      printf("Recieved PID for Game-> %d\n", t.g.pid);
      t.games[t.activeGames].pid = t.g.pid;
      t.activeGames++;
      sprintf(PIPE, "../src/player/PLAYER_PIPE-> %d", t.players[i].pid);
      printf("Sending info for PLAYER_PIPE-> %d\n", t.players[i].pid);
      t.players[i].inTournment = true;
      t.players[i].Gamepid = t.g.pid;

      int fd_send = open(PIPE, O_WRONLY);
      send.action = GAMEPID;
      send.g.pid = t.g.pid;
      write(fd_send, &send, sizeof(send));
      close(fd_send);
    }
    t.running = true;
  } else {
    printf("The minimum palyers to start a Championship is 2\nCurrent players: "
           "%d.\n Waiting for more players...\n",
           t.activePlayers);
  }
}

void createGame() {
  pid_t pid = fork();
  if (pid < 0) {
    perror("Fork failed\n");
    shutdown();
  }
  if (pid == 0) { // child
    execlp(GAMEDIR, GAMEDIR, NULL);
    printf("The Program could not be started\n");
    shutdown();
  }
}

void funcTimer(int timer) {
  time_t bg, end;
  int aux = 0;
  int t = 0;
  bg = time(NULL);
  while (t < timer) {
    end = time(NULL);
    t = (int)((end - bg));
    if (t != aux) {
      aux = t;
      printf("%d sec passed\n", t);
    }
  }
}

void *timerthread() {
  funcTimer(t.waitingTime);
  t.timeExpired = true;
  printf("Timer concluded\n");
  pthread_cancel(t.timer);
}

void *receiver() {
  Tournment receive, send;
  char PIPE[PATH_MAX];
  int flag, pid;

  int fd_receive = open(REFEREE_PIPE, O_RDONLY);
  if (fd_receive == -1) {
    printf("Error opening FIFO of Referee. Leaving...\n");
    shutdown();
  }
  do {
    if (t.activePlayers >= 2 && t.running == false) {
      if (t.enableTimer == false) {
        pthread_t timer;
        if (pthread_create(&timer, NULL, timerthread, NULL) != 0) {
          perror("ERROR creating the thread!\n");
          shutdown();
        }
        t.timer = timer;
        printf("\n\nDebug\n\n");
        t.enableTimer = true;
        printf("Timer enabled\n");
      }
      pthread_mutex_lock(&t.m2);
      if (t.timeExpired == true) {
        t.enableTimer = false;
        printf("\nStarting Tournment Timer: At least 2 players online!\n");
        givePlayersOneGame();
      }
    }

    read(fd_receive, &receive, sizeof(receive));
    sprintf(PIPE, "../src/player/PLAYER_PIPE-> %d", receive.p.pid);
    int fd_send = open(PIPE, O_WRONLY);

    switch (receive.action) {
    case CLIENT_SHUTDOWN:
      receive.p = findPlayerinArray(receive.p.pid);
      if (receive.p.inTournment == true) {
        printf("Player leaved the Game\nEnding Game-> %d\n\n",
               receive.p.Gamepid);
        kill(receive.p.Gamepid, SIGUSR1);
        sleep(1);
        printf("Exit Status: %d\n\n", getExitStatus(receive.p.Gamepid));
        removingGamefromTournment(receive.p.Gamepid);
      }
      delete_user_from_array_by_pid(receive.p.pid);
      printf("The user with the PID %d has left the program!\n", receive.p.pid);
      break;
    case GAMEPID:
      t.g.pid = receive.g.pid;
      printf("Recieved PID for Game-> %d\n", t.g.pid);
      break;
    case GAMESHUTDOWN:
      pid = removePlayerWithGamePID(receive.g.pid);
      delete_game_from_array_by_pid(receive.g.pid);
      printf("Exit Status: %d\n", getExitStatus(receive.g.pid));

      sprintf(PIPE, "../src/player/PLAYER_PIPE-> %d", pid);
      fd_send = open(PIPE, O_WRONLY);
      t.running = false;
      send.action = GAMESHUTDOWN;
      send.p.pid = send.p.Gamepid = -1;
      write(fd_send, &send, sizeof(send));
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
    }
    receive.action = EMPTY;
    send.action = EMPTY;
  } while (1);
  close(fd_receive);
}
