#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

int a[9][9],b[9][9],r[60][2];
int row, col, icount, mode;
char solh;
void main()
{
logFile << "main 1" << std::endl;



    void readvalues(void), display(void),generate(void);
    int solve(),checkmat(), checkrow(), checkcolumn(),check(),isfixed();
    int i,j,error;
    char c;
    clrscr();
    printf("\t\t\t   SUDOKU SOLVER by:\n\n\t\t\t  \n\t\t\t   MCA-M.Tech CSE, Lovely Professional University\n\t\t\t   Email:@hotmail.com");
    printf("\n\n\n\n\t\tEnter '1' to GENERATE SuDoKu Puzzle\n\n\t\tEnter any other key to SOLVE SuDoKu\n\n\n\n\t\tEnter: ");
    scanf("%c",&c);
    if(c=='1')
    {
logFile << "main 2" << std::endl;

        getchar();
        generate();
        if(solh=='y' || solh=='Y')
            {
logFile << "main 3" << std::endl;
readvalues();
}
logFile << "main 4" << std::endl;

        for(i=0; logFile << "main 5" << std::endl && (i<9); i++)
            {
for(j=0; logFile << "main 6" << std::endl && (j<9); j++)
                {
a[i][j]=b[i][j];
}
logFile << "main 7" << std::endl;

}
logFile << "main 8" << std::endl;

        clrscr();
        display();
        getchar();
        getchar();
        exit(0);
    }
logFile << "main 9" << std::endl;

    clrscr();
    printf("\n\n\t\t\tHOW TO ENTER ELEMENTS\n");
    printf("\n\n1.Enter the elements by specifying the row and column number of\n  corresponding location");
    printf("\n\n2.Each row and column start from 1 and end at 9 (not from 0 to 8)");
    printf("\n\n3.After finishing entering the elements, enter zeroes (0)\n  for row or column");
    printf("\n\n4.If an element entered in a wrong location has to be deleted,\n  enter zero in that location");
    printf("\n\n\n\n\t\t\t  Enter any key to continue");
    getchar();
read:
    logFile << "main 10" << std::endl;
icount=0;
    row=0;
    col=0;
    for(i=0; logFile << "main 11" << std::endl && (i<9); i++)
        {
for(j=0; logFile << "main 12" << std::endl && (j<9); j++)
            {
a[i][j]=0;
}
logFile << "main 13" << std::endl;

}
logFile << "main 14" << std::endl;

    for(i=0; logFile << "main 15" << std::endl && (i<60); i++)
    {
        r[i][0]=20;
        r[i][1]=20;
    }
logFile << "main 16" << std::endl;

    clrscr();
    readvalues();
    getchar();
    clrscr();
ask:
    logFile << "main 17" << std::endl;
display();
    printf("\n\nEnter 'm' to MODIFY\nEnter 'r' to RE-ENTER\nEnter any other key for SUDOKU Solution: ");
    scanf("%c",&c);
    if(c=='r' || c=='R')
    {
logFile << "main 18" << std::endl;

        clrscr();
        goto read;
    }
logFile << "main 19" << std::endl;

    if(c=='m' || c=='M')
    {
logFile << "main 20" << std::endl;

        printf("\n\n");
        readvalues();
        clrscr();
        getchar();
        goto ask;
    }
logFile << "main 21" << std::endl;

next:
    logFile << "main 22" << std::endl;
error=solve();
    clrscr();
    display();
    if(error==0)
        {
logFile << "main 23" << std::endl;
printf("\n\n\n\n\rNO SUOLUTION or TOO MANY MODIFICATIONS");
}
logFile << "main 24" << std::endl;

    cprintf("\n\n\n\n\n\rEnter c to continue and any other key to exit: ");
    scanf("%c",&c);
    if(c=='c')
        {
logFile << "main 25" << std::endl;
goto read;
}
logFile << "main 26" << std::endl;

    getchar();
}

/*FUNTION TO READ ELEMENTS*/

