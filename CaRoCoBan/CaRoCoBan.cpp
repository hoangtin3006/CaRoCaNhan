// CaRoCoBan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

/*
void inDong(int size) {
    for (int i = 0; i < size; i++) {
        cout << "-";
    }
    cout << endl;
}

void inCot(int size) {
    for (int i = 0; i < size; i++) {
        cout << "|";
    }
    cout << endl;
}*/
void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// An con tro console mac dinh
void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE; // An tro
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Hien con tro console mac dinh
void showCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = TRUE; // Hien tro
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Ham doi mau chu
void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int banCo[12][12] = {0};
int toadoX = 0;
int toadoY = 0;
int luotChoi = 1;


void veBanCo() {
   int startX = 2;
   int startY = 3;
    for (int i = 0; i < 12; i++) {
        gotoXY(startX, startY + i * 2);

        cout << "+";

        for (int j = 0; j < 12; j++) {
            cout << "---+";
        }

        gotoXY(startX, startY + i * 2 + 1);

        cout << "|";
        for (int j = 0; j < 12; j++) {
            cout << "   |";
        }
    }
    gotoXY(startX, 27);
    cout << "+";
    for (int j = 0; j < 12; j++) {
        cout << "---+";
    }
    gotoXY(0, 0);
}

void Ve_XO(int y, int x ) {
    int consoleX = 2 + x * 4 + 1;
    int consoleY = 3 + y * 2 + 1;

    gotoXY(consoleX, consoleY);

    char conNhay = ' ';
    if (banCo[y][x] == 1) {
            conNhay = 'X';
        }
    
    else if (banCo[y][x] == 2) {
            conNhay = 'O';
        }
        if (y == toadoY && x == toadoX) {
            setTextColor(14);
            cout << "[" << conNhay << "]";
            setTextColor(7);
        }
        else cout << " " << conNhay << " ";
    }

void Xoa_Nhay_Cu(int y, int x) {
    int consoleX = 2 + x * 4 + 1;
    int consoleY = 3 + y * 2 + 1;

    gotoXY(consoleX, consoleY);

    char conNhay = ' ';
    if (banCo[y][x] == 1) {
        conNhay = 'X';
    }
    else if (banCo[y][x] == 2) {
        conNhay = 'O';
    }
    setTextColor(7); 
    cout << " " << conNhay << " "; 
}

bool check_win_hang_ngang(int toadoY, int toadoX) {
    luotChoi = banCo[toadoY][toadoX];
    int count = 1;
    for (int i = toadoX + 1; i < 12; i++) {
        if (banCo[toadoY][i] == luotChoi) {
            count++;
        }
        else break;
    }

    for (int i = toadoX - 1; i >= 0; i--) {
        if (banCo[toadoY][i] == luotChoi) {
            count++;
        }
        else break;
    }
    return count >= 5;
}

bool check_win_hang_doc(int toadoY, int toadoX) {
    int count = 1;
    luotChoi = banCo[toadoY][toadoX];
    for (int i = toadoY + 1; i < 12; i++) {
        if (banCo[i][toadoX] == luotChoi) count++;
        else break;
    }

    for (int i = toadoY - 1; i >= 0; i--) {
        if (banCo[i][toadoX] == luotChoi) count++;
        else break;
    }
    return count >= 5;
}

bool check_win_hang_cheo_chinh(int toadoY, int toadoX) {
    luotChoi = banCo[toadoY][toadoX];
    int count = 1;
    for (int i = toadoY + 1, j = toadoX + 1; i < 12 && j < 12; i++, j++) {
        if (banCo[i][j] == luotChoi) count++;
        else break;
    }

    for (int i = toadoY - 1, j = toadoX - 1; i >= 0 && j >= 0; i--, j--) {
        if (banCo[i][j] == luotChoi) count++;
        else break;
    }
    return count >= 5;
}

bool check_win_hang_cheo_phu(int toadoY, int toadoX) {
    luotChoi = banCo[toadoY][toadoX];
    int count = 1;
    for (int i = toadoY + 1, j = toadoX - 1; i < 12 && j >= 0; i++, j--) {
        if (banCo[i][j] == luotChoi) count++;
        else break;
    }
    for (int i = toadoY - 1, j = toadoX + 1; i >= 0 && j < 12; i--, j++) {
        if (banCo[i][j] == luotChoi) count++;
        else break;
    }
    return count >= 5;
}

int main()
{
        hideCursor();
        setTextColor(4);

        veBanCo();

        gotoXY(0, 0);

        cout << "Luot cua nguoi choi: " << (luotChoi == 1 ? "X" : "O") << "      ";

        Ve_XO(toadoY,toadoX);

        //cout << endl; // de xuat du lieu 

        while (true) {
            int toadoX_cu = toadoX;
            int toadoY_cu = toadoY;

            char thaoTac = _getch();

            if (thaoTac == 'w' && toadoY > 0) {
                toadoY--;
            }
            else if (thaoTac == 's' && toadoY < 11) {
                toadoY++;
            }
            else if (thaoTac == 'a' && toadoX > 0) {
                toadoX--;
            }
            else if (thaoTac == 'd' && toadoX < 11) {
                toadoX++;
            }
            else if (thaoTac == 13) {
                if (banCo[toadoY][toadoX] == 0) {
                    banCo[toadoY][toadoX] = luotChoi;
                    Xoa_Nhay_Cu(toadoY, toadoX);
                    Ve_XO(toadoY, toadoX);
                    if (check_win_hang_ngang(toadoY, toadoX) == true) {
                        gotoXY(0, 2); 
                        setTextColor(13); 
                        cout << "Player " << (banCo[toadoY][toadoX] == 1 ? "X" : "O") << " WINS!" << endl;

                        _getch(); 
                       
                        return 0;
                    }
                    else if (check_win_hang_doc(toadoY, toadoX) == true) {
                        gotoXY(0, 2);
                        setTextColor(13);
                        cout << "Player " << (banCo[toadoY][toadoX] == 1 ? "X" : "O") << " WINS!" << endl;

                        _getch();

                        return 0;
                    }
                    else if (check_win_hang_cheo_chinh(toadoY, toadoX) == true) {
                        gotoXY(0, 2);
                        setTextColor(13);
                        cout << "Player " << (banCo[toadoY][toadoX] == 1 ? "X" : "O") << " WINS!" << endl;

                        _getch();

                        return 0;
                    }
                    else if (check_win_hang_cheo_phu(toadoY, toadoX) == true) {
                        gotoXY(0, 2);
                        setTextColor(13);
                        cout << "Player " << (banCo[toadoY][toadoX] == 1 ? "X" : "O") << " WINS!" << endl;

                        _getch();

                        return 0;
                    }
                    

                    if (luotChoi == 1) {
                        luotChoi = 2;
                    }
                    else {
                        luotChoi = 1;
                    }
                    gotoXY(0, 0);
                    cout << "Luot cua nguoi choi: " << (luotChoi == 1 ? "X" : "O") << "      ";
                }
            }

            if (toadoX != toadoX_cu || toadoY != toadoY_cu) {
                Xoa_Nhay_Cu(toadoY_cu, toadoX_cu);
                Ve_XO(toadoY, toadoX);
            }
        }

      
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
