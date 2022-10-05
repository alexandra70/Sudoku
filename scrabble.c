#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "scrabble.h"
#include "print_board.h"

#define MAX_LINE_SIZE 50
#define INPUT_LINE_CERINTA 0
#define INPUT_LINE_NR_CUVINTE 0
#define INPUT_LINE_Y 0
#define INPUT_LINE_X 2
#define INPUT_LINE_D 4
#define INPUT_LINE_CUVANT 6

int puncte[26];

int putere(int b, int e) {
	int r = 1;
	for (int i = 0; i < e; i++)
		r *= b;
	return r;
}

int get_number() {
	
	char* citeste = (char*)malloc(2);
	int numar_intors = 0;
	fgets(citeste, 2, stdin);
	//48 - ascii pt 0 si 57 => 9
	while (citeste[0] > 47 && citeste[0] < 58) {
		numar_intors = numar_intors * 10 + (citeste[0] - 48);
		fgets(citeste, 2, stdin);
	}
	return numar_intors;
}

void citire(char table[BOARD_SIZE][BOARD_SIZE]) {
	int N = get_number();
	char* cuvant = (char*)malloc(BOARD_SIZE + 1);
	for (int i = 0; i < N; i++) {
		int y = get_number();
		int x = get_number();
		int d = get_number();
		fgets(cuvant, BOARD_SIZE + 1, stdin);
		 
		if (d == 0) {
			int l = 0;
			for (int j = x; j <= BOARD_SIZE; j++) {
				if (cuvant[l] < 65 || cuvant[l] > 90) {
					break;
				}
				else {
					table[y][j] = cuvant[l];
					l++;
				}
			}
		}
		if (d == 1) {
			int l = 0;
			for (int j = y; j <= BOARD_SIZE; j++) {
				if (cuvant[l] < 65 || cuvant[l] > 90) {
					break;
				}
				else {
					table[j][x] = cuvant[l];
					l++;
				}
			}
		}
	}
}

int get_words(char*** words) {

	int N = get_number();
	char* cuvant = (char*)malloc(BOARD_SIZE + 1);
	*words = (char**)malloc(N * sizeof(char*));

	for (int i = 0; i < N; i++) {

		get_number();
		get_number();
		get_number();
		fgets(cuvant, BOARD_SIZE + 1, stdin);

		(*words)[i] = (char*)malloc(strlen(cuvant) * sizeof(char));	
		strncpy((*words)[i], cuvant, strlen(cuvant));
	}
	
	return N;
}


void task_bonus() {

	char* cuvant = (char*)malloc(BOARD_SIZE + 1);
	char* bonus1;
	char* bonus2;

	bonus1 = (char*)malloc(2 * sizeof(char));
	bonus2 = (char*)malloc(2);

	fgets(cuvant, BOARD_SIZE + 1, stdin);
	strncpy(bonus1, cuvant, 2);

	fgets(cuvant, BOARD_SIZE, stdin);
	strncpy(bonus2, cuvant, 2);

	int N = get_number();

	int punctaj1 = 0;
	int punctaj2 = 0;
	int xi;
	int yi;
	int di;

	for (int i = 0; i < N; i++) {

		yi = get_number();
		xi = get_number();
		di = get_number();

		fgets(cuvant, BOARD_SIZE + 1, stdin);

		int scor_cuvant = 0;

		for (int l = 0; cuvant[l] != '\n'; l++) {
			scor_cuvant += puncte[cuvant[l] - 'A'];
		}

		int has1 = 0;
		int has2 = 0;

		if (di == 0) {
			for (int j = xi; j < xi + strlen(cuvant) - 1; j++) {
				if (bonus_board[yi][j] == 1) {
					has1++;
				}
				if (bonus_board[yi][j] == 2) {
					has2++;
				}
			}
		}

		if (di == 1) {
			for (int j = yi; j < yi + strlen(cuvant) - 1; j++) {
				if (bonus_board[j][xi] == 1) {
					has1++;
				}
				if (bonus_board[j][xi] == 2) {
					has2++;
				}
			}
		}
		if (has1) {
			for (int l = 0; l < strlen(cuvant) - 2; l++) {
				if (cuvant[l] == bonus1[0]) {
					if (cuvant[l + 1] == bonus1[1]) {
						scor_cuvant *= putere(2, has1);
						break;
					}
				}
			}
		}

		if (has2) {
			if (cuvant[strlen(cuvant) - 3] == bonus2[0]) {
				if (cuvant[strlen(cuvant) - 2] == bonus2[1]) {
					scor_cuvant *= putere(3, has2);
				}
			}
		}

		if (i % 2 == 0) {
			punctaj1 += scor_cuvant;
		}
		if (i % 2 != 0) {
			punctaj2 += scor_cuvant;
		}
	}
	printf("Player 1: %d Points\n", punctaj1);
	printf("Player 2: %d Points\n", punctaj2);

}

