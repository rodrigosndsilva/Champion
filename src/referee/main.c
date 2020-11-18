#include "main.h"

int main(int argc, char *argv[]) {
  signal(SIGINT, SIGhandler);
  signal(SIGHUP, SIGhandler);
  signal(SIGQUIT, SIGhandler);

  readingArguments(argc, argv, t);
  readingenvvars(t);

  t->r.fd = creatingRefereePipe();

  pthread_t thread;
  if (pthread_create(&thread, NULL, receiver, t) != 0) {
    perror("ERRO! A criar a thread!\n");
    shutdown();
  }

  char c;
  getc(c);
  printf("\nServidor iniciado!\n\n");

  shutdown();
}
