# include "graphics.h"
# include "conio.h"
# include "stdio.h"
# include "stdlib.h"
# include "dos.h"
#define ARROW_SIZE 7
#define BALLOON_SIZE 3

int flag_arrow=0,flag_balloon=1,count_arrow=6,count_balloon=10;
void *balloon,*bow,*arrow,*burst;
void *clear_balloon,*clear_burst;
void draw_balloon(int ,int );
void draw_burst ( int x, int y );
void draw_bow(int x,int y);
void draw_arrow(int x, int y);
void shoot(int *x, int *y);
int testkeys();
void fly(int *x, int *y);
void start();

void main()
{
    int gmode = DETECT, gdriver , area ;
    initgraph ( &gmode, &gdriver, "c:\tc\bgi\ " ) ;
                setbkcolor(1);
                start();
                int maxx = getmaxx() ;
                int maxy = getmaxy() ;
                int p=400,q=300,m=100,n=100,x=m,y=n,key,score=0,finish=0,level=1,l_flag=1;
                char score1[5],ch,cnt_ball[5],char_level[2];

                rectangle ( 0, 0, maxx, maxy - 10 ) ;

                draw_burst(200,300);
                area=imagesize(0,0,32,24);
                burst=malloc(area);
                getimage(200-16,300-12,200+16,300+12,burst);
                putimage(200-16,300-12,burst,XOR_PUT);

                draw_balloon(p,q);

                area=imagesize(p-4*BALLOON_SIZE,q-5*BALLOON_SIZE,p+4*BALLOON_SIZE,q+7*BALLOON_SIZE);
                balloon=malloc(area);

                getimage(p-4*BALLOON_SIZE,q-5*BALLOON_SIZE,p+4*BALLOON_SIZE,q+7*BALLOON_SIZE,balloon);
                putimage(p-4*BALLOON_SIZE, q-5*BALLOON_SIZE, balloon, COPY_PUT);

                draw_arrow(x ,y  );
                area = imagesize(x, y-ARROW_SIZE, x+(6*ARROW_SIZE), y+ARROW_SIZE);
                arrow=malloc(area);
                getimage(x, y-ARROW_SIZE, x+(6*ARROW_SIZE), y+ARROW_SIZE,arrow);
                putimage(x, y-ARROW_SIZE,arrow,XOR_PUT);

                draw_bow(x,y);
                area=imagesize(x+25,y-65,x+66,y+65);
                bow=malloc(area);
                getimage(x+25,y-65,x+66,y+65,bow);

                if ( balloon == NULL || burst == NULL || bow == NULL )
                {
                printf( "Insufficient memory... Press any key " ) ;
                getch() ;
                closegraph() ;
                restorecrtmode() ;
                exit( 0 ) ;
            }
// Downloaded from www.indiaexam.in
                while (!finish)
                {
                settextstyle(8,0,1);
                setusercharsize(4,4,3,3);
            outtextxy(getmaxx()/2-100,5,"LEVEL : ");
                itoa(level,char_level,10);
                setfillstyle(0,0);
                bar(getmaxx()/2+40,15,getmaxx()/2+70,45);
                outtextxy(getmaxx()/2+50,5,char_level);

                rectangle(5,360,250,460);

                if( flag_balloon && count_balloon>0 )
                fly( &p, &q );
                else
                {
                q = 400;
                flag_balloon = 1;
            }

                if( kbhit() )
                {
                key = testkeys();
                if(key==77)
                flag_arrow = 1;
            }

                if( key == 27 )
                break;
                if (key == 80 &&!flag_arrow)
                {
                x=125;
                putimage(x,y-65,bow,XOR_PUT);
                if(y<300)
                y+=25;
                putimage(x,y-65,bow,XOR_PUT);
                draw_bow(x-25,y);
                key=0;
            }
                if (key == 72 &&!flag_arrow)
                {
                x=125;
                putimage(x,y-65,bow,XOR_PUT);
                if(y>70)
                y-=25;
                putimage(x,y-65,bow,XOR_PUT);
                draw_bow(x-25,y);
                key=0;
            }
                if(count_arrow > 0 && count_balloon > 0)
                {
                if(score==100 && l_flag==1)
                {
                level=2;
                count_balloon=8;
                count_arrow=6;
                l_flag=2;
            }
                if(score==180 && l_flag==2)
                {
                level=3;
                count_balloon=6;
                count_arrow=6;
                l_flag=0;
            }
                if( key == 77 || flag_arrow)
                {
                shoot(&x,&y);
                draw_bow(m,y);
                if(x>(p-12) && x<(p+12) && y>(q-15) && y<(q+25))
                {
                putimage(p-16,q-12,burst,COPY_PUT);
                sound(1500);
                delay(800);
                nosound();
                putimage(p-16,q-12,burst,XOR_PUT);
                count_balloon--;
                settextstyle(10,0,1);
                setusercharsize(30,70,20,70);
            outtextxy(20,380,"BALLOONS LEFT:");
                setfillstyle(0,0);
                bar(200,370,230,400);
                itoa(count_balloon,cnt_ball,10);
                outtextxy(200,380,cnt_ball);
                flag_balloon=0;
                score+=20;
                itoa(score,score1,10);
                setfillstyle(0,0);
                bar(190,getmaxy()-50,230,getmaxy()-30);
                setcolor(RED);
            outtextxy(20,getmaxy()-50,"SCORE          : ");
                outtextxy(190,getmaxy()-50,score1);
            }

                key=0;
            }
            }
                else
                {
                clearviewport();
                setbkcolor(9);
                setcolor(10);
                settextstyle(4,0,7);
                setusercharsize(120,50,120,40);
                outtextxy(getmaxx()/2-220,getmaxy()/2-180,"GAME OVER");

                settextstyle(8,0,1);
                setusercharsize(50,60,40,50);
                if(count_arrow<=0)
                outtextxy(getmaxx()/2-100,getmaxy()/2-70,"NO MORE ARROWS");

                if(count_balloon<=0)
                outtextxy(getmaxx()/2-120,getmaxy()/2-70,"NO MORE BALLOONS");

            outtextxy(getmaxx()/2-120,getmaxy()/2-20,"YOUR SCORE IS : ");
                itoa(score,score1,10);
                outtextxy(getmaxx()/2+150,getmaxy()/2-20,score1);

                if(level==1)
                outtextxy(getmaxx()/2-220,getmaxy()/2+20,"YOU REQUIRE TO PRACTICE MORE");
                if(level==2)
                outtextxy(getmaxx()/2-70,getmaxy()/2+20,"WELL PLAYED");
                if(level==3)
                outtextxy(getmaxx()/2-220,getmaxy()/2+20,"YOU ARE AN EFFICIENT SHOOTER");

                outtextxy(getmaxx()/2-30,getmaxy()/2+50,"(Q)UIT");

                settextstyle(1,0,1);
                setusercharsize(30,65,30,60);
                while( getch() != 'q');
                finish=1;
                break;
            }
            }
                free(bow);
                free(arrow);
                free(balloon);
                closegraph();
            }
