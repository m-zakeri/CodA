#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>



//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

void draw_line(int n,char ch);
void rules();

void main()
{
logFile << "main 1" << std::endl;

    int balanceamt,amt,no,dice;
    char playername[80],ch;
    clrscr();
    draw_line(60,'=');
    cout<<"\n\n\n\n\t\tCASINO GAME\n\n\n\n";
    draw_line(60,'=');
    cout<<"\n\n\nEnter Your Name  :";
    gets(playername);
    cout<<nter Deposit amount to play game :    logFile << "main 2" << std::endl;
cin>>balanceamt;
    do
    {
logFile << "main 3" << std::endl;

        clrscr();
        rules();
        cout<<"\n\nYour current balance is Rs."<<balanceamt;
        do
        {
logFile << "main 4" << std::endl;

            cout<<"\n\n"<<playername<<" enter money to bet";
            cin>>amt;
            if(amt>balanceamt)
                {
logFile << "main 5" << std::endl;
cout<<"Your betting amount is more than your current balance\n\nRe-enter data\n ";
}
            else
                {
logFile << "main 6" << std::endl;
break;
}
logFile << "main 7" << std::endl;

        }
        while(logFile << "main 7" << std::endl && (1));
logFile << "main 8" << std::endl;

        do
        {
logFile << "main 9" << std::endl;

            cout<<"Enter your lucky number to bet between 1 to 12 :";
            cin>>no;
            if(no<=0||no>12)
                {
logFile << "main 10" << std::endl;
cout<<"Please check the number!! should be between 1 to 12\n\nRe-enter data\n ";
}
            else
                {
logFile << "main 11" << std::endl;
break;
}
logFile << "main 12" << std::endl;

        }
        while(logFile << "main 12" << std::endl && (1));
logFile << "main 13" << std::endl;

        randomize();
        dice=random(12)+1;
        if(dice==no)
        {
logFile << "main 14" << std::endl;

            cout<<"\n\nGood Luck!! You won Rs."<<amt*10;
            balanceamt=balanceamt+amt*10;
        }
        else
        {
logFile << "main 15" << std::endl;

            cout<<"Bad Luck this time !! You lose Rs."<<amt;
            balanceamt=balanceamt-amt;
        }
logFile << "main 16" << std::endl;

        cout<<"\n\nThe winning number was : "<<dice;

        cout<<"\n\n\t"<<playername<<" You have Rs. "<<balanceamt<<endl;
        cout<<"\n\n-->Do you want to play (y/n)? ";
        cin>>ch;
    }
    while(logFile << "main 16" << std::endl && (ch=='Y'|| ch=='y'));
logFile << "main 17" << std::endl;

    clrscr();
    cout<<"\n\n\n";
    draw_line(70,'+');
    cout<<HANKS FOR COME TO CASINO YOUR BALANCE AMOUNT IS RS."<<balanceamt<<"    draw_line(70,'+');
    cout<<"\n\nGame developed by ANIKET RAJPUT\n";
    draw_line(70,'+');
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

void rules()
{
logFile << "rules 1" << std::endl;

    clrscr();
    cout<<"\n\n";
    draw_line(60,'-');
    cout<<"\n\t\tRULES OF THE GAME\n";
    draw_line(60,'-');
    cout<<"\n\t1. Choose any number between 1 to 12\n\t2. If you win you will get 10 times of money you bet\n\t3. If you bet on wrong number you will lose your betting amount\n\n";
    draw_line(60,'-');
    cout<<endl;
}
