#include <iostream>
#include<fstream>
#include <iomanip>
#include <Windows.h>
using namespace std;
#define Grid 19
struct Board {
    char G[Grid][Grid];
    int Dimension;
    char PlayerSymbol[2] = { ' ', 'O' };
    char PlayerName[2][30] = { {},{"Computer"} };
    int turn, ri = Grid, ci = Grid, ConsecWinCounter,DifficultyLevel/*how much consecutive symbols to check to Win*/;
    bool gameOver = false;
    char WinName[30]; //Storing the Winner's Name to print when game ends.
};
struct Position {
    int ri, ci;
};
void Init(Board& B)
{
    //B.ConsecWinCounter = 5;
    fstream Rdr("Board.txt");
    Rdr >> B.Dimension;
    for (int ri = 0; ri < B.Dimension; ri++)
    {
        for (int ci = 0; ci < B.Dimension; ci++)
        {
            Rdr >> B.G[ri][ci];
        }
    }
    cout << endl << "Enter Player's Name: ";
    cin >> B.PlayerName[0];
    
    do {
        cout << "Enter your Symbol: ";
        cin >> B.PlayerSymbol[0];
        if (B.PlayerSymbol[0] != B.PlayerSymbol[1])
            break;
        else {
            cout << "The Symbols of both Computer and Player are same\nSo, enter your symbol again!" << endl;
            cout << "Computer's Symbol is ---> " << B.PlayerSymbol[1] << " <--- your symbol must be different than Computer's.\n";
            continue;
        }
    } while (true);
    cout << "\nEnter Win Counter: ";
    cin >> B.ConsecWinCounter;
    do{
        cout << "\nEnter the Difficulty Level from the following: \n";
        cout << "0 for Hard Difficulty Level: \n1 for Normal Difficulty Level: ";
        cin >> B.DifficultyLevel;
        if (B.DifficultyLevel != 0 && B.DifficultyLevel != 1)
            cout << "\nEnter the the difficulty level again: \n"<< endl;
        else
            break;
    } while (true);
     B.turn = rand() % 2;
}
void DisplayBoard(char b[][Grid], int dim)
{

    system("cls");
    int riDisplay = 1;
    int ciDisplay = 1;
    cout << "      ";
    for (int i = 0; i < dim; i++)
    {
        cout << setw(2) << ciDisplay << "  ";
        ciDisplay++;
    }
    cout << endl << endl;
    for (int ri = 0; ri < dim; ri++)
    {
        cout << left << setw(4) << riDisplay << "|";
        for (int ci = 0; ci < dim; ci++)
        {
            cout << right << setw(2) << b[ri][ci] << " |";
        }
        cout << endl << "    ";
        for (int i = 0; i < dim; i++)
        {
            cout << "----";
        }
        cout << endl;
        riDisplay++;
    }
}
void DisplayTurnMsg(char aikName[], char aikSym)
{
    cout << aikName << "'s Turn " << endl << "Symbol: " << aikSym << endl << "Sample Input--->[row's index, coloum's index]" << endl;

}
void SelectPosition(Position& p)
{
    int repeaterRef = 0;
    while (true) {
        if (repeaterRef > 0)
            cout << "Enter the Values Again, Values must be lesser than 19 (Grid)!\nSample Input--->[row's index, coloum's index]: " << endl;
        cin >> p.ri >> p.ci;
        p.ri--, p.ci--;
        if (p.ri > Grid || p.ci > Grid)
        {
            repeaterRef++;
        }
        else
            break;
    }
}
bool isValidPosition(Position p, int d, char b[][Grid])
{
    return((p.ri >= 0 && p.ci >= 0) && (p.ri < d&& p.ci < d)/* && (b[p.ri][p.ci] == '-')*/);
}
bool OverwriteError(Position p, char G[][Grid], Board B) {
    if ((G[p.ri][p.ci] == B.PlayerSymbol[0] || G[p.ri][p.ci] == B.PlayerSymbol[1]))
    {
        return true;
    }
    return false;
}
void UpdateBoard(char b[][Grid], Position p, char One_Sym)
{
    b[p.ri][p.ci] = One_Sym;

}
void TurnChange(int& turn)
{
    turn = (turn + 1) % 2;
}
bool H_Win_Checker(Board b, int ri, int ci)
{
    if ((ci + b.ConsecWinCounter) > b.Dimension)
    {
        return false;
    }
    for (int i = 0; i < b.ConsecWinCounter; i++)
    {
        if (b.G[ri][ci + i] != b.PlayerSymbol[b.turn])
        {
            return false;
        }
    }
    return true;
}
bool V_Win_Checker(Board b, int ri, int ci)
{
    if ((ri + b.ConsecWinCounter) > b.Dimension)
    {
        return false;
    }
    for (int i = 0; i < b.ConsecWinCounter; i++)
    {
        if (b.G[ri + i][ci] != b.PlayerSymbol[b.turn])
        {
            return false;
        }
    }
    return true;
}
bool LowerD_Win_Checker(Board b, int ri, int ci)
{
    if ((ri + b.ConsecWinCounter) > b.Dimension && (ci + b.ConsecWinCounter) > b.Dimension)
        return false;
    for (int i = 0; i < b.ConsecWinCounter; i++)
    {
        if (b.G[ri + i][ci + i] != b.PlayerSymbol[b.turn])
            return false;
    }
    return true;
}
bool UpperD_Win_Checker(Board b, int ri, int ci)
{
    if ((ri + b.ConsecWinCounter) > b.Dimension && (ci - b.ConsecWinCounter - 1) < 0)
        return false;
    for (int i = 0; i < b.ConsecWinCounter; i++)
    {
        if (b.G[ri + i][ci - i] != b.PlayerSymbol[b.turn])
            return false;
    }
    return true;
}
bool IsWin(Board b)
{
    for (int i = 0; i < b.Dimension; i++)
    {

        for (int j = 0; j < b.Dimension; j++)
        {
            //Checking if someone is winning from either side (Left, right, up, down, all Diagonal directions)
            if (H_Win_Checker(b, i, j) || V_Win_Checker(b, i, j) || LowerD_Win_Checker(b, i, j) || UpperD_Win_Checker(b, i, j))
                return true;
        }
    }
    return false;
}
bool IsDraw(Board b)
{
    for (int i = 0; i < b.Dimension; i++)
    {
        for (int j = 0; j < b.Dimension; j++)
        {
            if (b.G[i][j] == '-')
                return false;

            //Checking if there's is not '-' anymore on boards and no one has won yet than it's a draw 
        }
    }
    return true;
}
void ComputerMove(Board B, Position& P)
{
    for (int ri = 0; ri < B.Dimension; ri++)
    {
        for (int ci = 0; ci < B.Dimension; ci++)
        {
            P.ri = ri, P.ci = ci;
            if (isValidPosition(P, B.Dimension, B.G) && !OverwriteError(P, B.G, B))
            {
                B.G[ri][ci] = B.PlayerSymbol[1];
                if (IsWin(B))
                {
                    B.G[ri][ci] = '-';
                    return;
                }
                else {
                    B.G[ri][ci] = '-';
                }
            }
        }
    }
    for (int i = B.ConsecWinCounter; i > (B.ConsecWinCounter - i)+B.DifficultyLevel; i--)
    {
        B.ConsecWinCounter = i;
        for (int ri = 0; ri < B.Dimension; ri++)
        {
            for (int ci = 0; ci < B.Dimension; ci++)
            {
                P.ri = ri, P.ci = ci;
                if (isValidPosition(P, B.Dimension, B.G) && !OverwriteError(P, B.G, B))
                {
                    B.G[ri][ci] = B.PlayerSymbol[0];
                    B.turn = 0;
                    if (IsWin(B))
                    {
                        B.G[ri][ci] = '-';
                        return;
                    }
                    else {
                        B.G[ri][ci] = '-';
                    }
                }
            }
        }
    }
    do {
        P.ri = rand() % B.Dimension;
        P.ci = rand() % B.Dimension;
    } while (!isValidPosition(P, B.Dimension, B.G) && OverwriteError(P, B.G, B));
}
void Main() {

    Board B;
    Position pos;
    int ref = 1;
    char color[9] = "Color E0";
    int colorChanger = 0;
    int draw = -1;
    int counter = 0;
    Init(B);
    do {
        system(color);
        //   DisplayBoard(B.G, B.Dimension);
        //Changing Color of screen/ board
        if (colorChanger < 9)
            colorChanger++;
        if (colorChanger == 7 || colorChanger == 6)
            colorChanger++;
        if (colorChanger == 7)
            colorChanger++;
        if (colorChanger >= 9)
            colorChanger = 0;
        color[7] = (char)(48 + colorChanger);
        DisplayBoard(B.G, B.Dimension);
        DisplayTurnMsg(B.PlayerName[B.turn], B.PlayerSymbol[B.turn]);
        if (B.turn == 0)
        {
            do {
                SelectPosition(pos);
                system("cls");
                if (!isValidPosition(pos, B.Dimension, B.G) || OverwriteError(pos, B.G, B))
                {
                    DisplayBoard(B.G, B.Dimension);
                    cout << "Coordinates are not Right\nEnter the coordinates again: " << endl;
                    DisplayTurnMsg(B.PlayerName[B.turn], B.PlayerSymbol[B.turn]);
                    continue;
                }
                else {
                    break;
                }
            } while (true);
        }
        else if (B.turn == 1) {
            Sleep(800);
            ComputerMove(B, pos);
        }
        UpdateBoard(B.G, pos, B.PlayerSymbol[B.turn]);
        B.gameOver = IsWin(B);
        if (B.gameOver)
        {
            strcpy_s(B.WinName, B.PlayerName[B.turn]);
            DisplayBoard(B.G, B.Dimension);
        }
        if (IsDraw(B))
        {
            draw = 1;
            DisplayBoard(B.G, B.Dimension);
            B.gameOver = true;
        }
        if (!B.gameOver)
        {
            TurnChange(B.turn);
        }
    } while (!B.gameOver);
    if (draw == 1)
    {
        cout << "Game is Draw...";
    }
    else
    {
        cout << "\t\t----->>> " << B.WinName << " is The Winner!<<<-----" << endl;
        cout << "\t\t         Game End." << endl;
    }
}
int main()
{
    system("Color 04");
    cout << "\t\t\t ----------------------------\n";
    cout << "\t\t\t|                            |\n";
    cout << "\t\t\t| Welcome to THE GOMOKU GAME |\n";
    cout << "\t\t\t|                            |\n";
    cout << "\t\t\t ----------------------------\n\n";
    Main();
}