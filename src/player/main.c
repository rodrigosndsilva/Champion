#include "main.h"

int main() {
  signal(SIGINT, SIGhandler);
  signal(SIGHUP, SIGhandler);
  signal(SIGQUIT, SIGhandler);

  checkIfRefereeIsOn();
  creatingPlayerPipe();
  printf("\nProgram Iniciated!\n\n");

  
  pthread_t thread;
  if (pthread_create(&thread, NULL, receiver, NULL) != 0) {
    perror("ERROR creating the thread!\n");
    shutdown();
  }
  printf("%d\n",getpid());
  login(t);
  do
  {
    printf("GAME: ");
    scanf("%s", t.p.username);
  } while (1);
  
  shutdown();
}