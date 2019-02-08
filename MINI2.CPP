#include<stdio.h>
#include<iostream.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>

int xmax,ymax,xdum=2,ydum=2,player=1,vert,x,o;

int xex[200],yex[200],who[200],ind;

struct pct
{
	int p1;
	int con1;
	int con2;
	int con1_p1;
	int con2_p1;
}p[15][15];

void putlinev(int i,int j,int k);
void putline(int i,int j,int k);
void putdot(int i,int j,int k);
void drawX(int i,int j,int k);
void draw0(int i,int j,int k);
void reposition();
void graphinit();
void drawlines();
void drawdots();
int choosecol();
void status();
void check1();
void check();
void putX0();
void intro();
void move();
void dim();
void end();


void main()
{
	dim();
	graphinit();
	setbkcolor(15);
	drawdots();
	move();
	closegraph();
}

void graphinit()
{
	int p1=DETECT,p2;
	initgraph(&p1,&p2,"..\\BGI");
}
void dim()
{
	int i,j;
	start:
	clrscr();
	cout<<"Width (2-13)";
	cin>>i;
	if(i<2||i>13)
		goto start;
	cout<<"Height (2-13)";
	cin>>j;
	if(j<2||j>13)
		goto start;
	xmax=i;
	ymax=j;
}
void drawdots()
{
	cleardevice();
	for(int i=1;i<=xmax;i++)
		for(int j=1;j<=ymax;j++)
			putdot(i,j,1);
}

void putdot(int i,int j,int k)
{
	setcolor(k);
	line(i*30-1,j*30-1,i*30+1,j*30-1);
	line(i*30-1,j*30,i*30+1,j*30);
	line(i*30-1,j*30+1,i*30+1,j*30+1);
}
inline void putline(int i,int j,int k)
{
	setcolor(k);
	line(i*30+2,j*30-1,i*30+28,j*30-1);
	line(i*30+2,j*30,i*30+28,j*30);
	line(i*30+2,j*30+1,i*30+28,j*30+1);
}

inline void putlinev(int i,int j,int k)
{
	setcolor(k);
	line(i*30+1,j*30+2,i*30-1,j*30+28);
	line(i*30,j*30+2,i*30,j*30+28);
	line(i*30+1,j*30+2,i*30+1,j*30+28);
}

void drawX(int i,int j,int k)
{
	setcolor(k);
	line(i*30+6,j*30-6,i*30+24,j*30-24);
	line(i*30+6,j*30-24,i*30+24,j*30-6);  
}

void draw0(int i,int j,int k)
{
	setcolor(k);
	circle(i*30+15,j*30-15,10);
}
void putX0()
{
	for(int l=0;l<=ind;l++)
		if(who[l]==1)
			drawX(xex[l],yex[l],2);
		else
			draw0(xex[l],yex[l],12);
}

void drawlines()
{
	for(int i=1;i<=xmax;i++)
		for(int j=1;j<=ymax;j++)
		{
			if(p[i][j].con2)
				if(p[i][j].con2_p1==1)
					putline(i,j,12);
				else
					putline(i,j,2);
			if(p[i][j].con1)
				if(p[i][j].con1_p1==1)
					putlinev(i,j,12);
				else
					putlinev(i,j,2);
		}
}

inline void reposition()
{
	if(xdum>=xmax&&!vert)
		xdum--;
	if(ydum>=ymax&&vert)
		ydum--;
}

