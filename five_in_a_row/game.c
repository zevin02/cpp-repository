#include"game.h"
int x=0;
int y=0;
void menu()
{
printf("#############################\n#");
printf("####1.play   0.exit###########\n");
printf("##############################\n");
printf("###please make your decision##\n");

}


//player1_win :用户1赢
//player2_win: 用户2赢
//draw：平局


int isover(int board[][col],int row,int col)
{
//难点
//现在点是在x，y处
//五子连珠
int count1=chesscount(board,row,col,left)+chesscount(board,row,col,right);//在该位置向左数+向该位置向右,判断横的有没有连起来
}


void showboard(int board[][col],int row,int col)
{
//讲数组内容
}

//落子
void playermove(int board[][col],int row,int col,int who)
{
//合法性，去重
//提示用户输入
while(1)
{
  printf("player[%d] please enter your pos",who);
  scanf("%d %d",&x,&y);
//判断坐标的合法性
if(x<1||x>row||y<1||y>col)
{
    printf("pos is not valid\n");
    continue;
}

    else if(board[x-1][y-1]!=0)
{
  printf("pos is occupied!\n");
  continue;
}
//走到这里就说明既合法又没被占用
else 
{
board[x-1][y-1]=who;
break;

}
//走到这里就是合法坐标
//被占了
//一开始我们设置为0就是没人下的
}


void game()
{
int board[row][col];//棋盘
memset(board,0,sizeof(board));//进行对棋盘初始化全部都弄成0
int result=next;

do{

//第一步要先显示棋盘
showboard(board,row,col);
//玩家落子
playermove(board,row,col,player1);
//判定结果
result=isover(board,row,col);

if(next!=result)
{
  break;//游戏结束
}
//走到这里说明用户1走完之后并没有出结

showboard(board,row,col);
playermove(board,row,col,player2);
//判定结果
result=isover( board,row,col);

if(next!=result)
{
  break;//游戏结束
}


}while(1);
//循环退出了，
//p1赢了
//p2赢了
//平局
//

switch(result)
{

  case player1_win:
    printf("恭喜用户1，你已经赢了！\n");
    break;
  case player2_win:
    printf("恭喜用户2，你已经赢了！\n");
    break;
  case draw:
    printf("平局\n");
    break;
  default:
  //do nothing
    break;

}


showboard(board,row,col);



}
