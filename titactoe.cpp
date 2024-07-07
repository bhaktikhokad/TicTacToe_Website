#include <bits/stdc++.h>
using namespace std;
#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

bool columncross(char gboard[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (gboard[0][i] == gboard[1][i] &&
            gboard[1][i] == gboard[2][i] &&
            gboard[0][i] != '*') {
            return true;
        }
    }
    return false;
}

bool rowcrossed(char gboard[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (gboard[i][0] == gboard[i][1] &&
            gboard[i][1] == gboard[i][2] &&
            gboard[i][0] != '*') {
            return true;
        }
    }
    return false;
}

bool diagonalcross(char gboard[][SIDE]) {
    if ((gboard[0][0] == gboard[1][1] &&
         gboard[1][1] == gboard[2][2] &&
         gboard[0][0] != '*') ||
        (gboard[0][2] == gboard[1][1] &&
         gboard[1][1] == gboard[2][0] &&
         gboard[0][2] != '*')) {
        return true;
    }
    return false;
}

void showboard(char gboard[][SIDE]) {
    cout << gboard[0][0] << "|" << gboard[0][1] << "|" << gboard[0][2] << endl;
    cout << "-----" << endl;
    cout << gboard[1][0] << "|" << gboard[1][1] << "|" << gboard[1][2] << endl;
    cout << "-----" << endl;
    cout << gboard[2][0] << "|" << gboard[2][1] << "|" << gboard[2][2] << endl;
}

bool gameOver(char gboard[][SIDE]) {
    return rowcrossed(gboard) || columncross(gboard) || diagonalcross(gboard);
}

void show() {
    cout << "1|2|3" << endl;
    cout << "-----" << endl;
    cout << "4|5|6" << endl;
    cout << "-----" << endl;
    cout << "7|8|9" << endl;
}

int minimax(char gboard[][SIDE], int depth, bool isPlay) {
    int score = 0, bestscore = 0;
    if (gameOver(gboard)) {
        if (isPlay) return -10;
        else return +10;
    } else {
        if (depth < 9) {
            if (isPlay) {
                bestscore = -999;
                for (int i = 0; i < SIDE; i++) {
                    for (int j = 0; j < SIDE; j++) {
                        if (gboard[i][j] == '*') {
                            gboard[i][j] = COMPUTERMOVE;
                            score = minimax(gboard, depth + 1, false);
                            gboard[i][j] = '*';
                            if (bestscore < score) bestscore = score;
                        }
                    }
                }
                return bestscore;
            } else {
                bestscore = 999;
                for (int i = 0; i < SIDE; i++) {
                    for (int j = 0; j < SIDE; j++) {
                        if (gboard[i][j] == '*') {
                            gboard[i][j] = HUMANMOVE;
                            score = minimax(gboard, depth + 1, true);
                            gboard[i][j] = '*';
                            if (bestscore > score) bestscore = score;
                        }
                    }
                }
                return bestscore;
            }
        }
    }
    return 0;
}

void initialize(char gboard[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            gboard[i][j] = '*';
        }
    }
}

int bestWay(char gboard[][SIDE], int maxIn) {
    int x = -1, y = -1;
    int score = 0, bestscore = -999;
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (gboard[i][j] == '*') {
                gboard[i][j] = COMPUTERMOVE;
                score = minimax(gboard, maxIn + 1, false);
                gboard[i][j] = '*';
                if (bestscore < score) bestscore = score, x = i, y = j;
            }
        }
    }
    return x * 3 + y;
}

void declareWinner(int whoseTurn) {
    if (whoseTurn == COMPUTER)
        cout << "COMPUTER has won";
    else
        cout << "HUMAN has won";
}

void playTurn(int whoseTurn) {
    char gboard[SIDE][SIDE];
    int maxIn = 0, x = 0, y = 0;

    initialize(gboard);
    show();
    cout << endl;

    while (!gameOver(gboard) && maxIn != SIDE * SIDE) {
        int n;
        if (whoseTurn == COMPUTER) {
            n = bestWay(gboard, maxIn);
            x = n / SIDE;
            y = n % SIDE;
            gboard[x][y] = COMPUTERMOVE;
            showboard(gboard);
            maxIn++;
            whoseTurn = HUMAN;
        } else if (whoseTurn == HUMAN) {
            cout << "Enter your move: ";
            cin >> n;
            n--;
            x = n / SIDE;
            y = n % SIDE;
            if (gboard[x][y] == '*' && n < 9 && n >= 0) {
                gboard[x][y] = HUMANMOVE;
                showboard(gboard);
                maxIn++;
                whoseTurn = COMPUTER;
            } else if (n >= 9 || n < 0)
                cout << "Invalid input" << endl;
            else
                cout << "Already occupied" << endl;
        }
    }
    if (!gameOver(gboard) && maxIn == SIDE * SIDE)
        cout << "It's a draw";
    else {
        if (whoseTurn == COMPUTER)
            whoseTurn = HUMAN;
        else if (whoseTurn == HUMAN)
            whoseTurn = COMPUTER;
        declareWinner(whoseTurn);
    }
}

int main() {
    char cont = 'y';
    cout << "Do you want to play first? (y/n): ";
    do {
        char choice;
        cin >> choice;
        if (choice == 'y') {
            playTurn(HUMAN);
        } else if (choice == 'n') {
            playTurn(COMPUTER);
        } else {
            cout << "Invalid input";
        }
        cout << "\nEnter 'n' to exit, any other key to play again: ";
        cin >> cont;
    } while (cont != 'n');

    return 0;
}
