#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>
unsigned int score = 0;
unsigned int plan = 0;
void drawingBoard(unsigned int board[4][4]) {
	unsigned int x, y;
	char k, reset[] = "|";
        printf(" score = %d", score);
		for (y = 0; y < 4; y++) {
			for (x = 0; x < 4; x++) {
				printf("       ");
				printf("%s", reset);
				}
			printf("\n");
			for (x = 0; x < 4; x++) {
				if (board[x][y] != 0) {
				char s[8];
				snprintf(s, 8, "%u", (unsigned int)1<<board[x][y]);
				unsigned int t = 7-strlen(s);
				printf("%*s%s%*s",t-t/2,"",s,t/2,"");
				}
			 	else {
				printf("   ·   ");
				}
			printf("%s",reset);
			}
			printf("\n");
			x=0;
			while(x<4) {
				printf("       ");
				printf("%s",reset);
				x++;
				}
			printf("\n");
		}
	printf("\n");
	printf(".....move up, down, left, right.....\n");
}
unsigned int Target(unsigned int A[4],unsigned int p,unsigned int s) {   //s=stop
	unsigned int w,T;
	if (p==0) {
		return T;
	}
	T=p-1;
	if(T>=0)  {
		if (A[T]!=0) {
			if (A[T]!=A[p]) {
				return T+1;
				}
				return T;
				} 
			else {
				if (T==s) {
				return T;
			}
		}
	T--;
	}
	return p;
}
int slidingarr(unsigned int A[4]) {
	int success = false;
	unsigned int x=0,T,stop=0;
	do  {
		if (A[x]!=0) {
			T = Target(A,x,stop);
			if (T!=x) {
				if (A[T]==0) {
					A[T]=A[x];
				} else if (A[T]==A[x]) {
					A[T]++;
					score+=(unsigned int)1<<A[T];
					stop = T+1;
				}
				A[x]=0;
				success = true;
			}
		}
		x++;
	} while(x<4);
	return success;

}
void rotation(unsigned int board[4][4]) {
	unsigned int i,j,N=4;
	unsigned int tmp;
	for (i=0; i<N/2; i++) {
		for (j=i; j<N-i-1; j++) {
			tmp = board[i][j];
			board[i][j] = board[j][N-i-1];
			board[j][N-i-1] = board[N-i-1][N-j-1];
			board[N-i-1][N-j-1] = board[N-j-1][i];
			board[N-j-1][i] = tmp;
		}
	}
}
int moveUp(unsigned int board[4][4]) {
	int i, j, k;
	for(i=0; i<4 ;i++)       
   		for(j=0; j<4 ;j++)  {
      			if(!board[j][i])    {
			         for(k=j+1; k<4 ;k++)  
			            if(board[k][i])            {
               			     	board[j][i]=board[k][i]; 
               				board[k][i]=0;          
               				break;
           				}
				}
			}
		}
int moveLeft(unsigned int board[4][4]) {
	int success;
	rotation(board);
	success = moveUp(board);
	rotation(board);
	return success;
}

int moveDown(unsigned int board[4][4]) {
	int success;
	rotation(board);
	success = moveUp(board);
	rotation(board);
	return success;
}

int moveRight(unsigned int board[4][4]) {
	int success;
	rotation(board);
	success = moveUp(board);
	rotation(board);
	return success;
}
int findpairDown(unsigned int board[4][4]) {
	int success = false;
	unsigned int x,y;
	for (x=0;x<4;x++) {
		for (y=0;y<3;y++) {
			if (board[x][y]==board[x][y+1]) return true;
				}
			}
	return success;
}
unsigned int nocount(unsigned int board[4][4]) {
	unsigned int x,y;
	unsigned int count=0;
	for (x=0;x<4;x++) {
		for (y=0;y<4;y++) {
			if (board[x][y]==0) {
				count++;
			}
		}
	}
	return count;
}
int gameEnded(unsigned int  board[4][4]) {
	int ended = true;
	if (nocount(board)>0) return false;
	if (findpairDown(board)) return false;
	rotation(board);
	if (findpairDown(board)) ended = false;
	rotation(board);
	return ended;
}
void addRandom(unsigned int board[4][4]) {
	static int initialized = false;
	unsigned int x,y;
	unsigned int r,length=0;
	unsigned int n,list[16][2];

	if (!initialized) {
		srand(time(NULL));
		initialized = true;
	}

	for (x=0;x<4;x++) {
		for (y=0;y<4;y++) {
			if (board[x][y]==0) {
				list[length][0]=x;
				list[length][1]=y;
				length++;
			}
		}
	}

	if (length>0) {
		r = rand()%length;
		x = list[r][0];
		y = list[r][1];
		n = (rand()%10)/9+1;
		board[x][y]=n;
	}
}
void initBoard(unsigned int board[4][4]) {
	unsigned int x,y;
	for (x=0;x<4;x++) {
		for (y=0;y<4;y++) {
			board[x][y]=0;
		}
	}
	addRandom(board);
	drawingBoard(board);
	score = 0;
}
void setBufferedInput(bool enable) {
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		// restore the former settings
		tcsetattr(STDIN_FILENO,TCSANOW,&old);
		// set the new state
		enabled = true;
	} else if (!enable && enabled) {
		// get the terminal settings for standard input
		tcgetattr(STDIN_FILENO,&new);
		// we want to keep the old setting to restore them at the end
		old = new;
		// disable canonical mode (buffered i/o) and local echo
		new.c_lflag &=(~ICANON & ~ECHO);
		// set the new settings immediately
		tcsetattr(STDIN_FILENO,TCSANOW,&new);
		// set the new state
		enabled = false;
	}
}
int main(int argc, char *argv[]) {
	unsigned int board[4][4];
	char k;
	int success,d;
	initBoard(board);
	setBufferedInput(false);
	while (true) {
		d=getchar();
		switch(d) {
			case 1:
			case 2:
			case 3:
				success = moveLeft(board);  break;
			case 97:	
			case 104:	
			case 68:	
				success = moveLeft(board);  break;
			case 100:	
			case 108:	
			case 67:	
				success = moveRight(board); break;
			case 119:	
			case 107:	
			case 65:
				success = moveUp(board);    break;
			case 115:	
			case 106:	
			case 66:	
				success = moveDown(board);  break;
			default: success = false;
		}
		if (success) {
			drawingBoard(board);
			usleep(150000);
			addRandom(board);
			drawingBoard(board);
			if (gameEnded(board)) {
				printf("......Game over.......\n");
				break;
			}
		}
		}
	setBufferedInput(true);
	return EXIT_SUCCESS;
}