int scor(char* cuvant, int y, int x, int d, char* bonus1, char* bonus2) {

	int scor_cuvant = 0;

	for (int l = 0; l < strlen(cuvant); l++) {
		scor_cuvant += puncte[cuvant[l] - 'A'];
	}
	int has1 = 0;
	int has2 = 0;

	if (d == 0) {//verific pe orizontala pe y
		for (int i = x; i < strlen(cuvant) + x; i++) {
			if (bonus_board[y][i] == 1) {
				has1++;
			}
			if (bonus_board[y][i] == 2) {
				has2++;
			}
		}
	}

	if (d == 1) {//verific pe verticala pe x
		for (int i = y; i < strlen(cuvant) + y; i++) {
			if (bonus_board[i][x] == 1) {
				has1++;
			}
			if (bonus_board[i][x] == 2) {
				has2++;
			}
		}
	}

	if (has1) {
		for (int l = 0; l < strlen(cuvant)-1; l++) {
			if (bonus1[0] == cuvant[l]) {
				if (bonus1[1] == cuvant[l + 1]) {
					for (int i = 1; i <= has1; i++) {
						scor_cuvant *= 2;
					}
					break;
				}
			}
		}
	}

	if (has2) {
		if (bonus2[0] == cuvant[strlen(cuvant) - 2]) {
			if (bonus2[1] == cuvant[strlen(cuvant) - 1]) {
				for (int i = 1; i <= has2; i++) {
					scor_cuvant *= 3;
				}
			}
		}
	}	
	return scor_cuvant;
}

void task_put_word(char table[BOARD_SIZE][BOARD_SIZE]) {

	char* bonus1;
	char* bonus2;

	bonus1 = (char*)malloc(2 * sizeof(char));
	bonus2 = (char*)malloc(2 * sizeof(char));

	char* cuvant = (char*)malloc((BOARD_SIZE + 2) * sizeof(char));

	fgets(bonus1, BOARD_SIZE, stdin);
	fgets(bonus2, BOARD_SIZE, stdin);
	
	int N = get_number();
	
	int vector_vizite[NUM_WORDS] = { 0 };

	for (int i = 0; i < N; i++) {

		int yi = get_number();
		int xi = get_number();
		int di = get_number();

		fgets(cuvant, BOARD_SIZE + 2, stdin);

		for (int l = 0; cuvant[l] != '\0'; l++) {
			if (cuvant[l] == '\n') {
				cuvant[l] = '\0';
				break;
			}
		}
		if (di == 0) {
			int l = 0;
			for (int x = xi; x < BOARD_SIZE + 1; x++) {
				if (cuvant[l] < 65 || cuvant[l] > 90) {
					break;
				}
				table[yi][x] = cuvant[l];
				l++;
			}
		}
		if (di == 1) {
			int l = 0;
			for (int y = yi; y < BOARD_SIZE + 1; y++) {
				if (cuvant[l] < 65 || cuvant[l] > 90) {
					break;
				}
				table[y][xi] = cuvant[l];
				l++;
			}
		}
		for (int w = 0; w < NUM_WORDS; w++) {
			if (strcmp(words[w], cuvant) == 0) {
				vector_vizite[w] = 1;
			}
		}

	}
	int spatiu = 0;
	for (int w = 0; w < NUM_WORDS; w++) {
		if (vector_vizite[w] == 1) {
			continue;
		}
		if (vector_vizite[w] == 0) {
			for (int i = 0; i < BOARD_SIZE; i++) {
				for (int j = 0; j < BOARD_SIZE; j++) {
					if (table[i][j] == words[w][0]) {
						if (strlen(words[w]) + j - 1 < BOARD_SIZE) {
							spatiu = 0;
							for (int x = j + 1; x <= strlen(words[w]) + j - 1; x++) {
								if (table[i][x] == '.') {
									spatiu++;
								}
							}
							if (spatiu == strlen(words[w]) - 1) {
								for (int l = 1; l < strlen(words[w]); l++) {
									table[i][j+l] = words[w][l];
								}
								return;		
							}
						}
						if (strlen(words[w]) + i - 1 < BOARD_SIZE) {
							spatiu = 0;
							for (int y = i + 1; y <= strlen(words[w]) + i - 1; y++) {
								if (table[y][j] == '.') {
									spatiu++;
								}
							}
							if (spatiu == strlen(words[w]) - 1) {
								for (int l = 1; l < strlen(words[w]); l++) {
									table[i + l][j] = words[w][l];
								}
								return;
							}
						}
					}
				}
			}
		}
	}
}

