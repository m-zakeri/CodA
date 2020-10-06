#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>



//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

void draw_line(int n,char ch);
void board();
void gamescore(char name1[],char name2[],int p1, int p2);
void play_dice(int &score);

void main()
{
logFile << "main 1" << std::endl;

    int player1=0,player2=0,lastposition;
    char player1name[80],player2name[80];
    clrscr();
    randomize();
    draw_line(50,'=');
    cout<<"\n\n\n\n\t\tSNAKE LADDER GAME\n\n\n\n";
    draw_line(50,'=');
    cout<<"\n\n\nEnter Name of player 1 :";
    gets(player1name);
    cout<<nter Name of player 2 :    gets(player2name);
    while(logFile << "main 2" << std::endl && (player1<=100 && player2<=100))
    {
        board();
        gamescore(player1name,player2name,player1,player2);
        cout<<"\n\n--->" <<player1name<<" Now your Turn >> Press any key to play ";
        getch();
        lastposition=player1;
        play_dice(player1);
        if(player1<lastposition)
            {
logFile << "main 3" << std::endl;
cout<<"\n\aOops!! Snake found !! You are at postion "<<player1<<"\n";
}
        else {
logFile << "main 4" << std::endl;
if(player1>lastposition+6)
            {
logFile << "main 5" << std::endl;
cout<<"\nGreat!! you got a ladder !! You are at position "<<player1;
}
logFile << "main 6" << std::endl;

}
logFile << "main 7" << std::endl;

        cout<<"\n\n--->"<<player2name<<" Now your Turn >> Press any key to play ";
        getch();
        lastposition=player2;
        play_dice(player2);
        if(player2<lastposition)
            {
logFile << "main 8" << std::endl;
cout<<"\n\n\aOops!! Snake found !! You are at position "<<player2<<"\n";
}
        else {
logFile << "main 9" << std::endl;
if(player2>lastposition+6)
            {
logFile << "main 10" << std::endl;
cout<<"\n\nGreat!! you got a ladder !! You are at position "<<player2<<"\n";
}
logFile << "main 11" << std::endl;

}
logFile << "main 12" << std::endl;

        getch();
    }
logFile << "main 13" << std::endl;

    clrscr();
    cout<<"\n\n\n";
    draw_line(50,'+');
    cout<<"\n\n\t\tRESULT\n\n";
    draw_line(50,'+');
    cout<<endl;
    gamescore(player1name,player2name,player1,player2);
    cout<<"\n\n\n";
    if(player1>=player2)
        {
logFile << "main 14" << std::endl;
cout<<player1name<<" !! You are the winner of the game\n\n";
}
    else
        {
logFile << "main 15" << std::endl;
cout<<player2name<<" !! You are the winner of the game\n\n";
}
logFile << "main 16" << std::endl;

    draw_line(50,'+');
    getch();
}


void draw_line(int n,char ch)
{
logFile << "drawlineintncharch 1" << std::endl;

    for(int i=0; logFile << "drawlineintncharch 2" << std::endl && (i<n); i++)
        {
cout<<ch;
}
logFile << "drawlineintncharch 3" << std::endl;

}

void board()
{
logFile << "board 1" << std::endl;

    clrscr();
    cout<<"\n\n";
    draw_line(50,'-');
    cout<<"\n\t\tSNAKE AT POSITION\n";
    draw_line(50,'-');
    cout<<"\n\tFrom 98 to 28 \n\tFrom 95 to 24\n\tFrom 92 to 51\n\tFrom 83 to 19\n\tFrom 73 to  1\n\tFrom 69 to 33\n\tFrom 64 to 36\n\tFrom 59 to 17\n\tFrom 55 to  7\n\tFrom 52 to 11\n\tFrom 48 to  9\n\tFrom 46 to  5\n\tFrom 44 to 22\n\n";
    draw_line(50,'-');
    cout<<"\n\t\t LADDER AT POSITION\n";
    draw_line(50,'-');
    cout<<"\n\tFrom  8 to 26\n\tFrom 21 to 82\n\tFrom 43 to 77\n\tFrom 50 to 91\n\tFrom 62 to 96\n\tFrom 66 to 87\n\tFrom 80 to 100\n";
    draw_line(50,'-');
    cout<<endl;
}

void gamescore(char name1[],char name2[],int p1, int p2)
{
logFile << "gamescorecharname1charname2intp1intp2 1" << std::endl;

    cout<<"\n";
    draw_line(50,'~');
    cout<<"\n\t\tGAME STATUS\n";
    draw_line(50,'~');
    cout<<"\n\t--->"<<name1<<" is at position "<<p1<<endl;
    cout<<"\t--->"<<name2<<" is at position "<<p2<<endl;
    draw_line(50,'_');
    cout<<endl;
}

void play_dice(int &score)
{
logFile << "playdiceintscore 1" << std::endl;

    int dice;
    dice=random(6)+1;
    cout<<"\nYou got "<<dice<<" Point !! ";
    score=score+dice;
    cout<<"Now you are at position "<<score;
    switch(score)
    {
    case 98 :
        logFile << "playdiceintscore 2" << std::endl;
score=28;
        break;
    case 95 :
        logFile << "playdiceintscore 3" << std::endl;
score=24;
        break;
    case 92 :
        logFile << "playdiceintscore 4" << std::endl;
score=51;
        break;
    case 83 :
        logFile << "playdiceintscore 5" << std::endl;
score=19;
        break;
    case 73 :
        logFile << "playdiceintscore 6" << std::endl;
score=1;
        break;
    case 69 :
        logFile << "playdiceintscore 7" << std::endl;
score=33;
        break;
    case 64 :
        logFile << "playdiceintscore 8" << std::endl;
score=36;
        break;
    case 59 :
        logFile << "playdiceintscore 9" << std::endl;
score=17;
        break;
    case 55 :
        logFile << "playdiceintscore 10" << std::endl;
score=7;
        break;
    case 52 :
        logFile << "playdiceintscore 11" << std::endl;
score=11;
        break;
    case 48 :
        logFile << "playdiceintscore 12" << std::endl;
score=9;
        break;
    case 46 :
        logFile << "playdiceintscore 13" << std::endl;
score=5;
        break;
    case 44 :
        logFile << "playdiceintscore 14" << std::endl;
score=22;
        break;
    case 8  :
        logFile << "playdiceintscore 15" << std::endl;
score=26;
        break;
    case 21 :
        logFile << "playdiceintscore 16" << std::endl;
score=82;
        break;
    case 43 :
        logFile << "playdiceintscore 17" << std::endl;
score=77;
        break;
    case 50 :
        logFile << "playdiceintscore 18" << std::endl;
score=91;
        break;
    case 54 :
        logFile << "playdiceintscore 19" << std::endl;
score=93;
        break;
    case 62 :
        logFile << "playdiceintscore 20" << std::endl;
score=96;
        break;
    case 66 :
        logFile << "playdiceintscore 21" << std::endl;
score=87;
        break;
    case 80 :
        logFile << "playdiceintscore 22" << std::endl;
score=100;
    }
logFile << "playdiceintscore 23" << std::endl;

}
