#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#define DOTCOLOR 14
#define DIGCOLOR 5
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
    style=1;
    SIZE=1;
    HEIGHT=1;
    WIDTH=12;
    COLOR=15;
    bar_make();
}
Digital_Clock::Digital_Clock(int s,int c,int st)
{
    style=st;
    SIZE=s;
    COLOR=c;
    HEIGHT=1;
    WIDTH=6;
    bar_make();
}
void Digital_Clock::bar_make()
{
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
    int num,gap,qu,rem;
    gap=(SIZE*HEIGHT);
    num=n;
    if(num==62)
    {
        DrawDig(x,y,62);
    }
    if(num==63)
    {
        DrawDig(x,y,63);
    }
    if(num>=0&&num<10)
    {
        DrawDig(x,y,0);
        DrawDig(x+WIDTH*SIZE+HEIGHT*SIZE+gap,y,n);
    }
    if(num>=10&&num<61)
    {
        qu=num/10;
        rem=num%10;
        DrawDig(x,y,qu);
        DrawDig(x+WIDTH*SIZE+HEIGHT*SIZE+gap,y,rem);
    }
}
void Digital_Clock::DrawDig(int x,int y,int n)
{
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
        for(i=0; i<3; i++)
        {
            if(ph[0][i]==1)
            {
                putimage(HX[i],HY[i],HOR,XOR_PUT);
            }
        }
        for(i=0; i<4; i++)
        {
            if(pv[0][i]==1)
            {
                putimage(VX[i],VY[i],VER,XOR_PUT);
            }
        }
    }
    else if(n==63)
    {
        for(i=0; i<3; i++)
        {
            if(ph[1][i]==1)
            {
                putimage(HX[i],HY[i],HOR,XOR_PUT);
            }
        }
        for(i=0; i<4; i++)
        {
            if(pv[1][i]==1)
            {
                putimage(VX[i],VY[i],VER,XOR_PUT);
            }
        }
    }
    else
    {
        for(i=0; i<3; i++)
        {
            if(H[n][i]==1)
                putimage(HX[i],HY[i],HOR,XOR_PUT);
        }
        for(i=0; i<4; i++)
        {
            if(V[n][i]==1)
                putimage(VX[i],VY[i],VER,XOR_PUT);
        }
    }
}
Digital_Clock::~Digital_Clock()
{
    delete HOR;
    delete VER;
}
void drawdot();
int color=DOTCOLOR;
void main()
{
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
        p.PutDig(500,y,62);
    else
        A.PutDig(500,y,63);
    while(!kbhit())
    {
        gettime(&t);
        if(th!=t.ti_hour)
        {
            th=t.ti_hour;
            h.PutDig(20,y,t.ti_hour);
        }
        if(tm!=t.ti_min)
        {
            tm=t.ti_min;
            m.PutDig(220,y,t.ti_min);
        }
        if(ts!=t.ti_sec)
        {
            ts=t.ti_sec;
            s.PutDig(380,y,t.ti_sec);
            drawdot();
        }
    }
    getch();
}

void drawdot()
{
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
    while((2.0*b*b*x)<=(2.0*a*a*y))
    {
        x++;
        if(p1<=0)
            p1=p1+(2.0*b*b*x)+(b*b);
        else
        {
            y--;
            p1=p1+(2.0*b*b*x)+(b*b)-(2.0*a*a*y);
        }
        disp();
        x=-x;
        disp();
        x=-x;
    }
    x=a;
    y=0;
    disp();
    p2=(a*a)+2.0*(b*b*a)+(b*b)/4;
    while((2.0*b*b*x)>(2.0*a*a*y))
    {
        y++;
        if(p2>0)
            p2=p2+(a*a)-(2.0*a*a*y);
        else
        {
            x--;
            p2=p2+(2.0*b*b*x)-(2.0*a*a*y)+(a*a);
        }
        disp();
        y=-y;
        disp();
        y=-y;
    }

}
void disp()
{
    putpixel(xc+x,yc+y,5);
    putpixel(xc-x,yc+y,5);
    putpixel(xc+x,yc-y,5);
    putpixel(xc+x,yc-y,5);
}
