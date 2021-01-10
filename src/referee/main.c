#include "main.h"
#include "commands.h"
#include "functions.h"

int main(int argc, char *argv[]) {

  signal(SIGINT, SIGhandler);
  signal(SIGHUP, SIGhandler);
  signal(SIGQUIT, SIGhandler);
  signal(SIGKILL, SIGhandler);

  readingArguments(argc, argv);
  readingenvvars();

  creatingRefereePipe();

  t.activePlayers = 0;
  t.activeGames = 0;
  t.timeExpired = false;
  t.enableTimer = false;
  Player p[t.maxPlayers]; // aux
  t.players = p;
  Game g[t.maxPlayers];
  t.games = g;
  t.running = false;

  pthread_t thread;
  if (pthread_create(&thread, NULL, receiver, NULL) != 0) {
    perror("ERROR creating the thread!\n");
    shutdown();
  }
  t.thread = thread;

   pthread_mutex_t m1,m2;
  if (pthread_mutex_init(&m1, NULL) != 0) {
    printf("\n mutex falhou\n");
    return 1;
  }
  t.m1 = m1;
  if (pthread_mutex_init(&m2, NULL) != 0) {
    printf("\n mutex falhou\n");
    return 1;
  }

  t.m2 = m2;

  printf("\nServer Iniciated!\n\n");

  char command[20];
  do {
    scanf("%s", command);
    int flag = handleCommand(command);
    if (flag == 0) {
      printf("Command not found!\n");
    }
  } while (strcmp(command, "exit") != 0);

  shutdown();
}
