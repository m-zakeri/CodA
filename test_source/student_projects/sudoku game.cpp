#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
int a[9][9],b[9][9],r[60][2];
int row, col, icount, mode;
char solh;
void main()
{


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
        getchar();
        generate();
        if(solh=='y' || solh=='Y')
            readvalues();
        for(i=0; i<9; i++)
            for(j=0; j<9; j++)
                a[i][j]=b[i][j];
        clrscr();
        display();
        getchar();
        getchar();
        exit(0);
    }
    clrscr();
    printf("\n\n\t\t\tHOW TO ENTER ELEMENTS\n");
    printf("\n\n1.Enter the elements by specifying the row and column number of\n  corresponding location");
    printf("\n\n2.Each row and column start from 1 and end at 9 (not from 0 to 8)");
    printf("\n\n3.After finishing entering the elements, enter zeroes (0)\n  for row or column");
    printf("\n\n4.If an element entered in a wrong location has to be deleted,\n  enter zero in that location");
    printf("\n\n\n\n\t\t\t  Enter any key to continue");
    getchar();
read:
    icount=0;
    row=0;
    col=0;
    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            a[i][j]=0;
    for(i=0; i<60; i++)
    {
        r[i][0]=20;
        r[i][1]=20;
    }
    clrscr();
    readvalues();
    getchar();
    clrscr();
ask:
    display();
    printf("\n\nEnter 'm' to MODIFY\nEnter 'r' to RE-ENTER\nEnter any other key for SUDOKU Solution: ");
    scanf("%c",&c);
    if(c=='r' || c=='R')
    {
        clrscr();
        goto read;
    }
    if(c=='m' || c=='M')
    {
        printf("\n\n");
        readvalues();
        clrscr();
        getchar();
        goto ask;
    }
next:
    error=solve();
    clrscr();
    display();
    if(error==0)
        printf("\n\n\n\n\rNO SUOLUTION or TOO MANY MODIFICATIONS");
    cprintf("\n\n\n\n\n\rEnter c to continue and any other key to exit: ");
    scanf("%c",&c);
    if(c=='c')
        goto read;
    getchar();
}

/*FUNTION TO READ ELEMENTS*/

void readvalues()
{
    int i=icount,j,x,y,chek;
    void display(void);
    int check(int,int);
    clrscr();
    do
    {
        display();
        printf("\n");
row:
        printf("\n\nEnter row: ");
        scanf("%d",&r[i][0]);
        if(r[i][0]==0)
        {
            r[i][0]=100;
            r[i][1]=100;
            break;
        }
        if(r[i][0]>10 || r[i][0]<0)
        {
            printf("\nInvalid size\nEnter again");
            r[i][0]=20;
            r[i][1]=20;
            getchar();
            goto row;
        }
column:
        printf("Enter column: ");
        scanf("%d",&r[i][1]);
        if(r[i][1]==0)
        {
            r[i][0]=100;
            r[i][1]=100;
            break;
        }
        if(r[i][1]<0 || r[i][1]>10)
        {
            printf("\nInvalid size\nEnter again\n\n");
            r[i][0]=20;
            r[i][1]=20;
            getchar();
            goto column;
        }
        r[i][0]=r[i][0]-1;
        r[i][1]=r[i][1]-1;
        x=r[i][0];
        y=r[i][1];
        if(solh=='y' || solh=='Y')
            for(j=0; j<icount; j++)
            {
                if(x==r[j][0] && y==r[j][1])
                {
                    printf("This location is fixed and cannot be changed");
                    goto row;
                }
                else
                    r[i][0]=20;
                r[i][1]=20;
            }
scan:
        printf("Enter the corresponding number: ");
        scanf("%d",&a[x][y]);
        if(a[x][y]==0)
        {
            for(j=0; j<icount; j++)
            {
                if(x==r[j][0] && y==r[j][1])
                {
                    r[j][0]=20;
                    r[j][1]=20;
                    goto end;
                }
                if(solh=='y' || solh=='Y')
                {
                    r[i][0]=20;
                    r[i][1]=20;
                    goto end;
                }
            }
        }
        if(a[x][y]>9 || a[x][y]<=0)
        {
            printf("\nNumber out of range\nEnter again\n\n");
            a[x][y]=0;
            goto scan;
        }
        else
        {
            chek=check(x,y);
            if(chek==0)
            {
                printf("\nInconsistent number\nEnter again");
                a[x][y]=0;
                r[i][0]=20;
                r[i][1]=20;
                goto row;
            }
        }
        if(solh!='y' && solh!='Y')
        {
            icount++;
            i++;
        }
end:
        clrscr();
    }
    while(r[i-1][0]!=-1 || r[i-1][1]!=-1);
}

