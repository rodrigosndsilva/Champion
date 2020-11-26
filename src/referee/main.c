#include "main.h"

int main(int argc, char *argv[]) {

  signal(SIGINT, SIGhandler);
  signal(SIGHUP, SIGhandler);
  signal(SIGQUIT, SIGhandler);

  readingArguments(argc, argv, &t);
  readingenvvars(&t);

  creatingRefereePipe();

  pthread_t thread;
  if (pthread_create(&thread, NULL, receiver, &t) != 0) {
    perror("ERROR creating the thread!\n");
    shutdown();
  }

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
