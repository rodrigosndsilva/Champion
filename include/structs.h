#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXPLAYERS 30
#define GAMEDIR "/home/rodrigo/Desktop/SO/Trabalho/Champion/build/game.exe"
#define TIMECHAMPION 20
#define WAITINGTIME 5

typedef struct {
  char command[50];
} admin;

typedef struct {
  char winner[50];
  int timeChampion;
  int waitingTime;
  int maxPlayers;
  char gameDir[50];
} tournment;

typedef struct {
  char pergunta[100];
  char resposta[50];
  
} game;

typedef struct {
  char username[20];
  int pid;
  int points;
  int Gamepid;
} player;

typedef struct {
  char username[20];
  int pid;
  int Gamepid;
  int points;
} playersinTournment;