void readvalues()
{
logFile << "readvalues 1" << std::endl;

    int i=icount,j,x,y,chek;
    void display(void);
    int check(int,int);
    clrscr();
    do
    {
logFile << "readvalues 2" << std::endl;

        display();
        printf("\n");
row:
        logFile << "readvalues 3" << std::endl;
printf("\n\nEnter row: ");
        scanf("%d",&r[i][0]);
        if(r[i][0]==0)
        {
logFile << "readvalues 4" << std::endl;

            r[i][0]=100;
            r[i][1]=100;
            break;
        }
logFile << "readvalues 5" << std::endl;

        if(r[i][0]>10 || r[i][0]<0)
        {
logFile << "readvalues 6" << std::endl;

            printf("\nInvalid size\nEnter again");
            r[i][0]=20;
            r[i][1]=20;
            getchar();
            goto row;
        }
logFile << "readvalues 7" << std::endl;

column:
        logFile << "readvalues 8" << std::endl;
printf("Enter column: ");
        scanf("%d",&r[i][1]);
        if(r[i][1]==0)
        {
logFile << "readvalues 9" << std::endl;

            r[i][0]=100;
            r[i][1]=100;
            break;
        }
logFile << "readvalues 10" << std::endl;

        if(r[i][1]<0 || r[i][1]>10)
        {
logFile << "readvalues 11" << std::endl;

            printf("\nInvalid size\nEnter again\n\n");
            r[i][0]=20;
            r[i][1]=20;
            getchar();
            goto column;
        }
logFile << "readvalues 12" << std::endl;

        r[i][0]=r[i][0]-1;
        r[i][1]=r[i][1]-1;
        x=r[i][0];
        y=r[i][1];
        if(solh=='y' || solh=='Y')
            {
logFile << "readvalues 13" << std::endl;
for(j=0; logFile << "readvalues 14" << std::endl && (j<icount); j++)
            {
                if(x==r[j][0] && y==r[j][1])
                {
logFile << "readvalues 15" << std::endl;

                    printf("This location is fixed and cannot be changed");
                    goto row;
                }
                else
                    {
logFile << "readvalues 16" << std::endl;
r[i][0]=20;
}
logFile << "readvalues 17" << std::endl;

                r[i][1]=20;
            }
logFile << "readvalues 18" << std::endl;

}
logFile << "readvalues 19" << std::endl;

scan:
        logFile << "readvalues 20" << std::endl;
printf("Enter the corresponding number: ");
        scanf("%d",&a[x][y]);
        if(a[x][y]==0)
        {
logFile << "readvalues 21" << std::endl;

            for(j=0; logFile << "readvalues 22" << std::endl && (j<icount); j++)
            {
                if(x==r[j][0] && y==r[j][1])
                {
logFile << "readvalues 23" << std::endl;

                    r[j][0]=20;
                    r[j][1]=20;
                    goto end;
                }
logFile << "readvalues 24" << std::endl;

                if(solh=='y' || solh=='Y')
                {
logFile << "readvalues 25" << std::endl;

                    r[i][0]=20;
                    r[i][1]=20;
                    goto end;
                }
logFile << "readvalues 26" << std::endl;

            }
logFile << "readvalues 27" << std::endl;

        }
logFile << "readvalues 28" << std::endl;

        if(a[x][y]>9 || a[x][y]<=0)
        {
logFile << "readvalues 29" << std::endl;

            printf("\nNumber out of range\nEnter again\n\n");
            a[x][y]=0;
            goto scan;
        }
        else
        {
logFile << "readvalues 30" << std::endl;

            chek=check(x,y);
            if(chek==0)
            {
logFile << "readvalues 31" << std::endl;

                printf("\nInconsistent number\nEnter again");
                a[x][y]=0;
                r[i][0]=20;
                r[i][1]=20;
                goto row;
            }
logFile << "readvalues 32" << std::endl;

        }
logFile << "readvalues 33" << std::endl;

        if(solh!='y' && solh!='Y')
        {
logFile << "readvalues 34" << std::endl;

            icount++;
            i++;
        }
logFile << "readvalues 35" << std::endl;

end:
        logFile << "readvalues 36" << std::endl;
clrscr();
    }
    while(logFile << "readvalues 36" << std::endl && (r[i-1][0]!=-1 || r[i-1][1]!=-1));
logFile << "readvalues 37" << std::endl;

}