int task5(char table[BOARD_SIZE][BOARD_SIZE]) {
	char* bonus1;
	char* bonus2;
	bonus1 = (char*)malloc(2 * sizeof(char));
	bonus2 = (char*)malloc(2 * sizeof(char));

	char* cuvant;
	cuvant = (char*)malloc((BOARD_SIZE + 2) * sizeof(char));
	fgets(bonus1, BOARD_SIZE, stdin);
	fgets(bonus2, BOARD_SIZE, stdin);

	//printf("%s%s", bonus1, bonus2);
	int N = get_number();
	//printf("%d\n", N);
	int yi;
	int xi;
	int di;

	int scor1 = 0;
	int scor2 = 0;

	for (int i = 0; i < N; i++) {
		yi = get_number();
		xi = get_number();
		di = get_number();
		fgets(cuvant, BOARD_SIZE + 2, stdin);

		if (di == 0) { //pe orizontala
			int l = 0;
			for (int x = xi; x < BOARD_SIZE + 1; x++) {
				if (cuvant[l] < 65 || cuvant[l] > 90) {
					break;
				}
				table[yi][x] = cuvant[l];
				l++;
			}
		}
		if (di == 1) { //pe orizontala
			int l = 0;
			for (int y = yi; y < BOARD_SIZE + 1; y++) {
				if (cuvant[l] < 65 || cuvant[l] > 90)
					break;
				table[y][xi] = cuvant[l];
				l++;

			}
		}

		cuvant[strlen(cuvant) - 1] = '\0';
		
		if(i % 2 == 0)
			scor1 += scor(cuvant, yi, xi, di, bonus1, bonus2);
		else
			scor2 += scor(cuvant, yi, xi, di, bonus1, bonus2);

		int vizite[NUM_WORDS] = { 0 };

		for (int w = 0; w < NUM_WORDS; w++) {
			if (strcmp(words[w],cuvant) == 0) {
				vizite[w] = 1;
			}
		}
	}

	int ymax;
	int xmax;
	int dmax;
	int scor_max = 0;
	int wmax;
	int spatiu;

	for (int w = 0; w < NUM_WORDS; w++) {
		if (words[w] == 1) {
			break;
		}
		for(int y = 0; y < BOARD_SIZE; y++) {
			for (int x = 0; x < BOARD_SIZE; x++) {
				if (words[w][0] == table[y][x]) {
					if (strlen(words[w]) + x - 1 < BOARD_SIZE) {
						spatiu = 0;
						for (int i = x; i <= strlen(words[w]) + x - 1; i++) {
							if (table[y][i] == '.') {
								spatiu++;
							}
						}
						if(spatiu == strlen(words[w]) - 1){
							int s = scor(words[w], y, x, 0, bonus1, bonus2);
							if (s == scor_max) {
								if (ymax > y) {
									xmax = x;
									ymax = y;
									wmax = w;
									dmax = 0;
								}
							}
							if (s > scor_max) {
								dmax = 0;
								scor_max = s;
								ymax = y;
								xmax = x;
								wmax = w;
							}
						}
					}
					if (strlen(words[w]) + y - 1 < BOARD_SIZE) {
						spatiu = 0;
						for (int i = y; i <= strlen(words[w]) + y - 1; i++) {
							if (table[i][x] == '.') {
								spatiu++;

							}
						}
							
						if (spatiu == strlen(words[w]) - 1) {
							int s = scor(words[w], y, x, 1, bonus1, bonus2);
							if (s > scor_max) {
								dmax = 1;
								scor_max = s;
								ymax = y;
								xmax = x;
								wmax = w;
							}
						}
					}
				}
			}
		}
	}

	if (dmax == 0) {
		int l = 1;
		for(int i = xmax + 1; i <= xmax+ strlen(words[wmax]) - 1; i++){
			table[ymax][i] = words[wmax][l];
			l++;
		}
	}
	if (dmax == 1) {
		int l = 1;
		for (int i = ymax + 1; i <= ymax + strlen(words[wmax]) - 1; i++) {
			table[i][xmax] = words[wmax][l];
			l++;
		}
	}
	
	scor2 += scor_max;
	if (scor1 > scor2)
		return 0;
	else 
		return 1;
}

