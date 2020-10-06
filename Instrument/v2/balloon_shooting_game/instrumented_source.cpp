# include "graphics.h"
# include "conio.h"
# include "stdio.h"
# include "stdlib.h"
# include "dos.h"
#define ARROW_SIZE 7
#define BALLOON_SIZE 3


//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

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
logFile << "main 1" << std::endl;

    int gmode = DETECT, gdriver , area ;
    initgraph ( &gmode, &gdriver,                 setbkcolor(1);
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
logFile << "main 2" << std::endl;

                printf( "Insufficient memory... Press any key " ) ;
                getch() ;
                closegraph() ;
                restorecrtmode() ;
                exit( 0 ) ;
            }
logFile << "main 3" << std::endl;

// Downloaded from www.indiaexam.in
                while (logFile << "main 4" << std::endl && (!finish))
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
                {
logFile << "main 5" << std::endl;
fly( &p, &q );
}
                else
                {
logFile << "main 6" << std::endl;

                q = 400;
                flag_balloon = 1;
            }
logFile << "main 7" << std::endl;


                if( kbhit() )
                {
logFile << "main 8" << std::endl;

                key = testkeys();
                if(key==77)
                {
logFile << "main 9" << std::endl;
flag_arrow = 1;
}
logFile << "main 10" << std::endl;

            }
logFile << "main 11" << std::endl;


                if( key == 27 )
                {
logFile << "main 12" << std::endl;
break;
}
logFile << "main 13" << std::endl;

                if (key == 80 &&!flag_arrow)
                {
logFile << "main 14" << std::endl;

                x=125;
                putimage(x,y-65,bow,XOR_PUT);
                if(y<300)
                {
logFile << "main 15" << std::endl;
y+=25;
}
logFile << "main 16" << std::endl;

                putimage(x,y-65,bow,XOR_PUT);
                draw_bow(x-25,y);
                key=0;
            }
logFile << "main 17" << std::endl;

                if (key == 72 &&!flag_arrow)
                {
logFile << "main 18" << std::endl;

                x=125;
                putimage(x,y-65,bow,XOR_PUT);
                if(y>70)
                {
logFile << "main 19" << std::endl;
y-=25;
}
logFile << "main 20" << std::endl;

                putimage(x,y-65,bow,XOR_PUT);
                draw_bow(x-25,y);
                key=0;
            }
logFile << "main 21" << std::endl;

                if(count_arrow > 0 && count_balloon > 0)
                {
logFile << "main 22" << std::endl;

                if(score==100 && l_flag==1)
                {
logFile << "main 23" << std::endl;

                level=2;
                count_balloon=8;
                count_arrow=6;
                l_flag=2;
            }
logFile << "main 24" << std::endl;

                if(score==180 && l_flag==2)
                {
logFile << "main 25" << std::endl;

                level=3;
                count_balloon=6;
                count_arrow=6;
                l_flag=0;
            }
logFile << "main 26" << std::endl;

                if( key == 77 || flag_arrow)
                {
logFile << "main 27" << std::endl;

                shoot(&x,&y);
                draw_bow(m,y);
                if(x>(p-12) && x<(p+12) && y>(q-15) && y<(q+25))
                {
logFile << "main 28" << std::endl;

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
logFile << "main 29" << std::endl;


                key=0;
            }
logFile << "main 30" << std::endl;

            }
                else
                {
logFile << "main 31" << std::endl;

                clearviewport();
                setbkcolor(9);
                setcolor(10);
                settextstyle(4,0,7);
                setusercharsize(120,50,120,40);
                outtextxy(getmaxx()/2-220,getmaxy()/2-180,"GAME OVER");

                settextstyle(8,0,1);
                setusercharsize(50,60,40,50);
                if(count_arrow<=0)
                {
logFile << "main 32" << std::endl;
outtextxy(getmaxx()/2-100,getmaxy()/2-70,"NO MORE ARROWS");
}
logFile << "main 33" << std::endl;


                if(count_balloon<=0)
                {
logFile << "main 34" << std::endl;
outtextxy(getmaxx()/2-120,getmaxy()/2-70,"NO MORE BALLOONS");
}
logFile << "main 35" << std::endl;


            outtextxy(getmaxx()/2-120,getmaxy()/2-20,"YOUR SCORE IS : ");
                itoa(score,score1,10);
                outtextxy(getmaxx()/2+150,getmaxy()/2-20,score1);

                if(level==1)
                {
logFile << "main 36" << std::endl;
outtextxy(getmaxx()/2-220,getmaxy()/2+20,"YOU REQUIRE TO PRACTICE MORE");
}
logFile << "main 37" << std::endl;

                if(level==2)
                {
logFile << "main 38" << std::endl;
outtextxy(getmaxx()/2-70,getmaxy()/2+20,"WELL PLAYED");
}
logFile << "main 39" << std::endl;

                if(level==3)
                {
logFile << "main 40" << std::endl;
outtextxy(getmaxx()/2-220,getmaxy()/2+20,"YOU ARE AN EFFICIENT SHOOTER");
}
logFile << "main 41" << std::endl;


                outtextxy(getmaxx()/2-30,getmaxy()/2+50,"(Q)UIT");

                settextstyle(1,0,1);
                setusercharsize(30,65,30,60);
                while( logFile << "main 42" << std::endl && (getch() != 'q')){
;
}
logFile << "main 43" << std::endl;

                finish=1;
                break;
            }
logFile << "main 44" << std::endl;

            }
