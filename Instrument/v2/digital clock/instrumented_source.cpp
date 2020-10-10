#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#define DOTCOLOR 14
#define DIGCOLOR 5

//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

void disp();
void ELLIPS();
class Digital_Clock
{
private:
    int X,Y;
    int SIZE;
    int COLOR;
    int HEIGHT,WIDTH;
    void *VER,*HOR;
public:
    int style;
    Digital_Clock();
    Digital_Clock(int s,int c,int st);
    void bar_make();
    void PutDig(int x,int y,int n);
    void DrawDig(int x,int y,int n);
    ~Digital_Clock();
};
Digital_Clock::Digital_Clock()
{
logFile << "DigitalClock 1" << std::endl;

    style=1;
    SIZE=1;
    HEIGHT=1;
    WIDTH=12;
    COLOR=15;
    bar_make();
}
Digital_Clock::Digital_Clock(int s,int c,int st)
{
logFile << "DigitalClockintsintcintst 1" << std::endl;

    style=st;
    SIZE=s;
    COLOR=c;
    HEIGHT=1;
    WIDTH=6;
    bar_make();
}
void Digital_Clock::bar_make()
{
logFile << "DigitalClockbarmake 1" << std::endl;

    int x,y,w,h;
    int area;
    x=10;
    y=getmaxy()/2;
    w=WIDTH*SIZE;
    h=HEIGHT*SIZE;
    setfillstyle(style,COLOR);
    bar(x+h,y,x+w-h,y+h);
    setcolor(COLOR);
    line(x,y+h/2,x+h,y);
    line(x,y+h/2,x+h,y+h);
    floodfill(x+h/2,y+h/2,COLOR);
    setcolor(COLOR);
    line(x+w-h,y,x+w+-h+h,y+h/2);
    line(x+w-h,y+h,x+w-h+h,y+h/2);
    floodfill(x+w-h+h/2,y+h/2,COLOR);
    area=imagesize(x,y,x+w,y+h);
    HOR=malloc(area);
    getimage(x,y,x+w,y+h,HOR);
    putimage(x,y,HOR,XOR_PUT);
    x=getmaxx()/2;
    y=10;
    h=SIZE*WIDTH;
    w=HEIGHT*SIZE;
    bar(x,y+w,x+w,y+h-w);
    setcolor(COLOR);
    line(x,y+w,x+w/2,y);
    line(x+w,y+w,x+w/2,y);
    floodfill(x+w/2,y+w/2,COLOR);
    setcolor(COLOR);
    line(x,y+h-w,x+w/2,y+h);
    line(x+w,y+h-w,x+w/2,y+h);
    floodfill(x+w/2,y+h-w/2,COLOR);
    area=imagesize(x,y,x+w,y+h);
    VER=malloc(area);
    getimage(x,y,x+w,y+h,VER);
    putimage(x,y,VER,XOR_PUT);
}
void Digital_Clock::PutDig(int x,int y,int n)
{
logFile << "DigitalClockPutDigintxintyintn 1" << std::endl;

    int num,gap,qu,rem;
    gap=(SIZE*HEIGHT);
    num=n;
    if(num==62)
    {
logFile << "DigitalClockPutDigintxintyintn 2" << std::endl;

        DrawDig(x,y,62);
    }
logFile << "DigitalClockPutDigintxintyintn 3" << std::endl;

    if(num==63)
    {
logFile << "DigitalClockPutDigintxintyintn 4" << std::endl;

        DrawDig(x,y,63);
    }
logFile << "DigitalClockPutDigintxintyintn 5" << std::endl;

    if(num>=0&&num<10)
    {
logFile << "DigitalClockPutDigintxintyintn 6" << std::endl;

        DrawDig(x,y,0);
        DrawDig(x+WIDTH*SIZE+HEIGHT*SIZE+gap,y,n);
    }
logFile << "DigitalClockPutDigintxintyintn 7" << std::endl;

    if(num>=10&&num<61)
    {
logFile << "DigitalClockPutDigintxintyintn 8" << std::endl;

        qu=num/10;
        rem=num%10;
        DrawDig(x,y,qu);
        DrawDig(x+WIDTH*SIZE+HEIGHT*SIZE+gap,y,rem);
    }
logFile << "DigitalClockPutDigintxintyintn 9" << std::endl;

}
void Digital_Clock::DrawDig(int x,int y,int n)
{
logFile << "DigitalClockDrawDigintxintyintn 1" << std::endl;

    int H[10][3]= {1,0,1,
                   0,0,0,
                   1,1,1,
                   1,1,1,
                   0,1,0,
                   1,1,1,
                   1,1,1,
                   1,0,0,
                   1,1,1,
                   1,1,1
                  };
    int ph[2][3]= {1,1,0,
                   1,1,0
                  };
    int pv[2][4]= {1,1,1,0,
                   1,1,1,1
                  };
    int V[10][4]= {1,1,1,1,
                   0,1,0,1,
                   0,1,1,0,
                   0,1,0,1,
                   1,1,0,1,
                   1,0,0,1,
                   1,0,1,1,
                   0,1,0,1,
                   1,1,1,1,
                   1,1,0,1
                  };
    int HX[3]= {x,x,x};
    int HY[3]= {y,y+WIDTH*SIZE,y+2*WIDTH*SIZE};
    int VX[4]= {x-(HEIGHT*SIZE)/2,x+WIDTH*SIZE-(HEIGHT*SIZE)/2,x-(HEIGHT*SIZE)/2,x+WIDTH*SIZE-(HEIGHT*SIZE)/2};
    int VY[4]= {y+(HEIGHT*SIZE)/2,y+(HEIGHT*SIZE)/2,y+WIDTH*SIZE+(HEIGHT*SIZE)/2,y+WIDTH*SIZE+(HEIGHT*SIZE)/2};
    int i;
    setfillstyle(1,getpixel(x-1,y-1));
    bar(x-(SIZE*HEIGHT)/2,y,x+WIDTH*SIZE+(SIZE*HEIGHT)/2,y+2*SIZE*WIDTH+HEIGHT*SIZE);
    if(n==62)
    {
logFile << "DigitalClockDrawDigintxintyintn 2" << std::endl;

        for(i=0; logFile << "DigitalClockDrawDigintxintyintn 3" << std::endl && (i<3); i++)
        {
            if(ph[0][i]==1)
            {
logFile << "DigitalClockDrawDigintxintyintn 4" << std::endl;

                putimage(HX[i],HY[i],HOR,XOR_PUT);
            }
logFile << "DigitalClockDrawDigintxintyintn 5" << std::endl;

        }
logFile << "DigitalClockDrawDigintxintyintn 6" << std::endl;

        for(i=0; logFile << "DigitalClockDrawDigintxintyintn 7" << std::endl && (i<4); i++)
        {
            if(pv[0][i]==1)
            {
logFile << "DigitalClockDrawDigintxintyintn 8" << std::endl;

                putimage(VX[i],VY[i],VER,XOR_PUT);
            }
logFile << "DigitalClockDrawDigintxintyintn 9" << std::endl;

        }
logFile << "DigitalClockDrawDigintxintyintn 10" << std::endl;

    }
    else {
logFile << "DigitalClockDrawDigintxintyintn 11" << std::endl;
if(n==63)
    {
logFile << "DigitalClockDrawDigintxintyintn 12" << std::endl;

        for(i=0; logFile << "DigitalClockDrawDigintxintyintn 13" << std::endl && (i<3); i++)
        {
            if(ph[1][i]==1)
            {
logFile << "DigitalClockDrawDigintxintyintn 14" << std::endl;

                putimage(HX[i],HY[i],HOR,XOR_PUT);
            }
logFile << "DigitalClockDrawDigintxintyintn 15" << std::endl;

        }
logFile << "DigitalClockDrawDigintxintyintn 16" << std::endl;

        for(i=0; logFile << "DigitalClockDrawDigintxintyintn 17" << std::endl && (i<4); i++)
        {
            if(pv[1][i]==1)
            {
logFile << "DigitalClockDrawDigintxintyintn 18" << std::endl;

                putimage(VX[i],VY[i],VER,XOR_PUT);
            }
logFile << "DigitalClockDrawDigintxintyintn 19" << std::endl;

        }
logFile << "DigitalClockDrawDigintxintyintn 20" << std::endl;

    }
    else
    {
logFile << "DigitalClockDrawDigintxintyintn 21" << std::endl;

        for(i=0; logFile << "DigitalClockDrawDigintxintyintn 22" << std::endl && (i<3); i++)
        {
            if(H[n][i]==1)
                {
logFile << "DigitalClockDrawDigintxintyintn 23" << std::endl;
putimage(HX[i],HY[i],HOR,XOR_PUT);
}
logFile << "DigitalClockDrawDigintxintyintn 24" << std::endl;

        }
logFile << "DigitalClockDrawDigintxintyintn 25" << std::endl;

        for(i=0; logFile << "DigitalClockDrawDigintxintyintn 26" << std::endl && (i<4); i++)
        {
            if(V[n][i]==1)
                {
logFile << "DigitalClockDrawDigintxintyintn 27" << std::endl;
putimage(VX[i],VY[i],VER,XOR_PUT);
}
logFile << "DigitalClockDrawDigintxintyintn 28" << std::endl;

        }
logFile << "DigitalClockDrawDigintxintyintn 29" << std::endl;

    }
logFile << "DigitalClockDrawDigintxintyintn 30" << std::endl;

}
logFile << "DigitalClockDrawDigintxintyintn 31" << std::endl;

}
Digital_Clock::~Digital_Clock()
{
logFile << "destructorDigitalClock 1" << std::endl;

    delete HOR;
    delete VER;
}
void drawdot();
int color=DOTCOLOR;
void main()
{
logFile << "main 1" << std::endl;

    int gd=DETECT,gm,i;
    initgraph(&gd,&gm,"");
    struct time t;
    int th=t.ti_hour;
    int tm=t.ti_min;
    int ts=t.ti_sec;
    gettime(&t);
    ELLIPS();
    Digital_Clock h(7,DIGCOLOR,1);
    Digital_Clock m(7,DIGCOLOR,1);
    Digital_Clock s(7,DIGCOLOR,1);
    Digital_Clock p(7,DIGCOLOR,1);
    Digital_Clock A(7,DIGCOLOR,1);

    int y=200;
    h.PutDig(20,y,t.ti_hour);
    m.PutDig(220,y,t.ti_min);
    s.PutDig(380,y,t.ti_sec);
    if(t.ti_hour>12)
        {
logFile << "main 2" << std::endl;
p.PutDig(500,y,62);
}
    else
        {
logFile << "main 3" << std::endl;
A.PutDig(500,y,63);
}
logFile << "main 4" << std::endl;

    while(logFile << "main 5" << std::endl && (!kbhit()))
    {
        gettime(&t);
        if(th!=t.ti_hour)
        {
logFile << "main 6" << std::endl;

            th=t.ti_hour;
            h.PutDig(20,y,t.ti_hour);
        }
logFile << "main 7" << std::endl;

        if(tm!=t.ti_min)
        {
logFile << "main 8" << std::endl;

            tm=t.ti_min;
            m.PutDig(220,y,t.ti_min);
        }
logFile << "main 9" << std::endl;

        if(ts!=t.ti_sec)
        {
logFile << "main 10" << std::endl;

            ts=t.ti_sec;
            s.PutDig(380,y,t.ti_sec);
            drawdot();
        }
logFile << "main 11" << std::endl;

    }
logFile << "main 12" << std::endl;

    getch();
}

