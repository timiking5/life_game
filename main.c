#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <locale.h>

#define Y 25
#define X 80

int check_neighbours(char field[][X], int x, int y);
int algorithm(char field1[][X], char field2[][X]);
void output(char field[][X]);
void clear(char field[][X]);


int main() {
    char field1[Y][X];
    char field2[Y][X];
    setlocale(LC_ALL, "Rus");
    int GAME_SPEED;
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            field1[i][j] = ' ';
        }
    }
    field1[12][12] = '1';
    field1[13][13] = '1';
    field1[14][12] = '1';
    field1[14][11] = '1';
    field1[14][13] = '1';
    field1[9][60] = '1';
    field1[9][61] = '1';
    field1[8][61] = '1';
    field1[8][60] = '1';
    int fl = 1;
    int reps = 0;
    printf("¬ведите скорость игры в милисекундах: ");
    char temp;
    if (!scanf("%d%c", &GAME_SPEED, &temp) || (temp != '\n')) {
        printf("n/a");
        exit(1);
    } else if (GAME_SPEED < 0) {
        printf("n/a");
        exit(1);
    }
    GAME_SPEED *= 1000;
    printf("\n");
    while (fl) {
        printf("\n");
        if (reps%2 == 0) {
            fl = algorithm(field1, field2);
            output(field1);
            reps++;
        } else {
            fl = algorithm(field2, field1);
            output(field2);
            reps--;
        }
        printf("\n");
        usleep(GAME_SPEED);
    }
    return 0;
}


int check_neighbours(char (*field)[X], int p_x, int p_y) {
    int neighbours = 0;
    int y_axis[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int x_axis[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; i++) {
        int x = p_x + x_axis[i], y = p_y + y_axis[i];
        if (y < 0) y = Y - 1;
        if (y > 24) y = 0;
        if (x < 0) x = X - 1;
        if (x > 79) x = 0;
        if (field[y][x] == '1') neighbours++;
    }
    return neighbours;
}


int algorithm(char field1[][X], char field2[][X]) {
    int alive = 0;
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            int nb = check_neighbours(field1, j, i);
            if ((field1[i][j] == ' ') && (nb == 3)) {
                field2[i][j] = '1';
                alive++;
            } else if ((field1[i][j] == '1') && (nb < 2)) {
                field2[i][j] = ' ';
                alive--;
            } else if ((field1[i][j] == '1') && (nb >= 2) && (nb <=3)) {
                field2[i][j] = '1';
                alive++;
            } else {
                field2[i][j] = ' ';
            }
        }
    }
    if (alive > 0) return 1;
    return 0;
}


void output(char field[][X]) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            printf("%c", field[i][j]);
        }
        if (i != Y - 1) printf("\n");
    }
}