isfixed(int count, int m, int n)
{
logFile << "isfixedintcountintmintn 1" << std::endl;

    int i;
    for(i=0; logFile << "isfixedintcountintmintn 2" << std::endl && (i<count); i++)
        {
if(m==r[i][0] && n==r[i][1])
            {
logFile << "isfixedintcountintmintn 3" << std::endl;
return(1);
}
logFile << "isfixedintcountintmintn 4" << std::endl;

}
logFile << "isfixedintcountintmintn 5" << std::endl;

    return(0);
}

/*FUNCTION TO DISPLAY SUDOKU*/

void display()
{
logFile << "display 1" << std::endl;

    int i,j,k,fixed;
    gotoxy(6,0);
    for(i=0; logFile << "display 2" << std::endl && (i<10); i++)
    {
        if(i%3==0)
        {
logFile << "display 3" << std::endl;

            textcolor(WHITE);
            if(i!=0)
                {
logFile << "display 4" << std::endl;
printf("\n");
}
logFile << "display 5" << std::endl;

            printf("\t\t");
            for(k=0; logFile << "display 6" << std::endl && (k<45); k++)
                {
cprintf("*");
}
logFile << "display 7" << std::endl;

            if(i==9)
                {
logFile << "display 8" << std::endl;
goto end;
}
logFile << "display 9" << std::endl;

        }
logFile << "display 10" << std::endl;

        if(i%3!=0)
        {
logFile << "display 11" << std::endl;

            textcolor(WHITE);
            printf("\n\t\t");
            printf("|\t\t\b|\t\t\b\b|\t\t\t\b\b\b\b|");
            printf("\n\t\t");
        }
        else
            {
logFile << "display 12" << std::endl;
printf("\n\t\t");
}
logFile << "display 13" << std::endl;

        for(j=0; logFile << "display 14" << std::endl && (j<9); j++)
        {
            if(j%3==0)
            {
logFile << "display 15" << std::endl;

                if(a[i][j]==0)
                {
logFile << "display 16" << std::endl;

                    textcolor(WHITE);
                    cprintf("|");
                    for(k=0; logFile << "display 17" << std::endl && (k<4); k++)
                        {
printf(" ");
}
logFile << "display 18" << std::endl;

                }
                else
                {
logFile << "display 19" << std::endl;

                    textcolor(WHITE);
                    cprintf("| ",a[i][j]);
                    fixed=isfixed(icount,i,j);
                    if(fixed==1)
                        {
logFile << "display 20" << std::endl;
textcolor(LIGHTRED);
}
                    else
                        {
logFile << "display 21" << std::endl;
textcolor(LIGHTGREEN);
}
logFile << "display 22" << std::endl;

                    cprintf("%d  ",a[i][j]);
                }
logFile << "display 23" << std::endl;

            }
            else
            {
logFile << "display 24" << std::endl;

                if(a[i][j]==0)
                    {
logFile << "display 25" << std::endl;
for(k=0; logFile << "display 26" << std::endl && (k<5); k++)
                        {
printf(" ");
}
logFile << "display 27" << std::endl;

}
                else
                {
logFile << "display 28" << std::endl;

                    fixed=isfixed(icount,i,j);
                    if(fixed==1)
                        {
logFile << "display 29" << std::endl;
textcolor(LIGHTRED);
}
                    else
                        {
logFile << "display 30" << std::endl;
textcolor(LIGHTGREEN);
}
logFile << "display 31" << std::endl;

                    cprintf("  %d  ",a[i][j]);
                }
logFile << "display 32" << std::endl;

            }
logFile << "display 33" << std::endl;

        }
logFile << "display 34" << std::endl;

        textcolor(WHITE);
        cprintf("\b|");
    }
logFile << "display 35" << std::endl;

end:
logFile << "display 36" << std::endl;
}