void task6(char table[BOARD_SIZE][BOARD_SIZE]) {

	char* bonus1;
	char* bonus2;
	char* cuvant;
	char* cuvant_player2;
	
	bonus1 = (char*)malloc(2 * sizeof(char));
	bonus2 = (char*)malloc(2 * sizeof(char));

	fgets(bonus1, BOARD_SIZE, stdin);
	fgets(bonus2, BOARD_SIZE, stdin);

	int N = get_number();
	int yi;
	int xi;
	int di;
	int vizite[NUM_WORDS] = { 0 };
	int scor1;
	int scor2;

	for (int i = 0; i < N; i++) {

		yi = get_number();
		xi = get_number();
		di = get_number();

		cuvant = (char*)malloc((BOARD_SIZE + 2) * sizeof(char));
		fgets(cuvant, BOARD_SIZE + 2, stdin);
		
		cuvant[strlen(cuvant) - 1] = '\0';
	
		scor1 += scor(cuvant, yi, xi, di, bonus1, bonus2);

		if (di == 0) {
			int l = 0;
			for (int x = xi; x < BOARD_SIZE; x++) {
				if (cuvant[l] < 65 || cuvant[l] > 90) {
					break;//dc cuvant nu e orice litera mare
				}
				table[yi][x] = cuvant[l];
				l++;
			}
		}

		if (di == 1) {
			int l = 0;
			for (int y = yi; y < BOARD_SIZE; y++) {
				if (cuvant[l] < 65 || cuvant[l] > 90) {
					break;
				}
				table[y][xi] = cuvant[l];
				l++;
			}
		}

		for (int w = 0; w < NUM_WORDS; w++) {
			if (strcmp(cuvant, words[w]) == 0) {
				vizite[w] = 1;
			}
		}
	}

	int spatiu = 0;
	int ymax;
	int xmax;
	int dmax;
	int wmax;
	int max_score = 0;
	int n = N;
	while (n > 0) {
		max_score = 0;
		
		for (int w = 0; w < NUM_WORDS; w++) {
			if (vizite[w] == 1) {
				continue;
			}
			for (int y = 0; y < BOARD_SIZE; y++) {
				for (int x = 0; x < BOARD_SIZE; x++) {
					if (table[y][x] == words[w][0]) {
						if (y == 2 && x == 6)
							printf("%s\n", words[w]);
						//depaseste limitele tablei
						if (strlen(words[w]) + x < BOARD_SIZE) {
							spatiu = 0;
							int l = 1;
							for (int i = x + 1; i < strlen(words[w]) + x; i++) {
								if (table[y][i] == '.' || table[y][i] == words[w][l]) {
									spatiu++;
								}
								l++;
							}
							//face max
							if (spatiu == strlen(words[w]) - 1) {
								//calculeaza scor
								int s = scor(words[w], y, x, 0, bonus1, bonus2);
								//dc scorul e mai mare decat cel de dinainte retine noul scor 
								//si pozitia la care se alfa cuvantul
								if (s > max_score) {
									max_score = s;
									ymax = y;
									xmax = x;
									wmax = w;
									dmax = 0;
								}
								if (y == 2 && x == 6)
									printf("S1: %d %s\n", s, words[w]);
								if (y == 7 && x == 9)
								if (s == max_score) {
									if (ymax > y) {
										max_score = s;
										ymax = y;
										xmax = x;
										wmax = w;
										dmax = 0;
									}
									else if (ymax == y) {
										if (xmax >= x) {
											max_score = s;
											ymax = y;
											xmax = x;
											wmax = w;
											dmax = 0;
										}
									}
									
								}
							}

						}

						if (strlen(words[w]) + y < BOARD_SIZE) {
							spatiu = 0;
							int l = 1;
							for (int i = y + 1; i < strlen(words[w]) + y; i++) {
								if (table[i][x] == '.' || table[i][x] == words[w][l]) {
									spatiu++;
								}
								l++;
							}
							if (spatiu == strlen(words[w]) - 1) {
								int s = scor(words[w], y, x, 1, bonus1, bonus2);
								if (s > max_score) {
									max_score = s;
									ymax = y;
									xmax = x;
									wmax = w;
									dmax = 1;									
								}
								if (s == max_score) {
									if (ymax > y) {
										max_score = s;
										ymax = y;
										xmax = x;
										wmax = w;
										dmax = 1;
									}
									else if (ymax == y) {
										if (xmax > x) {
											max_score = s;
											ymax = y;
											xmax = x;
											wmax = w;
											dmax = 1;
										}
										else if (xmax == x) {
											if (dmax == 1) {
												max_score = s;
												ymax = y;
												xmax = x;
												wmax = w;
												dmax = 1;
											}
										}
									}

								}
							}
						}
					}
				}
			}
		}
		printf("%d %s\n", max_score, words[wmax]);
		
		if (dmax == 0) {
			int l = 1;
			for (int i = xmax + 1; i < strlen(words[wmax]) + xmax; i++) {
				table[ymax][i] = words[wmax][l];
				l++;
			}
		}

		else {
			if (dmax == 1) {
				int l = 1;
				for (int i = ymax + 1; i < ymax + strlen(words[wmax]); i++) {
					table[i][xmax] = words[wmax][l];
					l++;
				}
			}
		}

		
		scor2 += scor(words[wmax], ymax, xmax, dmax, bonus1, bonus2);
		vizite[wmax] = 1;
		n--;
	}
	print_board(table);
	if (scor1 > scor2) {
		printf("Player 1 Won!\n");
	}
	else {
		printf("Player 2 Won!\n");
	}
}

