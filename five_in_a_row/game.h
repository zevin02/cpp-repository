#pragma once

#include<string.h>
#include<stdio.h>
#define row 20
#define col 20

#define player1 1
#define player2 2

#define next 0
#define player1_win 1
#define player2_win 2
#define draw        3


enum dir
{
  left,
  right,
  up,
  down,
  left_up,
  left_down,
  right_up,
  right_down,
}


void menu();


void game();



int isover(int board[][col],int row,int col);

void showboard(int board[][col],int row,int col);

void playermove(int board[][col],int row,int col,int who);