int checkmat(int m, int n)
{
    int x,y;
    for(x=(m/3)*3; logFile << "display 37" << std::endl && (x<((m/3)*3+3)); x++)
        {
for(y=(n/3)*3; logFile << "display 38" << std::endl && (y<((n/3)*3+3)); y++)
        {
            if(m!=x && n!=y)
                {
logFile << "display 39" << std::endl;
if(a[m][n]==a[x][y])
                    {
logFile << "display 40" << std::endl;
return(0);
}
logFile << "display 41" << std::endl;

}
logFile << "display 42" << std::endl;

        }
logFile << "display 43" << std::endl;

}
logFile << "display 44" << std::endl;

    return(1);
}


int checkrow(int m, int n)
{
logFile << "checkrowintmintn 1" << std::endl;

    int x;
    for(x=0; logFile << "checkrowintmintn 2" << std::endl && (x<9); x++)
    {
        if(x!=n)
            {
logFile << "checkrowintmintn 3" << std::endl;
if(a[m][n]==a[m][x])
                {
logFile << "checkrowintmintn 4" << std::endl;
return(0);
}
logFile << "checkrowintmintn 5" << std::endl;

}
logFile << "checkrowintmintn 6" << std::endl;

    }
logFile << "checkrowintmintn 7" << std::endl;

    return(1);
}


int checkcolumn(int m, int n)
{
logFile << "checkcolumnintmintn 1" << std::endl;

    int x;
    for(x=0; logFile << "checkcolumnintmintn 2" << std::endl && (x<9); x++)
    {
        if(x!=m)
            {
logFile << "checkcolumnintmintn 3" << std::endl;
if(a[m][n]==a[x][n])
                {
logFile << "checkcolumnintmintn 4" << std::endl;
return(0);
}
logFile << "checkcolumnintmintn 5" << std::endl;

}
logFile << "checkcolumnintmintn 6" << std::endl;

    }
logFile << "checkcolumnintmintn 7" << std::endl;

    return(1);
}

/*FUNCTION TO CHECK CONSISTENCY OF AN ELEMENT*/

int check(int m,int n)
{
logFile << "checkintmintn 1" << std::endl;

    int c;
    c=checkmat(m,n);
    if(c==1)
        {
logFile << "checkintmintn 2" << std::endl;
c=c*checkrow(m,n);
}
    else
        {
logFile << "checkintmintn 3" << std::endl;
return(c);
}
logFile << "checkintmintn 4" << std::endl;

    if(c==1)
        {
logFile << "checkintmintn 5" << std::endl;
c=c*checkcolumn(m,n);
}
    else
        {
logFile << "checkintmintn 6" << std::endl;
return(c);
}
logFile << "checkintmintn 7" << std::endl;

    return(c);
}

/*FUNCTION TO SOLVE SUDOKU*/