void drawdot()
{
logFile << "drawdot 1" << std::endl;

    int x,y,gap,size,c;
    gap=8;
    size=10;
    x=170;
    y=200;
    setfillstyle(1,color);
    bar(x+gap,y+gap,x+gap+size,y+gap+size);
    bar(x+gap,y+8*gap,x+gap+size,y+8*gap+size);
    bar(x+gap+170,y+gap,x+gap+size+170,y+gap+size);
    bar(x+gap+170,y+8*gap,x+gap+size+170,y+8*gap+size);
    delay(1);
}
float x,y;
int xc,yc;
void ELLIPS()
{
logFile << "ELLIPS 1" << std::endl;

    int a,b;
    long double p1,p2;
    xc=getmaxx()/2-20;
    yc= getmaxy()/2;
    a=getmaxx()-340;
    b= 120;
    x=0;
    y=b;
    disp();
    p1=(b*b)-(a*a*b)+(a*a)/4;
    while(logFile << "ELLIPS 2" << std::endl && ((2.0*b*b*x)<=(2.0*a*a*y)))
    {
        x++;
        if(p1<=0)
            {
logFile << "ELLIPS 3" << std::endl;
p1=p1+(2.0*b*b*x)+(b*b);
}
        else
        {
logFile << "ELLIPS 4" << std::endl;

            y--;
            p1=p1+(2.0*b*b*x)+(b*b)-(2.0*a*a*y);
        }
logFile << "ELLIPS 5" << std::endl;

        disp();
        x=-x;
        disp();
        x=-x;
    }
logFile << "ELLIPS 6" << std::endl;

    x=a;
    y=0;
    disp();
    p2=(a*a)+2.0*(b*b*a)+(b*b)/4;
    while(logFile << "ELLIPS 7" << std::endl && ((2.0*b*b*x)>(2.0*a*a*y)))
    {
        y++;
        if(p2>0)
            {
logFile << "ELLIPS 8" << std::endl;
p2=p2+(a*a)-(2.0*a*a*y);
}
        else
        {
logFile << "ELLIPS 9" << std::endl;

            x--;
            p2=p2+(2.0*b*b*x)-(2.0*a*a*y)+(a*a);
        }
logFile << "ELLIPS 10" << std::endl;

        disp();
        y=-y;
        disp();
        y=-y;
    }
logFile << "ELLIPS 11" << std::endl;


}
void disp()
{
logFile << "disp 1" << std::endl;

    putpixel(xc+x,yc+y,5);
    putpixel(xc-x,yc+y,5);
    putpixel(xc+x,yc-y,5);
    putpixel(xc+x,yc-y,5);
}
