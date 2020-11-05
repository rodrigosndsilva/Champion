#include "main.h"

void readingArguments(int argc, char *argv[], tournment *t) {

  if (argc != 3) {
    printf("Leitura dos argumentos de linha de comandos errada!\nAtribuida "
           "argumentos default\n");
    t->timeChampion = TIMECHAMPION;
    t->waitingTime = WAITINGTIME;
    printf("Duration Champion: %d\nWaiting Time: %d\n", t->timeChampion,
           t->waitingTime); 
  } else {
    t->timeChampion = atoi(argv[1]);
    t->waitingTime = atoi(argv[2]);
    printf("Duration Champion: %d\nWaiting Time: %d\n", t->timeChampion,
           t->waitingTime);
  }
}

void readingenvvars(tournment *t) {
  unsigned int value_uint = 0U;
  if (getenv("MAXPLAYERS")) {
    if (sscanf(getenv("MAXPLAYERS"), "%u", &value_uint) != 1) {
      printf(
          "Variável de ambiente deve indicar um número nulo ou "
          "positivo.\nA colocar variavel de ambiente MAXPLAYERS a Default\n");
      t->maxPlayers = MAXPLAYERS;
    } else {
      t->maxPlayers = atoi(getenv("MAXPLAYERS"));
    }
  } else {
    t->maxPlayers = MAXPLAYERS;
  }

  if (getenv("GAMEDIR")) {
    strcpy(t->gameDir, getenv("GAMEDIR"));
  } else {
    strcpy(t->gameDir, GAMEDIR);
  }
  printf("Maximo de Jogadores: %d\nDiretoria do jogo: %s\n", t->maxPlayers,
         t->gameDir);
}

int main(int argc, char *argv[]) {

  readingArguments(argc, argv, &t);
  readingenvvars(&t);
 
  return 0;
}