solve()
{
logFile << "solve 1" << std::endl;

    int i,m=0,n=0,number,c,fixed;

mainallot:

    logFile << "solve 2" << std::endl;
for(m=row; logFile << "solve 3" << std::endl && (m<9); m++)
    {
        n=col;
        while(logFile << "solve 4" << std::endl && (n<9))
        {
            number=1;
            fixed=isfixed(icount,m,n);
            if(fixed==0)
            {
logFile << "solve 5" << std::endl;

allot:
                logFile << "solve 6" << std::endl;
a[m][n]=number;
                c=check(m,n);
                if(c==0)
                {
logFile << "solve 7" << std::endl;

                    number++;
                    if(number>9)
                    {
logFile << "solve 8" << std::endl;

                        a[m][n]=0;
                        if(n==0)
                        {
logFile << "solve 9" << std::endl;

                            row=m-1;
                            col=8;
                            if(row<0)
                                {
logFile << "solve 10" << std::endl;
return(0);
}
logFile << "solve 11" << std::endl;

                            goto backadjust;
                        }
                        else
                        {
logFile << "solve 12" << std::endl;

                            row=m;
                            col=n-1;
                            if(row<0 || col<0)
                                {
logFile << "solve 13" << std::endl;
return(0);
}
logFile << "solve 14" << std::endl;

                            goto backadjust;
                        }
logFile << "solve 15" << std::endl;

                    }
logFile << "solve 16" << std::endl;

                    goto allot;
                }
logFile << "solve 17" << std::endl;

            }
logFile << "solve 18" << std::endl;

            n++;
            if(n>8)
                {
logFile << "solve 19" << std::endl;
col=0;
}
logFile << "solve 20" << std::endl;

        }
logFile << "solve 21" << std::endl;

    }
logFile << "solve 22" << std::endl;

    return(1);

backadjust:

    logFile << "solve 23" << std::endl;
fixed=isfixed(icount,row,col);
    if(fixed==0)
    {
logFile << "solve 24" << std::endl;

        number=a[row][col];
allot1:
        logFile << "solve 25" << std::endl;
number++;
        a[row][col]=number;
        if(number>9)
        {
logFile << "solve 26" << std::endl;

            a[row][col]=0;
            if(col==0)
            {
logFile << "solve 27" << std::endl;

                row--;
                col=8;
                if(row<0)
                    {
logFile << "solve 28" << std::endl;
return(0);
}
logFile << "solve 29" << std::endl;

                goto backadjust;
            }
            else
            {
logFile << "solve 30" << std::endl;

                col--;
                if(col<0)
                    {
logFile << "solve 31" << std::endl;
return(0);
}
logFile << "solve 32" << std::endl;

                goto backadjust;
            }
logFile << "solve 33" << std::endl;

        }
logFile << "solve 34" << std::endl;

        c=check(row,col);
        if(c==0)
            {
logFile << "solve 35" << std::endl;
goto allot1;
}
        else
        {
logFile << "solve 36" << std::endl;

            if(col==8)
            {
logFile << "solve 37" << std::endl;

                row++;
                if(row>8)
                    {
logFile << "solve 38" << std::endl;
return(0);
}
logFile << "solve 39" << std::endl;

                col=0;
                goto mainallot;
            }
            else
            {
logFile << "solve 40" << std::endl;

                col++;
                if(col>8)
                    {
logFile << "solve 41" << std::endl;
return(0);
}
logFile << "solve 42" << std::endl;

                goto mainallot;
            }
logFile << "solve 43" << std::endl;

        }
logFile << "solve 44" << std::endl;

    }
    else
    {
logFile << "solve 45" << std::endl;

        if(col==0)
        {
logFile << "solve 46" << std::endl;

            row--;
            col=8;
            if(row<0)
                {
logFile << "solve 47" << std::endl;
return(0);
}
logFile << "solve 48" << std::endl;

            goto backadjust;
        }
        else
        {
logFile << "solve 49" << std::endl;

            col--;
            if(col<0)
                {
logFile << "solve 50" << std::endl;
return(0);
}
logFile << "solve 51" << std::endl;

            goto backadjust;
        }
logFile << "solve 52" << std::endl;

    }
logFile << "solve 53" << std::endl;

}

/*FUNCTION TO GENERATE SODOKU*/

