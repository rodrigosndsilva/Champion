#include "functions.h"

int main() {

  creatingGamePipe();

  pthread_t thread;
  if (pthread_create(&thread, NULL, receiver, NULL) != 0) {
    perror("ERROR creating the thread!\n");
    shutdown();
  }
  sleep(8);
  // t = readFile(t);
  // printQandA(t);
  // t = runGame(t);
  printf("Terminar Jogo\n");
  shutdown();
  return 0;
}