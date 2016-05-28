#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct{
	char tipps,
		 all[10][4],
		 v_controll[10][4];
} m_game;

m_game m;

char v1;

void menu_outl(){
	printf("\nJ\xa0t\x82k: 1-es gomb\nKil\x82p\x82s: 0-as gomb\nV\xa0lasztott men\x81pont: ");
}

void init(){
	char i,j;

	printf("Initialization...");
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 4; j++) {
			m.all[i][j] = ' ';
			m.v_controll[i][j] = 0;
		}
	}
	v1 = 1;
	srand(time(NULL));
	m.tipps = 0;
	printf("\nReady!\n\n");
	menu_outl();
}

void call_rand_col(char *game_nums){
	char i;

	for (i = 0; i < 4; i++) {
		game_nums[i] = '1' + rand()%6 ;
	}

}

char control(char *tipp, char *game_nums){
	char i,j,k, result = 1,
		 temp[4], good[4],
		 max, v_res;

	for (i = 0; i < 4; i++) {
		temp[i] = 0;
		good[i] = 1;
	}

	for (i = 0; i < 4; i++){
		if (tipp[i] == game_nums[i]) {
			for (j = 0;m.v_controll[m.tipps-1][j] != 0; j++);
			m.v_controll[m.tipps-1][j] = 'X';
			good[i] = 0;
		}
	}

	for (i = 0; i < 4; i++) {
		if (good[i]) {
			k = max = v_res = 0;

			for (j = 0; j < 4; j++) {
				if (game_nums[j] == tipp[i]) {
					max++;
				}
			   if ((!good[j])&&(tipp[i] == game_nums[j])) {
					v_res++;
			   }
			}
			for (j = 0; j < 4; j++) {
                if (tipp[i] == temp[j]) {
				   v_res++;
				}
			}

			if (v_res < max) {
				v_res++;
				for (k = 0; temp[k] != 0; k++); 
				temp[k] = tipp[i];
			}
		}
	}

	for (i = 0; i < 4; i++) {
		if (good[i]) {
			result = 0;
			break;
		}
	}

	if (result) {
		printf("Gratul\xa0lok, t\x94%bb eszed van egy mar\x82knyi lepk\x82n\x82l! =)\n");
	} else {
		for (i = 0;i < 4; i++) {
			if (temp[i] != 0) {
				for (k = 0; m.v_controll[m.tipps-1][k] != 0; k++);
				m.v_controll[m.tipps-1][k] = 'O';
			}
		}
	}

	return result;//megoldást talált a júzer
}

void game(char *tipp, char *game_nums){
	char i;

	if ((m.tipps++) == 10) {
		printf("\nSzar vagy!\n");
		v1 = 2;
	}else{
		printf("\nTippelj, kedves bar\xa0tom: ");
		scanf("%s",tipp=m.all[m.tipps-1]);

		if (control(tipp,game_nums))
			v1 = 2;

		printf("\nJelenleg \xa1gy \xa0llsz:\n\n");
		for (i = 0; i < m.tipps; i++)
			printf("%d. Tipp: %c%c%c%c - V\xa0lasz: %c%c%c%c\n",i+1,m.all[i][0],m.all[i][1],
				m.all[i][2],m.all[i][3],m.v_controll[i][0],m.v_controll[i][1],m.v_controll[i][2],m.v_controll[i][3]);

	}
}

int main(void){
	char *game_nums,
		 *tipp;
	init();

	while(v1){
		scanf("%s",&v1);
		switch (v1) {
			case '1':
				call_rand_col(&game_nums);
				while (v1 == '1'){
					game(&tipp,&game_nums);
				}
				break;
			case '0':
				v1 = 0;
				break;
		default:
			printf("P\x94\cs vagy, v\xa0lassz egy rendes men\x81pontot!\n");
			;
		}
		menu_outl();
	}

	return 0;
}
