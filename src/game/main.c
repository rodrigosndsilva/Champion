#include "main.h"
#include "functions.h"

int main() {
  pid_t sid;

  sid = setsid();
  if (sid < 0) {
    printf("Setsid Error\n");
    shutdown();
  }

  close(STDIN_FILENO);

  signal(SIGINT, SIGhandler);
  signal(SIGHUP, SIGhandler);
  signal(SIGQUIT, SIGhandler);
  signal(SIGUSR1, SIGhandler);

  creatingGamePipe();

  pthread_t thread;
  if (pthread_create(&thread, NULL, receiver, NULL) != 0) {
    perror("ERROR creating the thread!\n");
    shutdown();
  }
  t.g.thread = thread;

  sleep(10);
  // t = readFile(t);
  // printQandA(t);
  // t = runGame(t);

  shutdown();
}