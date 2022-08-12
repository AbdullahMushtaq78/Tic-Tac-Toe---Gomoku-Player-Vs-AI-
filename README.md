# Tic-Tac-Toe---Gomoku-Player-Vs-AI-
Extended version of Tic Tac Toe which is also called as Gomoku. Player vs Ai version.
## Main Features:
- Name of Player
- Symbol of Player
- Win Counter
- Difficulty Mode
- Win / Draw
- Board with Different colors
- All Rules Check implemented
## Main Memory Structure:
- Struct Board
```
#define Grid 19
struct Board {
    char G[Grid][Grid];
    int Dimension;
    char PlayerSymbol[2] = { ' ', 'O' };
    char PlayerName[2][30] = { {},{"Computer"} };
    int turn, ri = Grid, ci = Grid, ConsecWinCounter,DifficultyLevel;
    bool gameOver = false;
    char WinnerName[30];
};
```
- Struct Pos
```
struct Position {
    int ri, ci;
};
```
- The initialization of baord is from the Board.txt file where the dimmensions and entire structure of board is saved already. The Dimmension of board is set to 19 by default because Gomoku has grid of 19 x 19 as compare to 9 x 9 board of tic tac toe. <br />
- Players can set their Name and their custom Symbol used to display their mark on board. <br />
- Symbol of AI is set to 'O' be default.<br />
- Win counter is the number of marking consecutive required for player to win. If it is set to 3 then game can be played as Tic Tac Toe but in Gomoku it is higher than 3.<br />
- After every turn there's a display message shows whose player turn it is right now. <br />
- Draw / Win functionality is also implemented. <br />
- Difficulty modes are also implemented. At the start of each game, you will be asked to set the difficulty of the game. Normal will let the player to win easily but in hard mode AI will try his best to block the every move of player to stop it from winning. <br />
- Color of Console and Boards will keep changing after specific number of moves. <br />
- There are multiple utility functions to implement multiple checks and rules of game to adopt the original vibe of Gomoku. <br />
###### You Can use this code in any of your projects. <br />
###### **Thanks.**
