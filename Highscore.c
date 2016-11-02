/**********************************************************************************
* Copyright  (C) Kajal Prakash Alam   alamkp15.it@coep.ac.in
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* This program is ditributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
**********************************************************************************/
#include <stdio.h> // fopen(), fclose(), fscanf()
#include <stdlib.h> // malloc()
#include <time.h>
struct Highscore {
	char *name;
	int score;
	char *time;
};
void initHiScore(struct Highscore Hisc[]);
void getHiScore(struct Highscore Hisc[]);
void setHiScore(struct Highscore Hisc[]);
void sortHiScore(struct Highscore Hisc[]);
void sortHiScore(struct Highscore Hisc[]) {
	int i, j;
	for (i = 0; i < 9; ++i) {

		for (j = 0; j < 9; ++j) {
			if (Hisc[j].score < Hisc[j + 1].score) {
				struct Highscore tmp = Hisc[j];
				Hisc[j] = Hisc[j + 1];
				Hisc[j + 1] = tmp;
			}
		}
	}
 }
void getHiScore(struct Highscore Hisc[]) {
	int temp1 = 0, read = 1;
	FILE *fd;
	if ((fd = fopen("hiscore.txt", "r")) == NULL) {
		fd = fopen("hiscore.txt", "w");
		initHiScore(Hisc);
		setHiScore(Hisc);
	}
	while (read != EOF) {
		Hisc[temp1].name = malloc( sizeof(char) * 11);
		Hisc[temp1].time = malloc( sizeof(char) * 17);
		read = fscanf(fd, "%s %d %s", Hisc[temp1].name, &(Hisc[temp1].score), Hisc[temp1].time);
		temp1++;
	}
	Hisc[temp1 - 1].name = "NONE";
	Hisc[temp1 - 1].time = "--:--_--/--/----";
	fclose(fd);
}
void setHiScore(struct Highscore Hisc[]) {
	int temp1;
	FILE *fd;
	fd = fopen("hiscore.txt", "w");
	sortHiScore(Hisc);
	for (temp1 = 0; temp1 < 10; temp1++)
		fprintf(fd, "%s %d %s\n", Hisc[temp1].name, Hisc[temp1].score, Hisc[temp1].time);
		fclose(fd);
}
void initHiScore(struct Highscore Hisc[]) {
	int k;
	for (k = 0; k < 10; k++) {
		Hisc[k].name = "NONE";
		Hisc[k].score = 0;
		Hisc[k].time = "--:--_--/--/----";
	}
}