void generate()
{
logFile << "generate 1" << std::endl;

    int c,i,m,n,count=1,fixed,error;
    char choice;
    randomize();
generate:
    logFile << "generate 2" << std::endl;
for(m=0; logFile << "generate 3" << std::endl && (m<9); m++)
        {
for(n=0; logFile << "generate 4" << std::endl && (n<9); n++)
            {
a[m][n]=0;
}
logFile << "generate 5" << std::endl;

}
logFile << "generate 6" << std::endl;

    for(i=0; logFile << "generate 7" << std::endl && (i<60); i++)
    {
        r[i][0]=20;
        r[i][1]=20;
    }
logFile << "generate 8" << std::endl;

    clrscr();
    printf("\n\n\n\n\t\tEnter your choice of difficulty");
    printf("\n\n\n\t\t1.VERY EASY\n\n\t\t2.EASY\n\n\t\t3.MEDIUM\n\n\t\t4.HARD\n\n\n\t\tENTER: ");
    scanf("%c",&choice);
    switch(choice)
    {
    case '1':
        logFile << "generate 9" << std::endl;
mode=34+random(4);
        break;
    case '2':
        logFile << "generate 10" << std::endl;
mode=29+random(4);
        break;
    case '3':
        logFile << "generate 11" << std::endl;
mode=27+random(2);
        break;
    case '4':
        logFile << "generate 12" << std::endl;
mode=25+random(2);
        break;
    default :
        logFile << "generate 13" << std::endl;
getchar();
        goto generate;
    }
logFile << "generate 14" << std::endl;

    a[0][0]=1+random(8);
    r[0][0]=0;
    r[0][1]=0;
    for(count=1; logFile << "generate 15" << std::endl && (count<10); count++)
    {
choose:
        logFile << "generate 16" << std::endl;
m=random(9);
        n=random(9);
        fixed=isfixed(icount,m,n);
        if(fixed==1)
            {
logFile << "generate 17" << std::endl;
goto choose;
}
logFile << "generate 18" << std::endl;

        r[count][0]=m;
        r[count][1]=n;
allot:
        logFile << "generate 19" << std::endl;
a[m][n]=1+random(9);
        if(a[m][n]==0)
            {
logFile << "generate 20" << std::endl;
goto allot;
}
logFile << "generate 21" << std::endl;

        c=check(m,n);
        if(c==0)
            {
logFile << "generate 22" << std::endl;
goto allot;
}
logFile << "generate 23" << std::endl;

    }
logFile << "generate 24" << std::endl;

    icount=count;
    error=solve();
    for(m=0; logFile << "generate 25" << std::endl && (m<9); m++)
        {
for(n=0; logFile << "generate 26" << std::endl && (n<9); n++)
            {
b[m][n]=a[m][n];
}
logFile << "generate 27" << std::endl;

}
logFile << "generate 28" << std::endl;

    row=0;
    col=0;
    for(i=0; logFile << "generate 29" << std::endl && (i<60); i++)
    {
        r[i][0]=20;
        r[i][1]=20;
    }
logFile << "generate 30" << std::endl;

    if(error==0)
        {
logFile << "generate 31" << std::endl;
goto generate;
}
logFile << "generate 32" << std::endl;

    for(count=0; logFile << "generate 33" << std::endl && (count<mode/2); count++)
    {
choose2:
        logFile << "generate 34" << std::endl;
m=random(9);
        n=random(5);
        fixed=isfixed(count,m,n);
        if(fixed==1)
            {
logFile << "generate 35" << std::endl;
goto choose2;
}
logFile << "generate 36" << std::endl;

        r[count][0]=m;
        r[count][1]=n;
        r[count+mode/2][0]=8-m;
        r[count+mode/2][1]=8-n;
    }
logFile << "generate 37" << std::endl;

    for(m=0; logFile << "generate 38" << std::endl && (m<9); m++)
        {
for(n=0; logFile << "generate 39" << std::endl && (n<9); n++)
        {
            fixed=isfixed(mode,m,n);
            if(fixed!=1)
                {
logFile << "generate 40" << std::endl;
a[m][n]=0;
}
logFile << "generate 41" << std::endl;

        }
logFile << "generate 42" << std::endl;

}
logFile << "generate 43" << std::endl;

    icount=mode;
    clrscr();
    display();
    getchar();
    printf("\n\n\nEnter 'y' to solve by yourself\nEnter 's' for solution\nEnter 'm' to generate more sudoku puzzles");
    printf("\nAnd any other key to exit: ");
    scanf("%c", &solh);
    if(solh=='y' || solh=='Y' || solh=='s' || solh=='S')
        {
logFile << "generate 44" << std::endl;
return;
}
logFile << "generate 45" << std::endl;

    getchar();
    if(solh=='m' || solh=='M')
        {
logFile << "generate 46" << std::endl;
goto generate;
}
logFile << "generate 47" << std::endl;

    exit(0);
}
