#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "../../include/structs.h"

void readingArguments(int argc, char *argv[], Tournment *t);
void readingenvvars(Tournment *t);
void SIGhandler(int signo);
void shutdown();
void creatingRefereePipe();
void handleLogin(Tournment *t, Tournment r);
void *receiver();

#endif
