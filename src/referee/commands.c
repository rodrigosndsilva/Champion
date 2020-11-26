#include "commands.h"

int handleCommand(char *command) {
  if (strcmp(command, " ") == 0) {
    return 0;
  }
  if (strcmp(command, "exit") == 0) {
    return 1;
  }
  if (strcmp(command, "end") == 0) {
    return 1;
  }
  return 0;
}