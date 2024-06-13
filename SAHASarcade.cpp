#include <graphics.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
int height=0,width=0;
int X_Full=0,Y_Full=0;
int Xratio=1,Yratio=1;
int page=0;

#define Xratio X_Full/1366 
#define Yratio Y_Full/768 

//2048
	int change=0,score=0,n=4;
	int win_continue=0;

	int shift_2048(int ar[4][4], int i, int j, int l)
	{
	    for(int k=j; k<(l-1); k++)
	    {
	        if (ar[i][k+1]!=0)
	        {
	            if(ar[i][k]==ar[i][k+1])
				{
	                score+=2*ar[i][k];
	                ar[i][k+1]=2*ar[i][k];//adds same number
	                ar[i][k]=0;//makes left element 0
	                change++;
	            }
	            return k+1;
	        }
	        else
	        {
	            ar[i][k+1]=ar[i][k];//shifting the selected element to the right
	            ar[i][k]=0;//making previous element 0
	            change++;
	        }
	    }
	    return l;
	}
	int play_2048(int ar[4][4], int i, int j)
	{ 
	    static int k=4;
	    if(i==n)
		{
	        return 0;
	    }
		else if(j==-1)
		{
			k=4;
	        play_2048(ar, i+1, n-2);
	    }
		else if(ar[i][j]==0)
		{
	        play_2048(ar, i, j-1);
	    }
		else
		{
	        k = shift_2048(ar, i, j, k);
	        play_2048(ar, i, j-1);
	    }
	}
	int caller_2048(int ar[4][4])
	{
		while(1)
		{
		    int temp[4][4];
		    if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState('W'))
			{
				while(GetAsyncKeyState(VK_UP)||GetAsyncKeyState('W'));
		        for(int i=0; i<4; i++)
				{
		            for(int j=0; j<4; j++)
					{
		                temp[i][j]=ar[i][4-1-j];
		            }
		        }
		        play_2048(temp,0,4-2);
		        for(int i=0; i<4; i++)
				{
		            for(int j=0; j<4; j++)
					{
		                ar[i][j]=temp[i][4-1-j];
		            }
		        }
		        return 1;
		    }
			else if(GetAsyncKeyState(VK_LEFT)||GetAsyncKeyState('A'))
			{
				while(GetAsyncKeyState(VK_LEFT)||GetAsyncKeyState('A'));
		        for(int i=0; i<4; i++)
				{
		            for(int j=0; j<4; j++)
					{
		                temp[i][j]=ar[4-1-j][i];
		            }
		        }
		        play_2048(temp,0,4-2);
		        for(int i=0; i<4; i++)
				{
		            for(int j=0; j<4; j++)
					{
		                ar[i][j]=temp[j][4-1-i];
		            }
		        }
		        return 1;
		    }
			else if(GetAsyncKeyState(VK_RIGHT)||GetAsyncKeyState('D'))
			{
				while(GetAsyncKeyState(VK_RIGHT)||GetAsyncKeyState('D'));
		        for(int i=0; i<4; i++)
				{
		            for(int j=0; j<4; j++)
					{
		                temp[i][j]=ar[j][4-1-i];
		            }
		        }
		        play_2048(temp,0,4-2);
		        for(int i=0; i<4; i++)
				{
		            for(int j=0; j<4; j++)
					{
		                ar[i][j]=temp[4-1-j][i];
		            }
		        }
		        return 1;
		    }
			else if(GetAsyncKeyState(VK_DOWN)||GetAsyncKeyState('S'))
			{
				while(GetAsyncKeyState(VK_DOWN)||GetAsyncKeyState('S'));
		        play_2048(ar,0,4-2);
		        return 1;
			}
			else if(GetAsyncKeyState(VK_ESCAPE))
			{
				while(GetAsyncKeyState(VK_ESCAPE));
	            return 0;
	        }
	    }
	}
	int win_check_2048(int ar[4][4])
	{
	    for (int i=0; i<4; i++)
		{
	        for(int j=0; j<4; j++)
			{
	            if(ar[i][j]==2048)
				{
					win_continue=1;
	                return 1;
	            }
	        }
	    }
	    return 0;
	}
	int generator_2048(int ar[4][4])
	{
	    int count=0;
	    for (int i=0; i<4; i++)
		{
	        for(int j=0; j<4; j++)
			{
	            if(ar[i][j]==0)
				{
	                count++;
	            }
	        }
	    }
	    if(count!=0)
		{
	        static int k=0;
	        srand(k);
	        int a=(rand())%4, b=(rand())%4;
	        if(ar[a][b]!=0)
			{
	            k++;
	            generator_2048(ar);
	        }
			else
			{
	            ar[a][b]=2;
	            k++;
	        }
	    }
		else
		{
	        return 0;
	    }
	}
	void grid_2048(int grid_ref_x[5],int grid_ref_y[5])
	{
		rectangle(grid_ref_x[0],grid_ref_y[0],grid_ref_x[4],grid_ref_y[4]);
		line(grid_ref_x[1],grid_ref_y[0],grid_ref_x[1],grid_ref_y[4]);
		line(grid_ref_x[2],grid_ref_y[0],grid_ref_x[2],grid_ref_y[4]);
		line(grid_ref_x[3],grid_ref_y[0],grid_ref_x[3],grid_ref_y[4]);
		line(grid_ref_x[0],grid_ref_y[1],grid_ref_x[4],grid_ref_y[1]);
		line(grid_ref_x[0],grid_ref_y[2],grid_ref_x[4],grid_ref_y[2]);
		line(grid_ref_x[0],grid_ref_y[3],grid_ref_x[4],grid_ref_y[3]);
	}	
	void print_score_2048()
	{
		char ch1[8]="Score: ";
		char ch2[16]="Press Escape to";
		char ch3[15]="Toggle Options";
		outtextxy(850*Xratio,200*Yratio,ch1);
		outtextxy(850*Xratio,450*Yratio,ch2);
		outtextxy(850*Xratio,520*Yratio,ch3);
		int score_board_ref[8]={850*Xratio,921*Xratio,992*Xratio,1064*Xratio,1135*Xratio,1207*Xratio,1278*Xratio,1350*Xratio};
		int length=1,temp=score;
		while(temp!=0)
		{
			length++;
			temp/=10;
		}
		length--;
		readimagefile("resources/2048/score_board.jpg",850*Xratio,265*Yratio,1350*Xratio,355*Yratio);
		temp=score;
		int digit;
		while(length!=0)
		{
			digit=temp%10;
			temp/=10;
			switch(digit)
			{
				case 0:
					readimagefile("resources/2048/digit_0.jpg",(score_board_ref[length-1]+5),270*Yratio,(score_board_ref[length]-5),350*Yratio);
					break;
				case 1:
					readimagefile("resources/2048/digit_1.jpg",(score_board_ref[length-1]+5),270*Yratio,(score_board_ref[length]-5),350*Yratio);
					break;
				case 2:
					readimagefile("resources/2048/digit_2.jpg",(score_board_ref[length-1]+5),270*Yratio,(score_board_ref[length]-5),350*Yratio);
					break;
				case 3:
					readimagefile("resources/2048/digit_3.jpg",(score_board_ref[length-1]+5),270*Yratio,(score_board_ref[length]-5),350*Yratio);
					break;
				case 4:
					readimagefile("resources/2048/digit_4.jpg",(score_board_ref[length-1]+5),270*Yratio,(score_board_ref[length]-5),350*Yratio);
					break;
				case 5:
					readimagefile("resources/2048/digit_5.jpg",(score_board_ref[length-1]+5),270*Yratio,(score_board_ref[length]-5),350*Yratio);
					break;
				case 6:
					readimagefile("resources/2048/digit_6.jpg",(score_board_ref[length-1]+5),270*Yratio,(score_board_ref[length]-5),350*Yratio);
					break;
				case 7:
					readimagefile("resources/2048/digit_7.jpg",(score_board_ref[length-1]+5),270*Yratio,(score_board_ref[length]-5),350*Yratio);
					break;
				case 8:
					readimagefile("resources/2048/digit_8.jpg",(score_board_ref[length-1]+5),270*Yratio,(score_board_ref[length]-5),350*Yratio);
					break;
				case 9:
					readimagefile("resources/2048/digit_9.jpg",(score_board_ref[length-1]+5),270*Yratio,(score_board_ref[length]-5),350*Yratio);
					break;
				default:
					break;
			}
			length--;
		}
	}
	void display_2048(int ar[4][4])
	{
		cleardevice();
		int grid_ref_x[5]={400*Xratio,500*Xratio,600*Xratio,700*Xratio,800*Xratio};
		int grid_ref_y[5]={200*Yratio,300*Yratio,400*Yratio,500*Yratio,600*Yratio};
		grid_2048(grid_ref_x,grid_ref_y);
		print_score_2048();
		readimagefile("resources/2048/logo.jpg",50*Xratio,150*Yratio,350*Xratio,450*Yratio);
	    for (int i=0; i<4; i++)
		{
	        for(int j=0; j<4; j++)
			{
	            if(ar[i][j]!=0)
	            {
	            	switch(ar[i][j])
	            	{
	            		case 2:
	            			readimagefile("resources/2048/2.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	            		case 4:
	            			readimagefile("resources/2048/4.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	            		case 8:
	            			readimagefile("resources/2048/8.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	            		case 16:
	            			readimagefile("resources/2048/16.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	            		case 32:
	            			readimagefile("resources/2048/32.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	            		case 64:
	            			readimagefile("resources/2048/64.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	            		case 128:
	            			readimagefile("resources/2048/128.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	            		case 256:
	            			readimagefile("resources/2048/256.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	            		case 512:
	            			readimagefile("resources/2048/512.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	           			case 1024:
	           				readimagefile("resources/2048/1024.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	           			case 2048:
	           				readimagefile("resources/2048/2048.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	           			case 4096:
	           				readimagefile("resources/2048/4096.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	           			case 8192:
	           				readimagefile("resources/2048/8192.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	           			case 16384:
	           				readimagefile("resources/2048/16384.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	           			case 32768:
	           				readimagefile("resources/2048/32768.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	            		case 65536:
	            			readimagefile("resources/2048/65536.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	            		case 131072:
	            			readimagefile("resources/2048/1131072.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);
	            			break;
	            		default:
	            			readimagefile("resources/2048/god_mode.jpg",grid_ref_x[i],grid_ref_y[j],grid_ref_x[i+1],grid_ref_y[j+1]);	
	            			break;
					}
				}
	        }
	    }
	}
	int checklose_2048(int ar[4][4])
	{
	    int count=0;
	    for (int i=0; i<4; i++)
		{
	        for(int j=0; j<4; j++)
			{
	            if(ar[i][j]==0)
				{
	                count++;
	            }
	        }
	    }
	    if(count==0)
		{
	        for (int i=0; i<4; i++)
			{
	            for(int j=0; j<4; j++)
				{
	                if((j!=3)&&ar[i][j]==ar[i][j+1])
					{
	                    return 0;
	                }
					else if((i!=3)&&ar[i][j]==ar[i+1][j])
					{
	                    return 0;
	                }
	            }
	        }
	    }
		else
		{
	        return 0;
	    }
	    return 1;
	}
	int win_menu_2048(int ar[4][4])
	{
		int choice=1;
		display_2048(ar);
		while(1)
		{
			setactivepage(page);
			setvisualpage(1-page);
			if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN))
			{
				choice=1-choice;
			}
			else if(GetAsyncKeyState(VK_RETURN))
			{
				return choice;
			}
			else if(GetAsyncKeyState(VK_RETURN))
				return choice;
			switch(choice)
			{
				case 0:
					readimagefile("resources/2048/win_quit.jpg",475*Xratio,250*Yratio,725*Xratio,550*Yratio);
					break;
				case 1:
				default:
					readimagefile("resources/2048/win_continue.jpg",475*Xratio,250*Yratio,725*Xratio,550*Yratio);
			}
			page=1-page;
			delay(150);
		}
	}
	int lose_menu_2048(int ar[4][4])
	{
		int choice=1;
		setactivepage(page);
		setvisualpage(1-page);
		display_2048(ar);
		page=1-page;
		while(1)
		{
			setactivepage(page);
			setvisualpage(1-page);
			if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN))
			{
				choice=1-choice;
			}
			else if(GetAsyncKeyState(VK_RETURN))
			{
				return choice;
			}
			switch(choice)
			{
				case 0:
					readimagefile("resources/2048/lose_quit.jpg",875*Xratio,250*Yratio,1225*Xratio,550*Yratio);
					break;
				case 1:
				default:
					readimagefile("resources/2048/lose_reset.jpg",875*Xratio,250*Yratio,1225*Xratio,550*Yratio);
			}
			page=1-page;
			delay(150);
		}
	}
	int options_2048(int ar[4][4])
	{
		int choice=1;
		display_2048(ar);
		while(1)
		{
			setactivepage(page);
			setvisualpage(1-page);
			if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN))
			{
				choice=1-choice;
			}
			else if(GetAsyncKeyState(VK_ESCAPE))
			{
				return 2;
			}	
			else if(GetAsyncKeyState(VK_RETURN))
			{
				return choice;
			}
			switch(choice)
			{
				case 0:
					readimagefile("resources/2048/options_quit.jpg",475*Xratio,250*Yratio,725*Xratio,550*Yratio);
					break;
				case 1:
				default:
					readimagefile("resources/2048/options_reset.jpg",475*Xratio,250*Yratio,725*Xratio,550*Yratio);
			}
			page=1-page;
			delay(100);
		}
	}
	void game_2048()
	{
		srand(time(0));
	    int x=rand()%4,y=rand()%4;
	    int ar[4][4];
	    for (int i=0; i<4; i++)
		{
	        for(int j=0; j<4; j++)
			{
	            ar[i][j]=0;
	        }
	    }
	    ar[x][y]=2;
	    display_2048(ar);
	    page=1-page;
	    while(1)
		{
			setactivepage(page);
			setvisualpage(1-page);
	        if(win_continue==0&&win_check_2048(ar)==1)	//player wins
			{
				if(win_menu_2048(ar)==0)					//player presses quit
				{
					break;
				}
				else								//player presses continue
				{
					display_2048(ar);
					page=1-page;
					continue;
				}
	        }
	        if(caller_2048(ar)==0)						//player presses Escape
	        {
	        	int option=options_2048(ar);
	        	if(option==0)						//player presses quit
	        	{
	        		break;
	        	}
	        	else if(option==1)					//player presses reset
	        	{
	        		score=0;
	        		for (int i=0; i<4; i++)
					{
	        			for(int j=0; j<4; j++)
						{
	            			ar[i][j]=0;
	       				}
	    			}
	    			generator_2048(ar);
	       			change=0;
				}
			}
	        if(change)								//generate new block of 2 only if there is a change the squares
			{
	            generator_2048(ar);
	            change=0;
	        }
	        if(checklose_2048(ar)==1)					//if the player loses
			{
	        	display_2048(ar);
	            delay(3000);
	            page=1-page;
	            if(lose_menu_2048(ar)==1)				//option for reset
	            {
	            	score=0;
	        		for (int i=0; i<4; i++)
					{
	        			for(int j=0; j<4; j++)
						{
	            			ar[i][j]=0;
	       				}
	    			}
	    			generator_2048(ar);
	       			change=0;
				}									//option for quit
				else
				{
					break;
				}
	        }
	        display_2048(ar);
	        delay(50);
	        page=1-page;
	    }
	}
	void start_2048()
	{
		width=GetSystemMetrics(SM_CXSCREEN),height=GetSystemMetrics(SM_CYSCREEN);
		X_Full=width,Y_Full=height;
		cleardevice();
		setbkcolor(WHITE);
		cleardevice();
		setcolor(BLACK);
		setlinestyle(0,0,3);
		settextstyle(3,0,7*Xratio);
		game_2048();
		score=0;
	}

//Air Hockey

	const double pi=2*acos(0.0);
	#define min(x,y) ((x)>(y))? (y):(x)
	#define max(x,y) ((x)>(y))? (x):(y)
	
	int X=10,Y=100;
	int goal_width=90,goal_height=125;
	int X1=0,Y1=0;//coordinates of top left corner of playable field
	int X2=0,Y2=0;//coordinates of bottom right corner of playable field
	
	int radius_striker=50,radius_ball=25;//radius of striker and ball are set
	int x1=0,y1=0;//coordinates of first striker
	int x2=0,y2=0;//coordinates of second striker
	int xb=0,yb=0;//coordinates of ball
	
	int speed_striker=10,speed_ball=20;//fixed speed of striker and ball
	double angle=90.0;
	
	int color_1=1,color_2=4;//color of first and second striker respectively
	int goal_1=0,goal_2=0;//goal counter for first and second player respectively
	int Time=0;
	int goal=0;//checks goal condition
	
	double rad(int degree)//converts degree to radian
	{
		return pi*degree/180.0;
	}
	double deg(double radi)//converts radian to degree
	{
		return 180.0*radi/pi;
	}
	void print_game_AH();
	void move_ball_AH();
	void goaling_AH(int who)//checks goal condition and updates value if goal is scored
	{
		goal=1;
		if(who==1)//gone into first players goal
		{
			goal_2++;//player 2 scores
			int ss=speed_ball;
			while(xb>X1-3*goal_width/4&&(yb>=(Y2+Y1)/2-goal_height+radius_ball)&&(yb<=(Y2+Y1)/2+goal_height-radius_ball))
			{
				print_game_AH();
				speed_ball=3;
				move_ball_AH();
				delay(10);
			}
			speed_ball=ss;
			x1=X1+radius_striker+10*Xratio;//reset striker 1 X coordinate
			y1=(Y2+Y1)/2;//reset striker 1 Y coordinate
			xb=(X2+X1)/2;//reset ball X coordinate to middle of playable field
			yb=(Y2+Y1)/2;//reset ball Y coordinate to middle of playable field
			x2=X2-radius_striker-10*Xratio;//reset striker 2 X coordinate
			y2=(Y2+Y1)/2;//reset striker 2 Y coordinate
			angle=90.0;//moves ball vertically next round so both players get fair chance to score
		}
		else
		{
			goal_1++;//player 1 scores
			int ss=speed_ball;
			while(xb<X2+3*goal_width/4 &&(yb>=(Y2+Y1)/2-goal_height+radius_ball)&&(yb<=(Y2+Y1)/2+goal_height-radius_ball))
			{
				print_game_AH();
				speed_ball=3;
				move_ball_AH();
				delay(10);
			}
			speed_ball=ss;
			x1=X1+radius_striker+10*Xratio;//reset striker 1 X coordinate
			y1=(Y2+Y1)/2;//reset striker 1 Y coordinate
			xb=(X2+X1)/2;//reset ball X coordinate to middle of playable field
			yb=(Y2+Y1)/2;//reset ball Y coordinate to middle of playable field
			x2=X2-radius_striker-10*Xratio;//reset striker 2 X coordinate
			y2=(Y2+Y1)/2;//reset striker 2 Y coordinate
			angle=90.0;//moves ball vertically next round so both players get fair chance to score
		}
		goal=0;//resets goal condition
		setvisualpage(1-page);
		readimagefile("resources/Air_Hockey/goal.jpg",(X1+X2)/2-150,(Y1+Y2)/2-75,(X1+X2)/2+150,(Y1+Y2)/2+75);
		settextstyle(4,HORIZ_DIR,3);//set text style to previous one
		sleep(2);
	}
	void boundary_AH()
	{
		if(xb<=(radius_ball+X1)&&(yb>=(Y2+Y1)/2-goal_height+radius_ball)&&(yb<=(Y2+Y1)/2+goal_height-radius_ball))
		{
			goaling_AH(1);
			return;
		}
		else if((xb+radius_ball)>=X2&&(yb>=(Y2+Y1)/2-goal_height+radius_ball)&&(yb<=(Y2+Y1)/2+goal_height-radius_ball))
		{
			goaling_AH(2);
			return;
		}
		if(xb<=(radius_ball+X1)||xb+radius_ball>=X2) 
		{
			angle=fmod(fmod(180.0-angle,360.0)+360.0,360.0);
		}
		if(yb<=(radius_ball+Y1) || yb+radius_ball>=Y2) 
		{	
			angle=fmod(fmod(360.0-angle,360.0)+360.0,360.0);
		}
	}
	int check_collision_AH()//function to check collision of ball and strikers
	{
		int ans=0;
		if(pow(x1-xb,2)+pow(y1-yb,2)<pow(radius_striker+radius_ball,2))//collision of ball with first striker
			ans++;
		if(pow(x2-xb,2)+pow(y2-yb,2)<pow(radius_striker+radius_ball,2))//collision of ball with second striker
			ans+=2;
		if(pow(x1-x2,2)+pow(y1-y2,2)<=pow(2*radius_striker,2))
			ans+=3;
		return ans;
	}
	void collision_AH()
	{
		if(pow(x1-xb,2)+pow(y1-yb,2)<=pow(radius_striker+radius_ball,2))
		{
			double theta=deg(atan((y1-yb)*1.0/(xb-x1)));
			if(yb==y1)
			{ 
				theta=(x1>xb)*(180);
			}
			else if(xb==x1)
			{ 
				theta=90+(yb>y1)*(180);
			}
			else if(x1>xb)
			{
				theta+=180.0;
			}
			double anglee=angle;
			angle=fmod(fmod(180.0+2*theta-angle,360.0)+360.0,360.0);
			int incx=round(speed_ball*cos(rad(anglee))),
			incy=round(speed_ball*sin(rad(anglee)));
			if(abs(anglee-angle)>10.0)
			{
				xb-=incx;
				yb+=incy;
			}
			else
			{ 
				move_ball_AH(); //Trying to debug tangential collisions with striker moving towards them
			}
		}
		else if(pow(x2-xb,2)+pow(y2-yb,2)<=pow(radius_striker+radius_ball,2))
		{
			double theta=deg(atan((y2-yb)*1.0/(xb-x2)));
			if(yb==y2)
			{ 
				theta=(x2>xb)*(180.0);
			}
			else if(xb==x2)
			{ 
				theta=90.0+(yb>y2)*(180.0);
			}
			else if(x2>xb)
			{
				theta+=180.0;
			}
			double anglee=angle;
			angle=fmod(fmod(180+2*theta-angle,360.0)+360.0,360.0);
			int incx=round(speed_ball*cos(rad(anglee))),
			incy=round(speed_ball*sin(rad(anglee)));
			if(abs(anglee-angle)>10.0)
			{
				xb-=incx;
				yb+=incy;
			}
			else
			{ 
				move_ball_AH(); //Trying to debug tangential collisions with striker moving towards them
			}
		}
	}
	void move_ball_AH()
	{
		int incx=round(speed_ball*cos(rad(angle)));//X component of speed of ball
		int incy=round(speed_ball*sin(rad(angle)));//Y component of speed of ball
		xb+=incx;//increment in X coordinate of ball
		yb-=incy;//increment in Y coordinate of ball
		if(goal==0 && (yb<((Y2+Y1)/2-goal_height+radius_ball)||yb>((Y2+Y1)/2+goal_height-radius_ball)))
		xb=max(xb,X1+radius_ball);
		if(goal==0 && (yb<((Y2+Y1)/2-goal_height+radius_ball)||yb>((Y2+Y1)/2+goal_height-radius_ball))) 
		xb=min(xb,X2-radius_ball);
		if(goal==0) 
		yb=max(yb,Y1+radius_ball);
		if(goal==0) 
		yb=min(yb,Y2-radius_ball);
	}
	void control_striker_AH()
	{
		int incx=0,incy=0;
		if(GetAsyncKeyState('W')) 
		{
			incy=speed_striker;
		}
		if(GetAsyncKeyState('A')) 
		{
			incx=-speed_striker;
		}
		if(GetAsyncKeyState('S')) 
		{	
			incy=-speed_striker;
		}
		if(GetAsyncKeyState('D'))
		{ 
			incx=speed_striker;
		}
		x1+=incx;
		y1-=incy;
		y1=max(y1,Y1+radius_striker);
		y1=min(y1,Y2-radius_striker);
		x1=max(x1,X1+radius_striker);
		x1=min(x1,(X2+X1)/2-radius_striker);
		if(check_collision_AH()>=1)
		{
			x1-=incx;
			y1+=incy;
		}
		incx=incy=0;
		if(GetAsyncKeyState(VK_RIGHT)) 
		{
			incx=speed_striker;
		}
		if(GetAsyncKeyState(VK_LEFT)) 
		{
			incx=-speed_striker;
		}
		if(GetAsyncKeyState(VK_UP)) 
		{
			incy=speed_striker;
		}	
		if(GetAsyncKeyState(VK_DOWN)) 
		{
			incy=-speed_striker;
		}
		x2+=incx;
		y2-=incy;
		y2=max(y2,Y1+radius_striker);
		y2=min(y2,Y2-radius_striker);
		x2=max(x2,(X2+X1)/2+radius_striker);
		x2=min(x2,X2-radius_striker);
		if(check_collision_AH()>=2)
		{
			x2-=incx;
			y2+=incy;
		}
	}
	void settings_AH()
	{
		cleardevice();
		setcolor(1);
		setlinestyle(0,0,5);
		rectangle(50,50,width-50,height-50);
		setfillstyle(SOLID_FILL,8);
		floodfill(width/2,height/2,1);
		char c1[]="Choose color for PLAYER 1:";
		settextstyle(3,HORIZ_DIR,7);
		outtextxy(width/4-100,100,c1);//prints text for player 1 to choose color
		char c2[]="Press 1 to choose";
		settextstyle(3,HORIZ_DIR,4);
		outtextxy(width/4-75,height-150,c2);
		char c3[]="Press 2 to choose";
		outtextxy(3*width/4-225,height-150,c3);
		setcolor(WHITE);
		setfillstyle(SOLID_FILL,1);//color choice 1
		circle(width/4+75,height/2+25,radius_striker*2.5);//prints first circle
		floodfill(width/4+75,height/2+25,WHITE);//fills circle 1 with first color choice
		circle(3*width/4-75,height/2+25,radius_striker*2.5);//prints second circle
		setfillstyle(SOLID_FILL,3);//color choice 2
		floodfill(3*width/4-75,height/2+25,WHITE);//fills circle 2 with second color choice
		setvisualpage(page);
		setactivepage(1-page);
		page=1-page;
		while(1)
		{
			if(GetAsyncKeyState('1'))
			{
				color_1=1;//assigns color choice 1 to striker 1
				break;
			}
			else if(GetAsyncKeyState('2'))
			{
				color_1=3;//assigns color choice 2 to striker 1
				break;
			}
			delay(10);
		}
		while(GetAsyncKeyState('1') || GetAsyncKeyState('2'))//to avoid misckicking of keys
		{
			delay(10);
		}
		cleardevice();
		setcolor(1);
		setlinestyle(0,0,5);
		rectangle(50,50,width-50,height-50);//outer border
		setfillstyle(SOLID_FILL,8);
		floodfill(width/2,height/2,1);
		char c4[]="Choose color for PLAYER 2:";//prints text for player 2 to chose color
		settextstyle(3,HORIZ_DIR,7);
		outtextxy(width/4-100,100,c4);
		char c5[]="Press 1 to choose";
		settextstyle(3,HORIZ_DIR,4);
		outtextxy(width/4-75,height-150,c5);
		char c6[]="Press 2 to choose";
		outtextxy(3*width/4-225,height-150,c6);
		setcolor(WHITE);
		setfillstyle(SOLID_FILL,4);//color choice 1
		circle(width/4+75,height/2+25,radius_striker*2.5);//prints first circle
		floodfill(width/4+75,height/2+25,WHITE);//fills circle 1 with first color choice
		circle(3*width/4-75,height/2+25,radius_striker*2.5);//prints second cirlce
		setfillstyle(SOLID_FILL,5);//color choice 2
		floodfill(3*width/4-75,height/2+25,WHITE);//fills circle 2 with second color choice
		setvisualpage(page);
		setactivepage(1-page);
		page=1-page;
		while(1)
		{
			if(GetAsyncKeyState('1'))
			{
				color_2=4;//assigns color choice 1 to striker 2
				break;
			}
			else if(GetAsyncKeyState('2'))
			{
				color_2=5;//assigns color choice 2 to striker 2
				break;
			}
			delay(10);
		}
		settextstyle(4,HORIZ_DIR,3);
	}
	void text_AH()//prints texts while game is running
	{
		char g1[3]="00";
		char g2[3]="00";
		char c1[]="TIME",c2[]="PLAYER 1",c3[]="PLAYER 2",c4[]="Press Escape",c5[]="for Menu",c6[]="Press Escape",c7[]="for Menu";
			g1[1]=(char)(goal_1%10+'0');
			g1[0]=(char)(goal_1/10+'0');
			g2[1]=(char)(goal_2%10+'0');
			g2[0]=(char)(goal_2/10+'0');
		outtextxy((X1+X2)/2-108,30,g1);
		outtextxy((X1+X2)/2+70,30,g2);
		char t[4];
			sprintf(t,"%d",Time);
			int tme=Time,sz=0;
		    while(tme>0){
				tme/=10;
				sz++;
			}
			sz=max(sz,1);
			outtextxy((X1+X2)/2-42,5,c1);
			outtextxy((X1+X2)/2-10*sz,38,t);
			outtextxy((X1+X2)/2-304,28,c2);
			outtextxy((X1+X2)/2+135,28,c3);
		outtextxy(X,18,c4);
		outtextxy(X,42,c5);
		outtextxy(width-230,18,c6);
		outtextxy(width-150,42,c7);
	}
	void print_movable_AH()
	{
		setcolor(15);
			circle(x1,y1,radius_striker);
			circle(x2,y2,radius_striker);
			circle(xb,yb,radius_ball);
		setfillstyle(SOLID_FILL,color_1);
			floodfill(x1,y1,15);
		setfillstyle(SOLID_FILL,color_2);
			floodfill(x2,y2,15);
		setfillstyle(SOLID_FILL,14);
			floodfill(xb,yb,15);
	}
	void color_AH()
	{
		setfillstyle(SOLID_FILL,2);
			floodfill(X1+2,Y1+2,BLACK);
			floodfill(X2-2,Y2-2,BLACK);
		setfillstyle(SOLID_FILL,9);
			floodfill(X1-10,(Y+height)/2,BLACK);
			floodfill((X1+X2)/2-10,(Y+height)/2,BLACK);
			floodfill((X1+X2)/2-100,40,BLACK);
		setfillstyle(SOLID_FILL,12);
			floodfill(X2+10,(Y+height)/2,BLACK);
			floodfill((X1+X2)/2+10,(Y+height)/2,BLACK);
			floodfill((X1+X2)/2+100,40,BLACK);
		setfillstyle(4,BLACK);//bleachers
			floodfill(X1-2,Y1+2,BLACK);
			floodfill(X1-2,Y2-2,BLACK);
			floodfill(X2+2,Y1+2,BLACK);
			floodfill(X2+2,Y2-2,BLACK);
	}
	void print_field_AH()
	{
		cleardevice();
		setcolor(BLACK);
		setlinestyle(0,0,3);
		//making stadium
		{
			rectangle(X,Y,width,height);
			rectangle(X,(Y+height)/2-goal_height,X+goal_width,(Y+height)/2+goal_height);//making left goal
			rectangle(width-goal_width,(Y+height)/2-goal_height,width,(Y+height)/2+goal_height);//making right goal
			rectangle(X1,Y1,X2,Y2);//making playable field
		}
		line((X1+X2)/2,Y1,(X1+X2)/2,Y2);//central line
		circle((X1+X2)/2,(Y1+Y2)/2,100);//making central circle
			rectangle((X1+X2)/2-50,0,(X1+X2)/2+50,80);//time square
			rectangle(((X1+X2)/2-50)-80,10,(X1+X2)/2-50,70);//score square 1
			rectangle(((X1+X2)/2+50)+80,10,(X1+X2)/2+50,70);//score square 2
			rectangle(((X1+X2)/2-50)-265,20,(X1+X2)/2-130,60);//name square 1
			rectangle(((X1+X2)/2+50)+265,20,(X1+X2)/2+130,60);//name square 2
	}
	void print_game_AH()
	{
		setactivepage(page);
		setvisualpage(1-page);
		print_field_AH();
		color_AH();
		text_AH();
		print_movable_AH();
		page=1-page;
	}
	void pause_screen_AH(int option)
	{
		setactivepage(page);
		setvisualpage(1-page);
		switch(option)
		{
			case 1:
				readimagefile("resources/Air_Hockey/pause_screen_resume.jpg",(X1+X2)/2-200,(Y1+Y2)/2-200,(X1+X2)/2+200,(Y1+Y2)/2+200);
				break;
			case 2:
				readimagefile("resources/Air_Hockey/pause_screen_reset.jpg",(X1+X2)/2-200,(Y1+Y2)/2-200,(X1+X2)/2+200,(Y1+Y2)/2+200);
				break;
			case 3:
				readimagefile("resources/Air_Hockey/pause_screen_settings.jpg",(X1+X2)/2-200,(Y1+Y2)/2-200,(X1+X2)/2+200,(Y1+Y2)/2+200);
				break;
			case 4:
				readimagefile("resources/Air_Hockey/pause_screen_quit.jpg",(X1+X2)/2-200,(Y1+Y2)/2-200,(X1+X2)/2+200,(Y1+Y2)/2+200);
				break;
			default:
				readimagefile("resources/Air_Hockey/pause_screen_resume.jpg",(X1+X2)/2-200,(Y1+Y2)/2-200,(X1+X2)/2+200,(Y1+Y2)/2+200);
		}
		page=1-page;
	}
	int pause_AH()
	{
		int option=1;
		while(1)
		{
			if(GetAsyncKeyState(VK_UP))
			{
				option--;
				if(option<1)
					option=4;
			}
			else if(GetAsyncKeyState(VK_DOWN))
			{
				option++;
				if(option>4)
					option=1;
			}
			else if(GetAsyncKeyState(VK_RETURN))
			{
				switch(option)
				{
					case 1:
						return 1;
						break;
					case 2:
						goal_1=0,goal_2=0,Time=0;
						xb=(X1+X2)/2,yb=(Y1+Y2)/2;
						x1=X1+radius_striker+10,y1=(Y1+Y2)/2;
						x2=X2-radius_striker-10,y2=(Y1+Y2)/2;
						angle=90.0;
						return 1;
						break;
					case 3:
						page=1-page;
						settings_AH();
						return 1;
						break;
					case 4:
						return 0;
						break;
					default:
						return 1;
				}
			}
			else if(GetAsyncKeyState(VK_ESCAPE))
			{	
				while(GetAsyncKeyState(VK_ESCAPE));
				return 1;
			}
			pause_screen_AH(option);
			delay(100);
		}
	}
	int game_AH()
	{
		time_t ti,tf;
		time(&ti);
		while(1)
		{
			time(&tf);
			if(ti!=tf)
			{//incrementing time
				ti=tf;
				Time++;
			}
			{//printing game screen
				print_game_AH();
			}
			{//physics	
				move_ball_AH();
				boundary_AH();
				collision_AH();
				control_striker_AH();
			}
			if(GetAsyncKeyState(VK_ESCAPE))
			{
				while(GetAsyncKeyState(VK_ESCAPE));
				int run_game=pause_AH();
				if(run_game==0)
				{
					break;
				}
			}
			delay(10);
		}
	}
	void start_AH()
	{
		width=GetSystemMetrics(SM_CXSCREEN),height=GetSystemMetrics(SM_CYSCREEN);
		X_Full=width,Y_Full=height;
		X1=X+goal_width,Y1=Y;
		X2=width-goal_width-10,Y2=height-20;
		x1=X1+radius_striker+10,y1=(Y1+Y2)/2;
		x2=X2-radius_striker-10,y2=(Y1+Y2)/2;
		xb=(X1+X2)/2,yb=(Y1+Y2)/2;
		sleep(5);
		cleardevice();
		height-=20;
		width-=10;
		setbkcolor(7);
		settings_AH();
		game_AH();
		goal_1=0,goal_2=0,Time=0;
		xb=(X1+X2)/2,yb=(Y1+Y2)/2;
		x1=X1+radius_striker+10,y1=(Y1+Y2)/2;
		x2=X2-radius_striker-10,y2=(Y1+Y2)/2;
		angle=90.0;
		height+=20;
		width+=10;
	}

//Snake Game
	int d=1;//direction of snake
	int dir=1;//dynamic map
	int rx=0,ry=0;//random variables for food 
	int f=1;//counter
	char lengtharr[3];
	int end=0;//to check if escape key is pressed 
	int endsnake(int e,int a);//when to end the game all 3 conditions)
	void start_SG()
	{
		cleardevice();
		width=GetSystemMetrics(SM_CXSCREEN),height=GetSystemMetrics(SM_CYSCREEN);
		X_Full=width,Y_Full=height;
		rx=(width/2)-((width/2)%10),ry=(height/2)-((height/2)%10);
		end=0;dir=1;d=1;
		int x[200],y[200],chk=700,length=1;
	
		for (int i=0;i<200;i++)
		{
			x[i]=0;
			y[i]=0;
		}
		
		int k=0;
		if (length>=5 && length<10)
			 k=1;
		else if (length>=10 && length<15)
		 	k=2;
		else if (length>=15 && length<20)
			 k=3;
		else if (length>=20) 
			k=4;
		delay(5-k);
		srand(time(NULL));
		setfillstyle(1,2);
		x[0]=(width/2)-((width/2)%10);
		y[0]=(height/2)-((height/2)%10);
		d=1;
		settextstyle(3, HORIZ_DIR, 7);
		for(;;)
		{
			setactivepage(page);
	        setvisualpage(1-page);
			setfillstyle(1,10);//set screen light green
			bar(10,210,width-10,height-10);
			setfillstyle(1,2);//boundary of game set green
			bar(0,200,width,210);
			bar(0,200,10,height);
			bar(0,height,width,height-10);
			bar(width-10,210,width,height);
			
			//making food appear after eating by snake
			if(x[0]==rx && y[0]==ry)
			{
				f++;
				length+=1;
				setfillstyle(1,4);
				bar(rx,ry,rx+10,ry+10);
				do
				{
					rx=20+rand()%(width-40);
					ry=210+rand()%(height-220);
				}
				while(getpixel(rx,ry)!=10  && rx>10 && ry>10);//to spawn food inside the boundary
				//convert to integer
				rx/=10;
				rx*=10;
				ry/=10;
				ry*=10;
			}
			setfillstyle(1,4); //foodcolor
			bar(rx,ry,rx+10,ry+10);
			
			//making food appear initially
			
			
			if(GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
			{
				d=1;
			}
			else if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
			{
				d=2;
			}
			else if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
			{
				d=3;
			}
			else if(GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
			{
				d=4;
			}
			else if(GetAsyncKeyState(VK_ESCAPE))
			{
				d=5;
			}
			else
			{
				d=0;
			}
			switch(d)
			{
				case 0:
					if(dir==1)
					{
						x[0]+=10;
					}
					else if(dir==2)
					{
						x[0]-=10;
					}
					else if(dir==3)
					{
						y[0]-=10;
					}
					else if(dir==4)
					{
						y[0]+=10;																																																				
					}
					else
					{
						d=0;
					}
					break;
					
				case 1:
					x[0]+=10;
					dir=1;
					break;
				case 2:
					x[0]-=10;
					dir=2;
					break;
					
				case 3:
					y[0]-=10;
					dir=3;
					break;
					
				case 4:
					y[0]+=10;
					dir=4;
					break;
				case 5:
					end+=1;
					break;
			}
			setfillstyle(1,9);//snakebodycolor
			for (int i=1;i<=length;i++)
			{
				bar(x[i],y[i],x[i]+10,y[i]+10);		
			}
			setfillstyle(1,1);//snakeheadcolor
			bar(x[0],y[0],x[0]+10,y[0]+10);
			for (int i=199;i>0;i--){
				x[i]=x[i-1];
				y[i]=y[i-1];
			}
			delay(100);
			for (int i=2;i<=length;i++){
				if(x[0]==x[i] && y[0]==y[i]){
					chk=i;//if snake collides with itself
				}
			}
			if(x[0]==x[chk] && y[0]==y[chk])
			{
				endsnake(f,0);
				break;
			}		
			if(x[0]>=width || x[0]<=0 || y[0]<=200 || y[0]>=height)
			{
				endsnake(f,1);//if snake collides with wall
				break;
			}
			if(end==1)
			{
				endsnake(f,2);//if esc is pressed
				break;
			}
	                 setcolor(RED);
	                 char ch1[20]="LENGTH ACHIEVED:";
	                 outtextxy(300,20,ch1);
	                 lengtharr[0]=char(48+length/10);
	                 lengtharr[1]=char(48+length%10);
	                 lengtharr[2]='\0';                 
	                 outtextxy(1070,20, lengtharr);
	                 
	    page = 1-page;
		}
	}
	int endsnake(int e,int a)
	{
		setcolor(RED);
		e=e-1;
		bar(0,200,width,height);
		delay(2000);
		page = 1-page;
		setactivepage(page);
        setvisualpage(1-page);
		cleardevice();
		char ch1[11]="GAME OVER!";
		outtextxy(width/2-200,height/2-100,ch1);
		if(a==1)
		{
			char ch2[30]="You crossed the boundary!";
			outtextxy(width/2-400,height/2,ch2);
		}
		else if (a==0)
		{
			char ch2[30]="You bumped into yourself!";
			outtextxy(width/2-400,height/2,ch2);		
		}
		else if (a==2)
		{
			char ch2[30]="You pressed esc key!";
			outtextxy(width/2-400,height/2,ch2);	
		}
		page = 1-page;
		setactivepage(page);
        setvisualpage(1-page);
        delay(3000);
		getch();
		return 0;
	}

int main()
{
	width=GetSystemMetrics(SM_CXSCREEN),height=GetSystemMetrics(SM_CYSCREEN);
	X_Full=width,Y_Full=height;
	initwindow(width,height,"",-3,-3);
	cleardevice();
	readimagefile("resources/opening_screen.jpg",0,0,width,height);
	sleep(5);
	cleardevice();
	int choice=0;
	page=0;
	while(1)
	{
		setvisualpage(page);
		setactivepage(1-page);
		if(GetAsyncKeyState(VK_DOWN))
		{
			while(GetAsyncKeyState(VK_DOWN));
			if(++choice>3)
			{
				choice=1;
			}
		}
		else if(GetAsyncKeyState(VK_UP))
		{
			while(GetAsyncKeyState(VK_UP));
			if(--choice<1)
			{
				choice=3;
			}
		}
		else if(GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
		else if(GetAsyncKeyState(VK_RETURN))
		{
			switch(choice)
			{
				case 1:
					cleardevice();
					page=1-page;
					setvisualpage(page);
					setactivepage(1-page);
					page=1-page;
					start_2048();
					break;
				case 2:
					cleardevice();
					page=1-page;
					setvisualpage(page);
					setactivepage(1-page);
					page=1-page;
					start_AH();
					break;
				case 3:
					cleardevice();
					page=1-page;
					setvisualpage(page);
					setactivepage(1-page);
					page=1-page;
					start_SG();
					break;
				default:
					break;
			}
		}
		switch(choice)
		{
			case 1:
				readimagefile("resources/main_menu.jpg",0,0,width,height);
				readimagefile("resources/icon_2048.jpg",800*Xratio,65*Yratio,1000*Xratio,265*Yratio);
				readimagefile("resources/icon_Air_Hockey.jpg",825*Xratio,285*Yratio,975*Xratio,435*Yratio);
				readimagefile("resources/icon_Snake_Game.jpg",825*Xratio,480*Yratio,975*Xratio,630*Yratio);
				break;
			case 2:
				readimagefile("resources/main_menu.jpg",0,0,width,height);
				readimagefile("resources/icon_2048.jpg",825*Xratio,90*Yratio,975*Xratio,240*Yratio);
				readimagefile("resources/icon_Air_Hockey.jpg",800*Xratio,260*Yratio,1000*Xratio,460*Yratio);
				readimagefile("resources/icon_Snake_Game.jpg",825*Xratio,480*Yratio,975*Xratio,630*Yratio);
				break;
			case 3:
				readimagefile("resources/main_menu.jpg",0,0,width,height);
				readimagefile("resources/icon_2048.jpg",825*Xratio,90*Yratio,975*Xratio,240*Yratio);
				readimagefile("resources/icon_Air_Hockey.jpg",825*Xratio,285*Yratio,975*Xratio,435*Yratio);
				readimagefile("resources/icon_Snake_Game.jpg",800*Xratio,455*Yratio,1000*Xratio,655*Yratio);
				break;
			default:
				readimagefile("resources/main_menu.jpg",0,0,width,height);
				readimagefile("resources/icon_2048.jpg",825*Xratio,90*Yratio,975*Xratio,240*Yratio);
				readimagefile("resources/icon_Air_Hockey.jpg",825*Xratio,285*Yratio,975*Xratio,435*Yratio);
				readimagefile("resources/icon_Snake_Game.jpg",825*Xratio,480*Yratio,975*Xratio,630*Yratio);
				break;
		}
		page=1-page;
		delay(250);
	}
	getch();
	closegraph();
	
}
