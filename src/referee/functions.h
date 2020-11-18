#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "../../include/structs.h"

Tournment *t;

void readingArguments(int argc, char *argv[], Tournment *t);
void readingenvvars(Tournment *t);
void SIGhandler(int signo);
void shutdown();
int creatingRefereePipe();
bool login(Tournment *t);
void receiver(Tournment *t);

#endif
