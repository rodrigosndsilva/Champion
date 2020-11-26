#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../../include/structs.h"

void SIGhandler(int signo);
void shutdown();
void creatingPlayerPipe();
void checkIfRefereeIsOn();
void *receiver();
void login(Tournment t);

#endif /* FUNCTIONS_H */
