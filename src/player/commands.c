#include "commands.h"
#include "main.h"

int handleCommand(char *command) {
  if (strcmp(command, " ") == 0) {
    return 0;
  }
  if (strcmp(command, "#quit") == 0) {
    shutdown();
    return 1;
  }
  if (strcmp(command, "#mygame") == 0) {
    if (t.p.Gamepid == -1) {
      printf("You dont have any Game\n");
    } else {
      printf("Your game is Game-> %d\n", t.p.Gamepid);
    }
    return 1;
  }

  return 0;
}