// Downloaded from www.indiaexam.in
                void draw_balloon(int x,int y)
                {
                setcolor(RED);
                setfillstyle(1,RED);
                fillellipse(x,y,3*BALLOON_SIZE,4*BALLOON_SIZE);
                line(x,y+4*BALLOON_SIZE,x,y+6*BALLOON_SIZE);
            }

                void draw_burst ( int x, int y )
                {
                setlinestyle(0,0,1);
                line ( x - 16, y - 12, x - 10, y - 2 ) ;
                line ( x - 10, y - 2, x - 16, y ) ;
                line ( x - 16, y, x - 10, y + 2 ) ;
                line ( x - 10, y + 2, x - 16, y + 12 ) ;

                line ( x - 16, y + 12, x - 6, y + 2 ) ;
                line ( x - 6, y + 2, x, y + 12 ) ;
                line ( x, y + 12, x + 6, y + 2 ) ;
                line ( x + 6, y + 2, x + 16, y + 12 ) ;

                line ( x - 16, y - 12, x - 6, y - 2 ) ;
                line ( x - 6, y - 2, x, y - 12 ) ;
                line ( x, y - 12, x + 6, y - 2 ) ;
                line ( x + 6, y - 2, x + 16, y - 12 ) ;

                line ( x + 16, y - 12, x + 10, y - 2 ) ;
                line ( x + 10, y - 2, x + 16, y ) ;
                line ( x + 16, y, x + 10, y + 2 ) ;
                line ( x + 10, y + 2, x + 16, y + 12 ) ;

            }

                void draw_bow(int x,int y)
                {
                setcolor(RED);
                setlinestyle(0,0,1);
                line(x+32,y-49,x+32,y+49);
                setlinestyle(0,0,3);
                arc(x,y,300,60,60);
                arc(x+34,y-56,100,220,6);
                arc(x+34,y+56,140,260,6);
            }

                void shoot(int *x, int *y)
                {
                char cnt_arrow[5];
                putimage(*x, *y-ARROW_SIZE, arrow, COPY_PUT);
                delay(3);
                putimage(*x, *y-ARROW_SIZE, arrow, XOR_PUT);
                *x+=ARROW_SIZE;

                if (*x>590)
                {
                *x=155;
                flag_arrow=0;
                count_arrow--;
                settextstyle(10,0,1);
                setusercharsize(30,70,20,70);
            outtextxy(20,400,"ARROWS LEFT :");
                setfillstyle(0,WHITE);
                bar(200,400,220,425);
                itoa(count_arrow,cnt_arrow,10);
                outtextxy(200,400,cnt_arrow);
            }

            }
                void draw_arrow(int x, int y)
                {
                setlinestyle(0,0,2);
                moveto(x, y);
                linerel(6*ARROW_SIZE, 0);
                linerel(-2*ARROW_SIZE, -1*ARROW_SIZE+1);
                linerel(0, 2*ARROW_SIZE-1);
                linerel(2*ARROW_SIZE, -1*ARROW_SIZE);
            }

                int testkeys()
                {
                union REGS ii, oo ;
                ii.h.ah = 0 ;
                int86 ( 22, &ii, &oo ) ;
                /* if ascii code is not 0 */
                if ( oo.h.al )
                return ( oo.h.al ) ;
                else
                return ( oo.h.ah ) ;
            }

                void fly(int *x, int *y)
                {
                int x1;
                putimage(*x-4*BALLOON_SIZE, *y-5*BALLOON_SIZE, balloon, COPY_PUT);
                delay(20);
                char cnt_ball[5];
                putimage(*x-4*BALLOON_SIZE, *y-5*BALLOON_SIZE, balloon, XOR_PUT);
                *y-=BALLOON_SIZE;

                if(*y<= 20)
                {
                *y=400;
                x1=450+rand()%150;
                *x=x1;
                count_balloon--;
                settextstyle(10,0,1);
                setusercharsize(30,70,20,70);
            outtextxy(20,380,"BALLOONS LEFT:");
                setfillstyle(0,0);
                bar(200,370,230,400);
                itoa(count_balloon,cnt_ball,10);
                outtextxy(200,380,cnt_ball);
            }
            }

                void start()
                {
                setbkcolor(0);
                settextstyle(7,0,0);
                outtextxy(10,400,"  PRESS ANY KEY TO CONTINUE....");
                settextstyle(1,0,0);
                setcolor(4);
                setusercharsize(25,15,20,4);
                outtextxy(85,120,"BALLOON SHOOTING");
                float octave[7] = { 130.81, 146.83, 164.81, 174.61, 196, 220, 246.94};
                while( !kbhit() )
                {
                sound( octave[ random(7) ]*4 );
                delay(300);
            }
                nosound();
                getch();
                clearviewport();
                rectangle(1,1,638,478);
                settextstyle(3,0,1);
                setusercharsize(50,30,50,30);
                outtextxy(150,10,"INSTRUCTIONS");
                setbkcolor(LIGHTBLUE);
                settextstyle(1,0,1);
                setusercharsize(40,70,20,20);
                outtextxy(10,70,"1. You can play three levels.");
                outtextxy(10,110,"2. You can move the bow UP and DOWN with the help of arrow keys.");
                outtextxy(10,150,"3. Press right arrow key to shoot the arrow.");
                outtextxy(10,190,"4. You score 20 points every time you shoot the balloon.");
                outtextxy(10,230,"5. First level has 6 arrows and 10 balloons.");
                outtextxy(10,270,"6. You require to score 100 points to enter the second level.");
                outtextxy(10,310,"7. Second level has 6 arrows and 8 balloons.");
                outtextxy(10,350,"8. You require to score 200 points to enter the third level.");
                outtextxy(10,390,"9. Third level has 6 arrows and 6 balloons.");
                settextstyle(7,0,1);
                outtextxy(150,430,"PRESS ANY KEY TO CONITINUE");

                getch();
                setusercharsize(1,1,1,1);
                settextstyle(0,0,0);
                setbkcolor(YELLOW);
                clearviewport();
            }
