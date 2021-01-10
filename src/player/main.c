#include "main.h"
#include "commands.h"
#include "functions.h"

int main() {
  signal(SIGINT, SIGhandler);
  signal(SIGHUP, SIGhandler);
  signal(SIGQUIT, SIGhandler);

  checkIfRefereeIsOn();
  creatingPlayerPipe();
  printf("\nProgram Iniciated!\n\n");

  t.p.Gamepid = -1;

  pthread_t thread;
  if (pthread_create(&thread, NULL, receiver, NULL) != 0) {
    perror("ERROR creating the thread!\n");
    shutdown();
  }
  t.p.thread = thread;

  login(t);

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