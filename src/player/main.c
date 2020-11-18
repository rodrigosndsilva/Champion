#include "main.h"

int main() {
  signal(SIGINT, SIGhandler);
  signal(SIGHUP, SIGhandler);
  signal(SIGQUIT, SIGhandler);

  checkIfRefereeIsOn();
  creatingPlayerPipe();
  printf("\nPlayer iniciado!\n\n");


  // do {
  //   Tournment t;
  //   printf("Enter a name : ");
  //   scanf("%s", &p.username);
  //   write(pipefd[1], V, ds * sizeof(V));
  // } while ();

  shutdown();
}