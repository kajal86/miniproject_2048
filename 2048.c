#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>
unsigned int score=0;
unsigned int scheme=0;
void drawingBoard(unsigned int board[4][4]) {
	unsigned int x,y;
	char k, reset[] = "|";
        printf(" score= %d",score);
		for (y=0;y<4;y++) {
		for (x=0;x<4;x++) {
			printf("       ");
			printf("%s",reset);
		}
		printf("\n");
		for (x=0;x<4;x++) {
			if (board[x][y]!=0) {
				char s[8];
				snprintf(s,8,"%u",(unsigned int)1<<board[x][y]);
				unsigned int t = 7-strlen(s);
				printf("%*s%s%*s",t-t/2,"",s,t/2,"");
			} else {
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
	printf("       up, down, right, left, q        \n");
}
unsigned int Target(unsigned int array[4],unsigned int x,unsigned int s) {   //s=stop
	unsigned int t;
	if (x==0) {
		return x;
	}
	t=x-1;
	while(t>=0)  {
		if (array[t]!=0) {
			if (array[t]!=array[x]) {
				return t+1;
			}
			return t;
		} else {
			if (t==stop) {
				return t;
			}
		}
	t--;
	}
	return x;
}

void rotation(unsigned int board[4][4]) {
	unsigned int i,j,n=4;
	unsigned int tmp;
	for (i=0; i<n/2; i++) {
		for (j=i; j<n-i-1; j++) {
			tmp = board[i][j];
			board[i][j] = board[j][n-i-1];
			board[j][n-i-1] = board[n-i-1][n-j-1];
			board[n-i-1][n-j-1] = board[n-j-1][i];
			board[n-j-1][i] = tmp;
		}
	}
}
int slideArray(unsigned int array[4]) {
	int success = false;
	unsigned int x=0,t,stop=0;
        while(x<4)  {
		if (array[x]!=0) {
			t = findTarget(array,x,stop);
			if (t!=x) {
				if (array[t]==0) {
					array[t]=array[x];
				} else if (array[t]==array[x]) {
					array[t]++;
					score+=(unsigned int)1<<array[t];
					stop = t+1;
				}
				array[x]=0;
				success = true;
			}
		}
		x++;
	}
	return success;
}
int main(int argc, char *argv[]) {
	unsigned int board[4][4];
	char k;
	int success;