isfixed(int count, int m, int n)
{
    int i;
    for(i=0; i<count; i++)
        if(m==r[i][0] && n==r[i][1])
            return(1);
    return(0);
}

/*FUNCTION TO DISPLAY SUDOKU*/

void display()
{
    int i,j,k,fixed;
    gotoxy(6,0);
    for(i=0; i<10; i++)
    {
        if(i%3==0)
        {
            textcolor(WHITE);
            if(i!=0)
                printf("\n");
            printf("\t\t");
            for(k=0; k<45; k++)
                cprintf("*");
            if(i==9)
                goto end;
        }
        if(i%3!=0)
        {
            textcolor(WHITE);
            printf("\n\t\t");
            printf("|\t\t\b|\t\t\b\b|\t\t\t\b\b\b\b|");
            printf("\n\t\t");
        }
        else
            printf("\n\t\t");
        for(j=0; j<9; j++)
        {
            if(j%3==0)
            {
                if(a[i][j]==0)
                {
                    textcolor(WHITE);
                    cprintf("|");
                    for(k=0; k<4; k++)
                        printf(" ");
                }
                else
                {
                    textcolor(WHITE);
                    cprintf("| ",a[i][j]);
                    fixed=isfixed(icount,i,j);
                    if(fixed==1)
                        textcolor(LIGHTRED);
                    else
                        textcolor(LIGHTGREEN);
                    cprintf("%d  ",a[i][j]);
                }
            }
            else
            {
                if(a[i][j]==0)
                    for(k=0; k<5; k++)
                        printf(" ");
                else
                {
                    fixed=isfixed(icount,i,j);
                    if(fixed==1)
                        textcolor(LIGHTRED);
                    else
                        textcolor(LIGHTGREEN);
                    cprintf("  %d  ",a[i][j]);
                }
            }
        }
        textcolor(WHITE);
        cprintf("\b|");
    }
end:
}


int checkmat(int m, int n)
{
    int x,y;
    for(x=(m/3)*3; x<((m/3)*3+3); x++)
        for(y=(n/3)*3; y<((n/3)*3+3); y++)
        {
            if(m!=x && n!=y)
                if(a[m][n]==a[x][y])
                    return(0);
        }
    return(1);
}


int checkrow(int m, int n)
{
    int x;
    for(x=0; x<9; x++)
    {
        if(x!=n)
            if(a[m][n]==a[m][x])
                return(0);
    }
    return(1);
}


int checkcolumn(int m, int n)
{
    int x;
    for(x=0; x<9; x++)
    {
        if(x!=m)
            if(a[m][n]==a[x][n])
                return(0);
    }
    return(1);
}

/*FUNCTION TO CHECK CONSISTENCY OF AN ELEMENT*/

int check(int m,int n)
{
    int c;
    c=checkmat(m,n);
    if(c==1)
        c=c*checkrow(m,n);
    else
        return(c);
    if(c==1)
        c=c*checkcolumn(m,n);
    else
        return(c);
    return(c);
}

/*FUNCTION TO SOLVE SUDOKU*/

