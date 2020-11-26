#include "commands.h"
#include "main.h"

int handleCommand(char *command) {
  if (strcmp(command, " ") == 0) {
    return 0;
  }
  if (strcmp(command, "exit") == 0) {
    shutdown();
    return 1;
  }
  if (strcmp(command, "end") == 0) {
    return 1;
  }
  if (strcmp(command, "players") == 0) {
    return 1;
  }
  if (strcmp(command, "playerslogged") == 0) {
    listAllPlayers(&t);
    return 1;
  }
  return 0;
}