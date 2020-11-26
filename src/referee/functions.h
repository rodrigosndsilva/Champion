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
void delete_user_from_array(int pid);
void listAllPlayers();

#endif
