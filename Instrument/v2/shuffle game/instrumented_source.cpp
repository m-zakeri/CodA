#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<dos.h>
#include<graphics.h>
#define true  1
#define false 0

//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

void disp();
void printmenu();
void intro();
void levelmenu();
void easy();
void initial(int x);
void draw(int x, int y, int i);
void userwin(int no);
int check(int key);
int load,i,step,level,num[25],win;
void main()
{
logFile << "main 1" << std::endl;

    int gdriver = DETECT, gmode, errorcode;
    initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
    intro();
    levelmenu();
    clrscr();
    cleardevice();
    setbkcolor(RED);
    easy();
}
void levelmenu()
{
logFile << "levelmenu 1" << std::endl;

    level=0;
    clrscr();
    cleardevice();
    setbkcolor(BLACK);
    settextstyle(1,0,2);
    setcolor(GREEN);
    outtextxy(240,240,"Press 1 to start");
    outtextxy(240,260,"----------------");
    outtextxy(240,280,"1. Start");
    outtextxy(240,300,"2. Rules");
    outtextxy(240,330,"Enter a choice: ");
    gotoxy(50+4,22);
    scanf("%d", &level);
    if(level==2)
    {
logFile << "levelmenu 2" << std::endl;

        outtextxy(20,40,"Read the rules :");
        outtextxy(20,80,"1: Arrange the nos in ascending order");
        outtextxy(20,120,"2: Press the no key to move the nos");
        outtextxy(20,160,"3: X-Exit");
        delay(3000);
        levelmenu();
    }
logFile << "levelmenu 3" << std::endl;

}
void intro()
{
logFile << "intro 1" << std::endl;

    int i,j;
    clrscr();
    cleardevice();
    setbkcolor(BLACK);
    gotoxy (25,12);
    settextstyle(4,0,6);
    for(i=0; logFile << "intro 2" << std::endl && (i<=10); i++)
    {
        setcolor(i%16);
        outtextxy(2,2,"SHUFFLE GAME");
        settextstyle(1,0,7);
        outtextxy(20,200,"");
        delay(100);
        outtextxy(180,200,"1");
        delay(100);
        outtextxy(220,200,"2");
        delay(100);
        outtextxy(260,200,"3");
        delay(100);
        outtextxy(180,300,"4");
        delay(100);
        outtextxy(220,300,"5");
        delay(100);
        outtextxy(260,300,"6");
        delay(100);
        outtextxy(180,400,"7");
        delay(100);
        outtextxy(220,400,"8");
        settextstyle(4,0,8);
        delay(100);
    }
logFile << "intro 3" << std::endl;

}
void printmenu()
{
logFile << "printmenu 1" << std::endl;

    int i;
    gotoxy (33,1);
    printf("SHUFFLE GAME");
    gotoxy (1,2);
    for(i=0; logFile << "printmenu 2" << std::endl && (i<80); i++)
        {
printf("\xcd");
}
logFile << "printmenu 3" << std::endl;

    printf("\t\t\t\tX=exit game\n");
    for(i=0; logFile << "printmenu 4" << std::endl && (i<80); i++)
        {
printf("\xcd");
}
logFile << "printmenu 5" << std::endl;

    gotoxy (35,23);
    printf("Moves = %d", step);
}
void easy()
{
logFile << "easy 1" << std::endl;

    int i, x, y,key,valid;
    char press[2];
    if(load==false)
        {
logFile << "easy 2" << std::endl;
initial(9);
}
    else
        {
logFile << "easy 3" << std::endl;
load=false;
}
logFile << "easy 4" << std::endl;

    do
    {
logFile << "easy 5" << std::endl;

start:
        logFile << "easy 6" << std::endl;
printmenu();
        i=0;
        for(y=8; logFile << "easy 7" << std::endl && (y<17); y+=4)
            {
for(x=33; logFile << "easy 8" << std::endl && (x<44); x+=5)
            {
                draw(x,y,i);
                i++;
            }
logFile << "easy 9" << std::endl;

}
logFile << "easy 10" << std::endl;

        userwin(8);
        if(win==true)
        {
logFile << "easy 11" << std::endl;

            cleardevice();
            outtextxy(2,2,"You have won the game");
            delay(2000);
            disp();
            delay(2000);
            win=false;
            return;
        }
logFile << "easy 12" << std::endl;

        gotoxy (55,17);
        printf("Tips:");
        gotoxy (61,18);
        printf("Number will move");
        gotoxy (61,19);
        printf("when you key in!");
        gotoxy (43,23);
        fflush(stdin);
        press[0]=toupper(getche());
        if(press[0]=='X')
        {
logFile << "easy 13" << std::endl;

            disp();
            exit(1);
        }
logFile << "easy 14" << std::endl;

        key=atoi(press);
        if((valid=check(key))==false)
            {
logFile << "easy 15" << std::endl;
goto start;
}
logFile << "easy 16" << std::endl;

        step++;
        if(step==50)
        {
logFile << "easy 17" << std::endl;

            cleardevice();
            outtextxy(20,200,"YOU HAVE SURPASSED MAXIMUM POSSIBLE MOVES");
            delay(1500);
            disp();
            delay(2500);
            exit(1);
        }
logFile << "easy 18" << std::endl;

        for(i=0; logFile << "easy 19" << std::endl && (i<9); i++)
        {
            if(num[i]==key)
                {
logFile << "easy 20" << std::endl;
num[i]=0;
}
            else {
logFile << "easy 21" << std::endl;
if(num[i]==0)
                {
logFile << "easy 22" << std::endl;
num[i]=key;
}
logFile << "easy 23" << std::endl;

}
logFile << "easy 24" << std::endl;

        }
logFile << "easy 25" << std::endl;

    }
    while(logFile << "easy 25" << std::endl && (true));
logFile << "easy 26" << std::endl;

}