solve()
{
    int i,m=0,n=0,number,c,fixed;

mainallot:

    for(m=row; m<9; m++)
    {
        n=col;
        while(n<9)
        {
            number=1;
            fixed=isfixed(icount,m,n);
            if(fixed==0)
            {
allot:
                a[m][n]=number;
                c=check(m,n);
                if(c==0)
                {
                    number++;
                    if(number>9)
                    {
                        a[m][n]=0;
                        if(n==0)
                        {
                            row=m-1;
                            col=8;
                            if(row<0)
                                return(0);
                            goto backadjust;
                        }
                        else
                        {
                            row=m;
                            col=n-1;
                            if(row<0 || col<0)
                                return(0);
                            goto backadjust;
                        }
                    }
                    goto allot;
                }
            }
            n++;
            if(n>8)
                col=0;
        }
    }
    return(1);

backadjust:

    fixed=isfixed(icount,row,col);
    if(fixed==0)
    {
        number=a[row][col];
allot1:
        number++;
        a[row][col]=number;
        if(number>9)
        {
            a[row][col]=0;
            if(col==0)
            {
                row--;
                col=8;
                if(row<0)
                    return(0);
                goto backadjust;
            }
            else
            {
                col--;
                if(col<0)
                    return(0);
                goto backadjust;
            }
        }
        c=check(row,col);
        if(c==0)
            goto allot1;
        else
        {
            if(col==8)
            {
                row++;
                if(row>8)
                    return(0);
                col=0;
                goto mainallot;
            }
            else
            {
                col++;
                if(col>8)
                    return(0);
                goto mainallot;
            }
        }
    }
    else
    {
        if(col==0)
        {
            row--;
            col=8;
            if(row<0)
                return(0);
            goto backadjust;
        }
        else
        {
            col--;
            if(col<0)
                return(0);
            goto backadjust;
        }
    }
}

/*FUNCTION TO GENERATE SODOKU*/

void generate()
{
    int c,i,m,n,count=1,fixed,error;
    char choice;
    randomize();
generate:
    for(m=0; m<9; m++)
        for(n=0; n<9; n++)
            a[m][n]=0;
    for(i=0; i<60; i++)
    {
        r[i][0]=20;
        r[i][1]=20;
    }
    clrscr();
    printf("\n\n\n\n\t\tEnter your choice of difficulty");
    printf("\n\n\n\t\t1.VERY EASY\n\n\t\t2.EASY\n\n\t\t3.MEDIUM\n\n\t\t4.HARD\n\n\n\t\tENTER: ");
    scanf("%c",&choice);
    switch(choice)
    {
    case '1':
        mode=34+random(4);
        break;
    case '2':
        mode=29+random(4);
        break;
    case '3':
        mode=27+random(2);
        break;
    case '4':
        mode=25+random(2);
        break;
    default :
        getchar();
        goto generate;
    }
    a[0][0]=1+random(8);
    r[0][0]=0;
    r[0][1]=0;
    for(count=1; count<10; count++)
    {
choose:
        m=random(9);
        n=random(9);
        fixed=isfixed(icount,m,n);
        if(fixed==1)
            goto choose;
        r[count][0]=m;
        r[count][1]=n;
allot:
        a[m][n]=1+random(9);
        if(a[m][n]==0)
            goto allot;
        c=check(m,n);
        if(c==0)
            goto allot;
    }
    icount=count;
    error=solve();
    for(m=0; m<9; m++)
        for(n=0; n<9; n++)
            b[m][n]=a[m][n];
    row=0;
    col=0;
    for(i=0; i<60; i++)
    {
        r[i][0]=20;
        r[i][1]=20;
    }
    if(error==0)
        goto generate;
    for(count=0; count<mode/2; count++)
    {
choose2:
        m=random(9);
        n=random(5);
        fixed=isfixed(count,m,n);
        if(fixed==1)
            goto choose2;
        r[count][0]=m;
        r[count][1]=n;
        r[count+mode/2][0]=8-m;
        r[count+mode/2][1]=8-n;
    }
    for(m=0; m<9; m++)
        for(n=0; n<9; n++)
        {
            fixed=isfixed(mode,m,n);
            if(fixed!=1)
                a[m][n]=0;
        }
    icount=mode;
    clrscr();
    display();
    getchar();
    printf("\n\n\nEnter 'y' to solve by yourself\nEnter 's' for solution\nEnter 'm' to generate more sudoku puzzles");
    printf("\nAnd any other key to exit: ");
    scanf("%c", &solh);
    if(solh=='y' || solh=='Y' || solh=='s' || solh=='S')
        return;
    getchar();
    if(solh=='m' || solh=='M')
        goto generate;
    exit(0);
}
