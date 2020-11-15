#include "main.h"

int main(int argc, char *argv[]) {
  signal(SIGINT, SIGhandler);
  signal(SIGHUP, SIGhandler);
  signal(SIGQUIT, SIGhandler);
  
  readingArguments(argc, argv, &t);
  readingenvvars(&t);

  creatingRefereePipe();

  shutdown();
  return EXIT_FAILURE;
}
