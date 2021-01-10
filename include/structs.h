#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <fcntl.h>
#include <linux/limits.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MAXPLAYERS 3
#define GAMEDIR "/home/rodrigo/Desktop/SO/Trabalho/Champion2/build/g_1"
#define GAME1 "g_1"
#define TIMECHAMPIONSHIP 20
#define WAITINGTIME 10
#define REFEREE_PIPE "../src/referee/REFEREE_PIPE"
#define EMPTY -1
#define LOGIN 1
#define LOGGED 2
#define NOTLOGGED 3
#define SERVER_SHUTDOWN 4
#define CLIENT_SHUTDOWN 5
#define GAMESHUTDOWN 6
#define GAMEPID 7

typedef struct {
  char question[50];
  char answer[50];
} QandA;

typedef struct {
  int pid;
  int cont;
  QandA qanda[30];
  bool answerResult;
  pthread_t thread;
} Game;

typedef struct {
  char username[20];
  int pid;
  int points;
  int Gamepid;
  bool inTournment;
  pthread_t thread;
} Player;

typedef struct {
  char winner[50];
  int timeChampionship;
  int waitingTime;
  int maxPlayers;
  char gameDir[50];
  int action;
  char message[50];
  int activePlayers;
  int activeGames;
  bool running;
  bool timeExpired;
  bool enableTimer;
  pthread_mutex_t m1, m2;
  pthread_t thread, timer;
  Game g;
  Game *games;
  Player p;
  Player *players;
} Tournment;

#endif