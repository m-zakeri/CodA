 
#include"graphics.h"
#include<fstream.h>
#include<iomanip.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
void proj_name(void);
void created(void);
  class consumer
   {
    public:
     long unsigned int tel_no;
     long unsigned int con_no;
     char name[60];
     char add[300];
     char city[40];
     long unsigned int op_rdg;
     long unsigned int cl_rdg;
     long unsigned int met_calls;
     long unsigned int free_calls;
     long unsigned int charge_calls;
     float met_charge;
     float rent;
     float debits;
     float tax;
     float credits;
     float gross_amt;
     float surcharge;
     long unsigned int net_amt_bef;
     long unsigned int net_amt_aft;
    public:
      void get_data(void);
      void show_data(void);
   };
 
void consumer::get_data(void)
{
  setfillstyle(1,BLACK);
  bar(0,0,680,480);
  consumer g1;  int a; char ch;
  setlinestyle(0,0,3);
  setcolor(BROWN);
  settextstyle(1,0,5);
  outtextxy(90,20,"ENTER THE RECORD:-");
  setfillstyle(1,BLACK);
  bar(50,100,550,400);
  rectangle(50,100,550,400);
  gotoxy(10,10);
  cout<<"TELEPHONE NO.    :";
  cout<<tel_no;
  cin.get(ch);
  gotoxy(10,12);
  cout<<"NAME             :";
  cin.getline(name,60);
  gotoxy(10,14);
  cout<<"ADDRESS          :";
  cin.getline(add,300);
  gotoxy(10,16);
  cout<<"CITY             :";
  cin.getline(city,40);
  gotoxy(10,18);
  cout<<"OPENING READING  :";
  cin>>op_rdg;
  gotoxy(10,20);
  cout<<"CLOSING READING  :";
  cin>>cl_rdg;
  met_calls=cl_rdg-op_rdg;
  free_calls=150;
  rent=360;
  if(met_calls<free_calls )
    {
     charge_calls=0;
     met_charge=0;
    }
  else
   {
    charge_calls=met_calls-free_calls;
    met_charge=charge_calls*(.80);
   }
  gotoxy(10,22);
  cout<<"DEBITS           :";
  cin>>debits;
  tax=(rent+met_charge+debits)/20;
  gross_amt=(met_charge+rent+tax+debits);
  gotoxy(10,24);
  cout<<"CREDITS          :";
  cin>>credits;
  if(credits>gross_amt)
  net_amt_bef=0;
  else
  net_amt_bef=gross_amt-credits;
  if(credits>=gross_amt)
  surcharge=0;
  else
  surcharge=20;
  net_amt_aft=net_amt_bef+surcharge;
}
 
void consumer::show_data(void)
{
  bar(0,0,660,480);
  setcolor(RED);
  settextstyle(8,0,3);
  outtextxy(55,10,"BHARAT SANCHAR NIGAM LIMITED");
  setlinestyle(1,0,3);
  line(51,40,486,40);
  gotoxy(10,5);
  settextstyle(3,0,1);
  setcolor(BROWN);
  outtextxy(15,55,"TELEPHONE NO.");
  outtextxy(330,55,"CONSUMER NO.");
  outtextxy(15,170,"OPENING READING  ");
  outtextxy(15,205,"CLOSING READING  ");
  outtextxy(15,235,"METERED CALLS    ");
  outtextxy(15,268,"FREE CALLS       ");
  outtextxy(15,300,"CHARGABLE CALLS  ");
  setcolor(BROWN);
  outtextxy(330,170,"METERED CALLS   ");
  outtextxy(330,205,"DEBITS          ");
  outtextxy(330,235,"TAXES           ");
  outtextxy(330,268,"GROSS AMOUNT    ");
  outtextxy(330,300,"CREDITS         ");
  outtextxy(330,140,"RENTAL                             ");
  setcolor(MAGENTA);
  outtextxy(15,327,"AMOUNT PAYABLE IF PAID ON OR BEFORE ");
  setcolor(BROWN);
  outtextxy(15,350,"SURCHARGE                           ");
  setcolor(MAGENTA);
  outtextxy(15,377,"AMOUNT PAYABLE IF PAID ON OR AFTER  ");
  setcolor(RED);
  setlinestyle(0,0,3);
  bar(70,90,320,160);
  rectangle(70,90,320,160);
  gotoxy(20,5);
  cout<<tel_no;
  gotoxy(60,5);
  cout<<con_no;
  gotoxy(12,7);
  cout<<name<<"\n";
  gotoxy(12,8);
  cout<<add<<"\n";
  gotoxy(12,9);
  cout<<city;
  gotoxy(54,10);
  cout<<setw(20)<<rent;
  gotoxy(25,12);
  cout<<setw(15);
  cout<<op_rdg;
  gotoxy(25,14);
  cout<<setw(15)<<cl_rdg;
  gotoxy(25,16);
  cout<<setw(15)<<met_calls;
  gotoxy(25,18);
  cout<<setw(15)<<free_calls;
  gotoxy(25,20);
  cout<<setw(15)<<charge_calls;
  gotoxy(59,12);
  cout<<setw(15)<<met_charge;
  gotoxy(59,14);
  cout<<setw(15)<<debits;
  gotoxy(59,16);
  cout<<setw(15)<<tax;
  gotoxy(59,18);
  cout<<setw(15)<<gross_amt;
  gotoxy(59,20);
  cout<<setw(15)<<credits;
  gotoxy(50,22);
  cout<<setw(5)<<net_amt_bef;
  gotoxy(25,23);
  cout<<setw(15)<<surcharge;
  gotoxy(50,25);
  cout<<setw(5)<<net_amt_aft;
}
 