logFile << "main 45" << std::endl;

                free(bow);
                free(arrow);
                free(balloon);
                closegraph();
            }
// Downloaded from www.indiaexam.in
                void draw_balloon(int x,int y)
                {
logFile << "drawballoonintxinty 1" << std::endl;

                setcolor(RED);
                setfillstyle(1,RED);
                fillellipse(x,y,3*BALLOON_SIZE,4*BALLOON_SIZE);
                line(x,y+4*BALLOON_SIZE,x,y+6*BALLOON_SIZE);
            }

                void draw_burst ( int x, int y )
                {
logFile << "drawburstintxinty 1" << std::endl;

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
logFile << "drawbowintxinty 1" << std::endl;

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
logFile << "shootintxinty 1" << std::endl;

                char cnt_arrow[5];
                putimage(*x, *y-ARROW_SIZE, arrow, COPY_PUT);
                delay(3);
                putimage(*x, *y-ARROW_SIZE, arrow, XOR_PUT);
                *x+=ARROW_SIZE;

                if (*x>590)
                {
logFile << "shootintxinty 2" << std::endl;

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
logFile << "shootintxinty 3" << std::endl;


            }
                void draw_arrow(int x, int y)
                {
logFile << "drawarrowintxinty 1" << std::endl;

                setlinestyle(0,0,2);
                moveto(x, y);
                linerel(6*ARROW_SIZE, 0);
                linerel(-2*ARROW_SIZE, -1*ARROW_SIZE+1);
                linerel(0, 2*ARROW_SIZE-1);
                linerel(2*ARROW_SIZE, -1*ARROW_SIZE);
            }

                int testkeys()
                {
logFile << "testkeys 1" << std::endl;

                union REGS ii, oo ;
                ii.h.ah = 0 ;
                int86 ( 22, &ii, &oo ) ;
                /* if ascii code is not 0 */
                if ( oo.h.al )
                {
logFile << "testkeys 2" << std::endl;
return ( oo.h.al ) ;
}
                else
                {
logFile << "testkeys 3" << std::endl;
return ( oo.h.ah ) ;
}
logFile << "testkeys 4" << std::endl;

            }

                void fly(int *x, int *y)
                {
logFile << "flyintxinty 1" << std::endl;

                int x1;
                putimage(*x-4*BALLOON_SIZE, *y-5*BALLOON_SIZE, balloon, COPY_PUT);
                delay(20);
                char cnt_ball[5];
                putimage(*x-4*BALLOON_SIZE, *y-5*BALLOON_SIZE, balloon, XOR_PUT);
                *y-=BALLOON_SIZE;

                if(*y<= 20)
                {
logFile << "flyintxinty 2" << std::endl;

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
logFile << "flyintxinty 3" << std::endl;

            }

                void start()
                {
logFile << "start 1" << std::endl;

                setbkcolor(0);
                settextstyle(7,0,0);
                outtextxy(10,400,"  PRESS ANY KEY TO CONTINUE....");
                settextstyle(1,0,0);
                setcolor(4);
                setusercharsize(25,15,20,4);
                outtextxy(85,120,"BALLOON SHOOTING");
                float octave[7] = { 130.81, 146.83, 164.81, 174.61, 196, 220, 246.94};
                while( logFile << "start 2" << std::endl && (!kbhit()) )
                {
                sound( octave[ random(7) ]*4 );
                delay(300);
            }
logFile << "start 3" << std::endl;

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
