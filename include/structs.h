#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXPLAYERS 30
#define GAMEDIR "/home/rodrigo/Desktop/SO/Trabalho/Champion/build/game.exe"
#define TIMECHAMPION 20
#define WAITINGTIME 5
#define REFEREE_PIPE "../src/referee/REFEREE_PIPE"
#define LOGIN 1

typedef struct {
  char command[50];
  int fd;
} Referee;

typedef struct {
  char pergunta[50];
  char resposta[50];
} QandA;

typedef struct {
  int pid;
  int cont;
  QandA qanda[30];
  bool answerResult;
} Game;

typedef struct {
  char username[20];
  int pid;
  int points;
  int Gamepid;
} Player;

typedef struct {
  char username[20];
  int pid;
  int Gamepid;
  int points;
} PlayersinTournment;

typedef struct {
  char winner[50];
  int timeChampion;
  int waitingTime;
  int maxPlayers;
  char gameDir[50];
  int action;
  Player player;
  Game g;
  Referee r;
  Player p[MAXPLAYERS];
  PlayersinTournment pt;
} Tournment;

#endif