void main()
{
    char ans; int con_no;
    int gd=DETECT,gm;  int i,j;
    int midx,midy;
    initgraph(&gd,&gm,"c:\\tc\\bgi");
    midx=getmaxx()/2; midy=getmaxy()/2;
    /*char*pass="HELLO";
    char*ppass;
    gotoxy(25,8);
    ppass=getpass("ENTER THE PASSWORD::");
    if(strcmpi(pass,ppass)!=0)
     {
      setcolor(GREEN);
      settextstyle(1,0,4);
      outtextxy(140,220,"INVALID PASSWORD");
      sleep(3);
      exit(1);
     }*/
    setlinestyle(1,0,2);
    setfillstyle(1,LIGHTCYAN);
    rectangle(2,1,660,660);
    bar(2,1,660,660);
    setcolor(RED);
    for(i=90;i<=385;i+=17)
      {
       outtextxy(50,i,"*");
       outtextxy(560,i,"*");
      }
    for(j=50;j<=560;j+=17)
      {
       outtextxy(j,90,"*");
       outtextxy(j,385,"*");
      }
    setfillstyle(1,LIGHTGRAY);
    ellipse(310,240,0,360,240,120);
    fillellipse(310,240,240,120);
    setfillstyle(1,LIGHTCYAN);
    ellipse(312,241,0,360,200,100);
    fillellipse(312,241,200,100);
    setfillstyle(1,LIGHTGRAY);
    ellipse(314,242,0,360,160,80);
    fillellipse(314,242,160,80);
    settextstyle(0,0,3);
    settextstyle(0,HORIZ_DIR,4);
    setcolor(RED);
    outtextxy(200,190,"WELCOME");
    settextstyle(1,0,4);
    for(i=220;i<221;i++)
     {
       outtextxy(280,i,"TO");
     }
    settextstyle(0,0,3);
    for(i=270;i<271;i++)
     {
       outtextxy(190,270,"OUR PROJECT");
     }
    sleep(1);
    sleep(1);
    proj_name();
    sleep(1);
    created();
    fstream fin;  consumer g1;
    i:
fin.open("m.dat",ios::in|ios::out|ios::app|ios::ate|ios::binary);
   fin.seekg(0,ios::end);
   int a;  char answer;
   setfillstyle(1,LIGHTMAGENTA);
   rectangle(0,0,600,480);
   bar(0,0,700,480);
   setcolor(BLUE);
   settextstyle(1,0,5);
   setlinestyle(1,0,3);
   outtextxy(10,20,"ENTER YOUR CHOICE:-");
   settextstyle(1,0,3);
   outtextxy(100,120,"PRESS 1:TO ADD NEW RECORD");
   outtextxy(100,150,"PRESS 2:TO SEE THE RECORDS");
   outtextxy(100,180,"PRESS 3:FOR ENQUIRY");
   outtextxy(100,210,"PRESS 4:FOR MODIFICATION");
   outtextxy(100,240,"PRESS 5:FOR EXIT");
   setfillstyle(1,RED);
   bar(580,370,640,420);
   gotoxy(77,25);
   cin>>a;
   setfillstyle(1,0);
 
		//TO ADD NEW RECORD
if(a==1)
 {
  do
   {
    setfillstyle(1,LIGHTMAGENTA);
    bar(0,0,679,679);
    settextstyle(1,0,4);
    setcolor(BLUE);
    outtextxy(90,10,"ENTER THE RECORD:-");
    gotoxy(40,9);
    long unsigned int tel_no;
    outtextxy(50,110,"TELEPHONE_NO :");
    cin>>tel_no;
    fin.seekg(0);
     do
      {
       fin.read((char*)&g1,sizeof(g1));
	if(fin.eof())
	break;
	if(g1.tel_no==tel_no)
	 {
	  bar(0,0,679,679);
	  settextstyle(1,0,3);
	  setfillstyle(1,LIGHTCYAN);
	  bar(20,200,610,250);
	  outtextxy(20,220,"PERSON WITH THIS TELEPHONE_NO ALREADY EXISTS");
	  delay(2000);
	  goto u;
	  }
	}while(!fin.eof());
     fin.close();
     fin.open("m.dat",ios::app|ios::out|ios::in|ios::ate|ios::binary);
     fin.seekg(0,ios::end) ;
     long unsigned int r=fin.tellg();
     long unsigned int t=(r/sizeof(g1))+1;
     con_no=t;
     g1.tel_no=tel_no;
     g1.con_no=con_no;
     g1.get_data();
     fin.write((char*)&g1,sizeof(g1));
     setcolor(RED);
     settextstyle(8,0,4);
     outtextxy(12,420,"ENTER ANY OTHER RECORD(Y/N)");
     setfillstyle(1,4);
     bar(250,450,270,470);
     gotoxy(37,35);
     answer=getche();
    }
    while ((answer=='Y')||(answer=='y'));
    goto u;
}
 
		  //TO SEE THE RECORDS
else if(a==2)
 {
  fin.seekg(0);
  fin.read((char*)&g1,sizeof(g1)) ;
  do
   {
    clrscr();
    g1.show_data();
    fin.read((char*)&g1,sizeof(g1));
    getch();
   }
   while(!fin.eof());
   fin.close();
   goto i;
  }
 
		  //FOR ENQUIRY
else if (a==3)
 {
  long unsigned int tel_no1;
  bar(0,0,679,679);
  setcolor(GREEN);
  outtextxy(70,150,"ENTER THE TELEPHONE_NO OF PERSON :");
  gotoxy(35,15);
  cin>>tel_no1;
  bar(0,0,679,679);
  fin.seekg(0);
  do
   {
    fin.read((char*)&g1,sizeof(g1));
    if(fin.eof())
    goto y;
    else if(g1.tel_no==tel_no1)
    break;
   }
    while(fin);
    g1.show_data();
    getch();
    goto u;
 }
 
		       //FOR MODIFICATION
else if(a==4)
 {
  long unsigned int tel_no2;
  long unsigned int con_no;
  char name[60];
  char add[300];
  char city[40];
  long unsigned int op_rdg;
  long unsigned int cl_rdg;
  long unsigned int met_calls;
  long unsigned int free_calls;
  long unsigned int charge_calls;
  float met_charge;
  float rent;
  float debits;
  float tax;
  float credits;
  float gross_amt;
  float surcharge;
  long unsigned int net_amt_bef;
  long unsigned int net_amt_aft;
  bar(0,0,679,679);
  setcolor(MAGENTA);
  outtextxy(100,150,"ENTER THE TELEPHONE_NO OF PERSON ");
  outtextxy(100,180,"        TO BE MODIFIED           ");
  gotoxy(35,17);
  cin>>tel_no2;
  setfillstyle(1,0);
  fin.seekg(0);
  do
   {
   fin.read((char*)&g1,sizeof(g1));
   if(fin.eof())
    {
    setfillstyle(1,LIGHTMAGENTA);
    bar(0,0,679,679);
    setfillstyle(1,LIGHTCYAN);
    bar(40,200,565,250);
    setcolor(BLUE);
    settextstyle(1,0,3);
    outtextxy(70,220,"DESIRED TELEPHONE_NO DOES NOT EXISTS");
    delay(2000);
    setfillstyle(1,0);
    goto u;
    }
   if(g1.tel_no==tel_no2)
    {
     char ch;
     long unsigned int b=fin.tellg();
     long unsigned int s=sizeof(g1);
     fin.close();
     fin.open("m.dat",ios::out|ios::ate|ios::binary);
     fin.seekp(b-s);
     setfillstyle(1,BLACK);
     bar(0,0,680,480);
     setlinestyle(0,0,3);
     setcolor(BROWN);
     settextstyle(1,0,5);
     outtextxy(90,20,"ENTER THE RECORD:-");
     setfillstyle(1,BLACK);
     bar(50,100,550,400);
     rectangle(50,100,550,400);
     gotoxy(10,10);
     cout<<"TELEPHONE NO.    :";
     cout<<g1.tel_no;
     cin.get(ch);
     gotoxy(10,12);
     cout<<"NAME             :";
     cin.getline(name,60);
     gotoxy(10,14);
     cout<<"ADDRESS          :";
     cin.getline(add,300);
     gotoxy(10,16);
     cout<<"CITY             :";
     cin.getline(city,20);
     gotoxy(10,18);
     cout<<"OPENING READING  :";
     cin>>op_rdg;
     gotoxy(10,20);
     cout<<"CLOSING READING  :";
     cin>>cl_rdg;
     met_calls=cl_rdg-op_rdg;
     free_calls=150;
     rent=360;
     if(met_calls<free_calls )
      {
       charge_calls=0;
       met_charge=0;
      }
     else
      {
       charge_calls=met_calls-free_calls;
       met_charge=charge_calls*(.80);
      }
    gotoxy(10,22);
    cout<<"DEBITS           :";
    cin>>debits;
    tax=(rent+met_charge+debits)/20;
    gross_amt=(met_charge+rent+tax+debits);
    gotoxy(10,24);
    cout<<"CREDITS          :";
    cin>>credits;
    if(credits>gross_amt)
    net_amt_bef=0;
    else
    net_amt_bef=gross_amt-credits;
    if(credits>=gross_amt)
    surcharge=0;
    else
    surcharge=20;
    net_amt_aft=net_amt_bef+surcharge;
    g1.con_no=g1.con_no;
    strcpy(g1.name,name);
    strcpy(g1.add,add);
    strcpy(g1.city,city);
    g1.op_rdg=op_rdg;
    g1.cl_rdg=cl_rdg;
    g1.met_calls=met_calls;
    g1.free_calls=free_calls;
    g1.charge_calls=charge_calls;
    g1.met_charge=met_charge;
    g1.rent=rent;
    g1.debits=debits;
    g1.tax=tax;
    g1.credits=credits;
    g1.gross_amt=gross_amt;
    g1.surcharge=surcharge;
    g1.net_amt_bef=net_amt_bef;
    g1.net_amt_aft=net_amt_aft;
    fin.write((char*)&g1,sizeof(g1));
    goto kk;
   }
  }while(fin);
 
kk:setfillstyle(1,LIGHTMAGENTA);
bar(0,0,679,679);
setfillstyle(1,LIGHTCYAN);
bar(35,200,550,250);
setcolor(BLUE);
settextstyle(1,0,3);
outtextxy(80,220,"RECORD OF THIS PERSON IS MODIFIED");
delay(4000);
setfillstyle(1,0);
goto u;
}
 
	       //FOR EXIT
else
 {
  exit(0);
 }
 
u:fin.close();
bar(0,0,680,480);
goto i;
 
y:setfillstyle(1,LIGHTMAGENTA);
bar(0,0,679,679);
settextstyle(TRIPLEX_FONT,0,3);
setfillstyle(1,LIGHTCYAN);
bar(150,200,490,245);
setcolor(BLUE);
outtextxy(210,220,"RECORD NOT FOUND");
setfillstyle(1,0);
fin.close();
delay(2000);
goto u;
}
 