inline void status()
{
	if(player==1)
	{
		setcolor(2);
		outtextxy(500,100,"Player 1 in move");
	}
	else
	{
		setcolor(12);
		outtextxy(500,100,"Player 2 in move");
	}
}
void end()
{
	if(ind==((xmax-1)*(ymax-1)))
	{
		if(x>o)
		{
			cout<<"player1 wins with "<<x<<"-"<<o;
			getch();
			exit(0);
		}
	if(x==o)
	{ 
		cout<<"tie("<<x<<"-"<<o<<")";
		getch();
		exit(0);
		
	}
	if(x<o)
	{
		cout<<"Player2 wins with"<<o<<"-"<<x;
		getch();
		exit(0);
	}
	}
}
inline void drawall()
{
	drawdots();
	drawlines();
	putX0();
	status();
}
void check()
{
	for(int i=1;i<=xmax;i++)
		for(int j=1;j<=ymax;j++)
		{
			int q=0;
			for(int l=0;l<=ind;l++)
				if((xex[l]==i)&&(yex[l]==j))
					q=1;
				if(!q)
					if(p[i][j].con2&&p[i][j-1].con1&&p[i][j-1].con2&&p[i+1][j-1].con1)
						if(player==1)
						{
							o++;
							player=2;
							draw0(i,j,12);
							xex[ind]=i;
							yex[ind]=j;
							who[ind]=2;
							ind++;
							return;
						}
						else
						{
							x++;
							drawX(i,j,2);
							xex[ind]=i;
							yex[ind]=j;
							who[ind]=1;
							ind++;
							return;
						}
		}
}
void check1()
{
	for(int i=1;i<=xmax;i++)
		for(int j=1;j<=ymax;j++)
		{
			int q=0;
			for(int l=0;l<ind;l++)
				if((xex[l]==i)&&(yex[l]==j))
					q=1;
				if(!q)
				if(p[i][j].con2&&p[i][j-1].con1&&p[i][j-1].con2&&p[i+1][j-1].con1)//check
				if(player==1)
				{
					x++;
					drawX(i,j,2);
					xex[ind]=i;
					yex[ind]=j;
					who[ind]=1;
					ind++;
				    return;
				}  
				else{
					o++;
					draw0(i,j,12);
					xex[ind]=i;
					yex[ind]=j;
					who[ind]=2;
					ind++;
					return;
				}
		}
}
void move()
{
	char a;
	while(a!='e')
	{
		begin:
		a=getch();
		if(!vert)
		{
			if(a=='d'&&xdum+1<=xmax)//Check
			{
				drawall();
				xdum++;
				putline(xdum,ydum,1);
			}
			if(a=='a'&&xdum-1>=1)
			{
				drawall();
				xdum--;
				putline(xdum,ydum,1);
			}
			if(a=='w'&&ydum-1>=1)
			{
				drawall();
				ydum--;
				putline(xdum,ydum,1);
			}
			if(a=='s'&&ydum+1<=ymax)
			{
				drawall();
				ydum++;
				putline(xdum,ydum,1);
			}
			if(a=='q'&&!p[xdum][ydum].con2)
			{
				p[xdum][ydum].con2=1;
				if(player==1)
					player=2;
				else
					player=1;
				p[xdum][ydum].con2_p1=player;
				check();
				check1();
				drawall();
				end();
			}
			if(a=='r')
			{
				if(vert)
					vert=0;
				else
					vert=1;
				reposition();
				drawlines();
				putlinev(xdum,ydum,1);
				goto begin;
			}
		}
		if(vert)
		{
			if(a=='d'&&xdum<=xmax)
			{
				drawall();
				xdum++;
				putlinev(xdum,ydum,1);
			}
			if(a=='a'&&xdum-1>=1)
			{
				drawall();
				xdum--;
				putlinev(xdum,ydum,1);
			}
			if(a=='w'&&ydum-1>=1)
			{
				drawall();
				ydum--;
				putlinev(xdum,ydum,1);
			}
			if(a=='s'&&ydum+1<=ymax)
			{
				drawall();
				ydum++;
				putlinev(xdum,ydum,1);
			}
			if(a=='q'&&!p[xdum][ydum].con1)
			{
				p[xdum][ydum].con1=1;
				if(player==1)
					player=2;
				else
					player=1;
				p[xdum][ydum].con1_p1=player;
				check();
				check1();
				drawall();
				end();
			}
			if(a=='r')
			{
				if(vert)
					vert=0;
				else
					vert=1;
				reposition();
				drawall();
				putline(xdum,ydum,1);
				goto begin;
			}
		}
	}
}
	
  
	
		
	
	

	
