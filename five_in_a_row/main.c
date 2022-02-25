#include"game.h"
int main()
{
  int quit=0;
  int select=0;
  while(!quit)
  {
   menu();
   printf("请做出你的选择：\n");
scanf("%d",&select);
switch(select)
{
  case 1:
game();
    break;
  case 0:
  quit=1;
    printf("bye!\n");
    break;
  default:
    printf("ERROR\n");

}
}
  return 0;
}
