#include "commands.h"
#include "main.h"

int handleCommand(char *command) {
  if (strcmp(command, " ") == 0) {
    return 0;
  }
  if (strcmp(command, "test") == 0) {
    printf("\n\nActive Players: %d\nRunning? %d\nActive Games: %d\n",
           t.activePlayers, t.running, t.activeGames);
    printf("\nPlayers Logged:\n");
    listAllPlayersinTournment();
    printf("\nPlayers in Tournment:\n");
    listAllPlayersinTournment();
    printf("\nGames Created:\n");
    listAllGamesCreated();
    return 1;
  }

  if (command[0] == 'k') {
    char name[19];
    for (int i = 0; i < 19; i++) {
      name[i] = command[i + 1];
    }
    delete_user_from_array_by_name(name);
    return 1;
  }
  if (strcmp(command, "exit") == 0) {
    shutdown();
    return 1;
  }
  if (strcmp(command, "players") == 0) {
    listAllPlayersinTournment();
    return 1;
  }
  if (strcmp(command, "gamescreated") == 0) {
    listAllGamesCreated();
    return 1;
  }
  if (strcmp(command, "playerslogged") == 0) {
    listAllPlayersLogged();
    return 1;
  }

  if (strcmp(command, "end") == 0) {
    if (t.activeGames > 0) {
      for (int i = 0; i < t.activeGames; i++) {
        printf("Ending Game-> %d\n", t.games[i].pid);
        kill(t.games[i].pid, SIGUSR1);
        printf("Exit Status: %d\n", getExitStatus(t.games[i].pid));
      }

      delete_all_games_from_array_by_pid();
      removeAllPlayerfromTournment();
      t.running = false;
      printf("asd\n");
    } else {
      printf("No Games Created.\n");
    }
    return 1;
  }

  return 0;
}