void initial(int x)
{
logFile << "initialintx 1" << std::endl;

    int i,no;
    step=0;
    no=0%x;
    if(no==1)
        {
logFile << "initialintx 2" << std::endl;
no+=5;
}
logFile << "initialintx 3" << std::endl;

    for(i=0; logFile << "initialintx 4" << std::endl && (i<x); i++)
    {
        num[i]=no;
        no+=2;
        if(no>=x)
            {
logFile << "initialintx 5" << std::endl;
if(!(no%2))
                {
logFile << "initialintx 6" << std::endl;
no=1;
}
            else
                {
logFile << "initialintx 7" << std::endl;
no=0;
}
logFile << "initialintx 8" << std::endl;

}
logFile << "initialintx 9" << std::endl;

    }
logFile << "initialintx 10" << std::endl;

}
void draw(int x, int y, int i)
{
logFile << "drawintxintyinti 1" << std::endl;

    gotoxy (x,y);
    if(level==1)
    {
logFile << "drawintxintyinti 2" << std::endl;

        printf("%c%c%c",201,205,187);
        gotoxy (x,y+1);
        printf("%c",186);
        if(num[i]==0)
            {
logFile << "drawintxintyinti 3" << std::endl;
printf(" ");
}
        else
            {
logFile << "drawintxintyinti 4" << std::endl;
printf("%d", num[i]);
}
logFile << "drawintxintyinti 5" << std::endl;

        printf("%c",186);
        gotoxy (x,y+2);
        printf("%c%c%c",200,205,188);
    }
logFile << "drawintxintyinti 6" << std::endl;

}
void disp()
{
logFile << "disp 1" << std::endl;

    cleardevice();
    setbkcolor(BLACK);
    settextstyle(4,0,4);
    setcolor(RED);
    outtextxy(200,100,"CREDITS:");
    settextstyle(2,0,13);
    outtextxy(300,220,"CBSEPORTAL");
    outtextxy(300,260,"Class: XII-A");
    outtextxy(300,300,"MDPS");
    delay(2500);
}
int check(int key)
{
logFile << "checkintkey 1" << std::endl;

    int i, valid=false;
    if(level==1)
        {
logFile << "checkintkey 2" << std::endl;
for(i=0; logFile << "checkintkey 3" << std::endl && (i<9); i++)
        {
            if(num[i]==key)
            {
logFile << "checkintkey 4" << std::endl;

                valid=true;
                switch(i)
                {
                case 0:
                    logFile << "checkintkey 5" << std::endl;
if(num[1]!=0 && num[3]!=0){
logFile << "checkintkey 6" << std::endl;
valid=false;
}
logFile << "checkintkey 7" << std::endl;

                    break;
                case 1:
                    logFile << "checkintkey 8" << std::endl;
if(num[0]!=0 && (num[2]!=0 && num[4]!=0))
                        {
logFile << "checkintkey 9" << std::endl;
valid=false;
}
logFile << "checkintkey 10" << std::endl;

                    break;
                case 2:
                    logFile << "checkintkey 11" << std::endl;
if(num[1]!=0 && num[5]!=0){
logFile << "checkintkey 12" << std::endl;
valid=false;
}
logFile << "checkintkey 13" << std::endl;

                    break;
                case 3:
                    logFile << "checkintkey 14" << std::endl;
if(num[0]!=0 && (num[4]!=0 && num[6]!=0))
                        {
logFile << "checkintkey 15" << std::endl;
valid=false;
}
logFile << "checkintkey 16" << std::endl;

                    break;
                case 4:
                    logFile << "checkintkey 17" << std::endl;
if((num[1]!=0 && num[3]!=0) &&
                            (num[5]!=0 && num[7]!=0)){
logFile << "checkintkey 18" << std::endl;
valid=false;
}
logFile << "checkintkey 19" << std::endl;

                    break;
                case 5:
                    logFile << "checkintkey 20" << std::endl;
if(num[2]!=0 && (num[4]!=0 && num[8]!=0))
                        {
logFile << "checkintkey 21" << std::endl;
valid=false;
}
logFile << "checkintkey 22" << std::endl;

                    break;
                case 6:
                    logFile << "checkintkey 23" << std::endl;
if(num[3]!=0 && num[7]!=0){
logFile << "checkintkey 24" << std::endl;
valid=false;
}
logFile << "checkintkey 25" << std::endl;

                    break;
                case 7:
                    logFile << "checkintkey 26" << std::endl;
if(num[4]!=0 && (num[6]!=0 && num[8]!=0))
                        {
logFile << "checkintkey 27" << std::endl;
valid=false;
}
logFile << "checkintkey 28" << std::endl;

                    break;
                case 8:
                    logFile << "checkintkey 29" << std::endl;
if(num[5]!=0 && num[7]!=0){
logFile << "checkintkey 30" << std::endl;
valid=false;
}
logFile << "checkintkey 31" << std::endl;

                    break;
                default:
                    logFile << "checkintkey 32" << std::endl;
valid=false;
                    break;
                }
logFile << "checkintkey 33" << std::endl;

            }
logFile << "checkintkey 34" << std::endl;

        }
logFile << "checkintkey 35" << std::endl;

}
logFile << "checkintkey 36" << std::endl;

    return valid;
}
void userwin(int no)
{
logFile << "userwinintno 1" << std::endl;

    int i;
    for(i=0; logFile << "userwinintno 2" << std::endl && (i<no); i++)
        {
if(num[i]!=i+1)
        {
logFile << "userwinintno 3" << std::endl;

            win=false;
            break;
        }
        else
            {
logFile << "userwinintno 4" << std::endl;
win=true;
}
logFile << "userwinintno 5" << std::endl;

}
logFile << "userwinintno 6" << std::endl;

}