void proj_name(void)
 {
  fflush(stdin);
  int midx,midy;
  midx=getmaxx()/2;
  midy=getmaxy()/2;
  int i,j;
  setcolor(RED);
  setlinestyle(1,0,3);
  setfillstyle(1,CYAN);
  bar(2,1,660,660);
  rectangle(2,1,660,660);
  setcolor(RED);
  setfillstyle(1,WHITE);
  bar(25,75,575,425);
  rectangle(25,75,575,425);
  setfillstyle(1,CYAN);
  bar(50,100,550,400);
  rectangle(50,100,550,400);
  setcolor(RED);
  setfillstyle(1,WHITE);
  bar(75,125,525,375);
  rectangle(75,125,525,375);
  setcolor(RED);
  setfillstyle(1,CYAN);
  bar(100,150,500,350);
  rectangle(100,150,500,350);
  setcolor(RED);
  settextstyle(0,0,1);
  settextstyle(1,0,6);
  settextjustify(CENTER_TEXT,CENTER_TEXT);
  for(i=170;i<=172;i++)
  {
   sleep(1);
   outtextxy(291,i,    "TELEPHONE");
   outtextxy(301,i+70, " BILLING ");
   outtextxy(331,i+140,"SYSTEM  ");
   }
 }
 
void created(void)
 {
  fflush(stdin);
  setfillstyle(1,LIGHTCYAN);
  rectangle(2,1,660,660);
  bar(2,1,660,660);
  setcolor(RED);
  setlinestyle(1,0,3);
  settextstyle(1,0,8);
  settextjustify(LEFT_TEXT,TOP_TEXT);
  line(10,110,380,110);
  outtextxy(10,20,"C");
  settextstyle(4,0,8);
  outtextxy(47,20,"reated By:-");
  settextstyle(1,0,6);
  settextjustify(LEFT_TEXT,CENTER_TEXT);
 
  outtextxy(275,250,"MOHIT & ROHIT");
 
  sleep(1);
  sleep(1);
  clrscr();
 }