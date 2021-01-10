#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "../../include/structs.h"

void readingArguments(int argc, char *argv[]);
void readingenvvars();
void SIGhandler(int signo);
void shutdown();
void creatingRefereePipe();
int handleLogin(Tournment r);
void *receiver();
int isNamePlayerOnTheList(char *username);
void delete_user_from_array_by_pid(int pid);
void delete_all_games_from_array_by_pid();
void delete_user_from_array_by_name(char *name);
void delete_game_from_array_by_pid(int pid);
void listAllPlayersLogged();
void listAllPlayersinTournment();
void createGame();
void givePlayersOneGame();
void listAllGamesCreated();
int getExitStatus(pid_t pid);
void removingPlayerfromTournment(pid_t pid);
void removeAllPlayerfromTournment();
Player findPlayerinArray(pid_t pid);
void removingGamefromTournment(pid_t pid);
void *timerthread();
void funcTimer(int timer);
int removePlayerWithGamePID(pid_t Gamepid);

#endif
