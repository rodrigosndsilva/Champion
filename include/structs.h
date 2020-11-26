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
#define TIMECHAMPIONSHIP 20
#define WAITINGTIME 5
#define REFEREE_PIPE "../src/referee/REFEREE_PIPE"
#define LOGIN 1
#define LOGGED 2

typedef struct {
  char command[50];
  int fd;
} Referee;

typedef struct {
  char question[50];
  char answer[50];
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
  int fd;
} Player;

typedef struct {
  char username[20];
  int pid;
  int Gamepid;
  int points;
} PlayersinTournment;

typedef struct {
  char winner[50];
  int timeChampionship;
  int waitingTime;
  int maxPlayers;
  char gameDir[50];
  int action;
  char message[50];
  Game g;
  Referee r;
  Player p[MAXPLAYERS];
  Player player;
  PlayersinTournment pt;
} Tournment;

#endif