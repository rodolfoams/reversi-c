# reversi-c

This project implements the game of Reversi using the C programming language.

## Compiling the code

Run `gcc reversi.c -o reversi`.

## Running the game

Run `./reversi`.

## Game Tutorial

The game can be played by two human players or by one human player against the machine.
The current player is shown in the bottom of the screen.
The valid plays are shown in the board by an asterisk ('*') mark.
The player should input the position of the next play indicating, respectively, the column and row to place the next piece (e.g.: "C4").
The game ends when there are no moves left for both players or when the board is completely filled.

## Roadmap

1. Create a board (DONE)
2. Create piece markers (DONE)
3. Define turn (DONE)
4. Mark valid move positions (DONE)
5. Display board (DONE)
6. Display current player (DONE)
7. Prompt next move (DONE)
8. Make move (DONE)
9. Change captured pieces (DONE)
9. End game (DONE)
10. Use ncurses to better control the screen
11. Pretify