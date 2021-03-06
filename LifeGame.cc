// LifeGame by Maria Montalvo and Victor Pla, 04/06/2020

#pragma region Libraries
#include "Cell.hh"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <unistd.h>
using namespace std;
#pragma endregion

#pragma region Global variables
// Global variables:
const int X = 10, Y = 10;
const int ITERATIONS = 5;
const char FILL = '+', BLANK = '-';

typedef vector<Cell> Row;
typedef vector<Row> Mesh;
Mesh mesh(Y, Row(X, BLANK));
#pragma endregion

#pragma region Functions
// Functions:
void initialize_cell();
void create_life();
void run_time();
void reload_frame(const int frame);
void conditions(const int x, const int y);
void condition1(const int x, const int y);
void condition2(const int x, const int y);
void condition3(const int x, const int y);
bool inside_mesh(const int x, const int y);
void reset();
#pragma endregion

#pragma region Conditions
// Conditions:
    // 1. An alone cell dies
    // 2. From - to |
    // 3. From a X to a �
#pragma endregion

//-----------------------------------------------------------------------//

int main() {

    system("clear");

    cout << endl << "Welcome to LifeGame by Maria Montalvo and Victor Pla! \n\nInput to start...";

    while (cin.ignore()) {

        initialize_cell();
        create_life();
        cout << endl << "Input to start..." << endl;
        reset();

    }

}

bool inside_mesh(const int x, const int y) {
    return (x >= 0 and x < X) and (y >= 0 and y < Y);
}

void conditions(const int x, const int y) {
    // Condition 1:
    condition1(x, y);
    // Condition 2:
    condition2(x, y);
    // Condition 3:
    condition3(x, y);

}

void condition1(const int x, const int y) {
    bool condition1 = 1;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int k = y - 1; k <= y + 1; k++) {
            if (x == i and y == k) continue;
            else if (inside_mesh(i, k)) {
                if (condition1) condition1 = (mesh[i][k] == BLANK);
            }
        }
    }
    if (condition1) {
        mesh[x][y] = BLANK;
    }
}

void condition2(const int x, const int y) {
    bool condition2A = inside_mesh(x - 1, y) and inside_mesh(x + 1, y) and (mesh[x - 1][y] == FILL and mesh[x + 1][y] == FILL);  //vertical
    bool condition2B = inside_mesh(x, y - 1) and inside_mesh(x, y + 1) and (mesh[x][y - 1] == FILL and mesh[x][y + 1] == FILL);  //horitzontal
    if (condition2A and not condition2B) {
        if (inside_mesh(x, y - 1)) {
            mesh[x][y - 1] = FILL;
        }
        if (inside_mesh(x, y + 1)) {
            mesh[x][y + 1] = FILL;
        }
        mesh[x - 1][y] = BLANK;
        mesh[x + 1][y] = BLANK;
    }
    if (condition2B and not condition2A) {
        if (inside_mesh(x - 1, y)) {
            mesh[x - 1][y] = FILL;
        }
        if (inside_mesh(x + 1, y)) {
            mesh[x + 1][y] = FILL;
        }
        mesh[x][y - 1] = BLANK;
        mesh[x][y + 1] = BLANK;
    }
}

void condition3(const int x, const int y) {
    if (inside_mesh(x - 1, y - 1) and inside_mesh(x + 1, y + 1)) {
        bool diag = true;
        bool vert = true;
        int i = x - 1;
        int k = y - 1;

        /*while (i<=x+1 and (diag or vert)) {
            k=y-1;
            while (k<=y+1 and (diag or vert)) {
                //diagonal corners
                if ((i-k)%2==0) {
                    diag=mesh[i][k]==FILL;
                }
                //central cross
                else {
                    vert=mesh[i][k]==FILL;
                }
                if (i!=x-1 and k!=y-1 and diag and vert) {
                    diag=0;
                    vert=0;
                }
                ++k;
            }
            ++i;
        } */

        while (i <= x + 1 and diag) {
            k = y - 1;
            while (k <= y + 1 and diag) {
                //X
                if ((i - k) % 2 == 0) {
                    diag = mesh[i][k] == FILL;
                }
                ++k;
            }
            ++i;
        }

        i = x - 1;
        while (i <= x + 1 and vert) {
            k = y - 1;
            while (k <= y + 1 and vert) {
                //�
                if ((i - k) % 2 != 0) {
                    vert = mesh[i][k] == FILL;
                }
                ++k;
            }
            ++i;
        }

        if (diag and vert) {
            diag = 0;
            vert = 0;
        }

        if (diag) {
            for (i = x - 1; i <= x + 1; ++i) {
                for (k = y - 1; k <= y + 1; ++k) {
                    if (x == i and y == k) continue;
                    if ((i - k) % 2 == 0) mesh[i][k] = BLANK;
                    else mesh[i][k] = FILL;
                }

            }
        }

        if (vert) {
            for (i = x - 1; i <= x + 1; ++i) {
                for (k = y - 1; k <= y + 1; ++k) {
                    if (x == i and y == k) continue;
                    if ((i - k) % 2 == 0) mesh[i][k] = FILL;
                    else mesh[i][k] = BLANK;
                }

            }

        }

    }

}

void run_time() {
    for (int i = 0; i < X; i++) {
        for (int k = 0; k < Y; k++) {
            if (mesh[i][k] == FILL) conditions(i, k);
        }
    }
}

void create_life() {

    for (int i = 0; i < ITERATIONS; i++) {
        sleep(1);
        reload_frame(abs(ITERATIONS - i));
        run_time();
    }
    reload_frame(0);

}

void reset() {
    Mesh aux(Y, Row(X, BLANK));
    mesh = aux;
}

void reload_frame(const int frame) {
    system("clear");
    cout << "Time: " << frame << endl;
    for (int i = 0; i < X; i++) {
        for (int k = 0; k < Y; k++) {
            cout << mesh[i][k].value();
        }
        cout << endl;
    }
}

void initialize_cell() {

    system("clear");
    cout << endl << "# Initialize first cells:" << endl;

    int x, y;
    cin >> x >> y;
    while (x != -1 and y != -1) {
        mesh[x][y] = Cell(FILL);
        cin >> x >> y;
    }

}

//-----------------------------------------------------------------------//