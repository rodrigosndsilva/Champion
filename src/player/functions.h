#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../../include/structs.h"

void SIGhandler(int signo);
void shutdown();
int creatingPlayerPipe();
void checkIfRefereeIsOn();

#endif /* FUNCTIONS_H */