int main() {

	char table[BOARD_SIZE][BOARD_SIZE];

	char* input_val = (char*)malloc(MAX_LINE_SIZE);

	fgets(input_val, MAX_LINE_SIZE, stdin);
	
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			table[i][j] = '.';
		}
	}
	for (int i = 0; i < 26; i++) {
		char litera = i + 'A';
		if (litera == 'A' || litera == 'E' ||
			litera == 'I' || litera == 'L' ||
			litera == 'N' || litera == 'O' ||
			litera == 'R' || litera == 'S' ||
			litera == 'T' || litera == 'U')

			puncte[i] = 1;

		if (litera == 'D' || litera == 'G')
			puncte[i] = 2;

		if (litera == 'B' || litera == 'C' ||
			litera == 'M' || litera == 'P')
			puncte[i] = 3;

		if (litera == 'F' || litera == 'H' ||
			litera == 'V' || litera == 'W' ||
			litera == 'Y')
			puncte[i] = 4;

		if (litera == 'K')
			puncte[i] = 5;


		if (litera == 'J' || litera == 'X')
			puncte[i] = 8;


		if (litera == 'Q' || litera == 'Z')
			puncte[i] = 10;

	}
	
	if (input_val[0] == '0') {
		print_board(table);
	}

	if (input_val[0] == '1') {
		citire(table);
		print_board(table);
	}
	
	char** cuvinte;

	if (input_val[0] == '2') {

		int scor_p1 = 0; 
		int scor_p2 = 0;
		int N = get_words(&cuvinte);
		for (int i = 0; i < N; i++) {

			int scor_cuvant = 0;
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (cuvinte[i][j] == '\n') {
					break;
				}
				scor_cuvant += puncte[cuvinte[i][j] - 'A'];
			}
			if (i % 2 == 0) {
				scor_p1 += scor_cuvant;
			}
			else {
				scor_p2 += scor_cuvant;
			}
		}
		printf("Player 1: %d Points\n", scor_p1);
		printf("Player 2: %d Points\n", scor_p2);

	}

	if (input_val[0] == '3') {

		task_bonus();
		
	}
	if (input_val[0] == '4') {

		task_put_word(table);
		print_board(table);
	}

	if (input_val[0] == '5') {

		if (task5(table))
			print_board(table);
		else
			printf("Fail!\n");
	}

	if (input_val[0] == '6') {
		
		task6(table);
		print_board(table);
	}

	return 0;

}

