/*
Author: Yaw Amoa-Asare

A simple version of tetris that uses SDL2 to help with the graphical interface
*/
#include <iostream>
#include <string>
#include <time.h>
#include "tetromino.h"
#include "board.h"

int main(int argc, char **argv)
{
	const char tetrominoChoices[7] = { 'O','I','J','S','T','Z','L' };
	srand(time(NULL));
	int randIndex = rand() % 7;
	//initializes a random tetris piece
	Tetromino *currentPiece = new Tetromino(tetrominoChoices[randIndex]);
	Board tetrisBoard(20,10);
	clock_t start = clock();
	double duration;
	bool gameOver = false;
	//runs while the tetris window is still open
	while (tetrisBoard.open())
	{
		while (!gameOver && tetrisBoard.open())
		{
			try
			{
				duration = (clock() - start) / (double)CLOCKS_PER_SEC;
				tetrisBoard.pollEvents(currentPiece);
				if (duration > .5)
				{	//moves the tetris piece down after a certain amount of time has passed
					tetrisBoard.move(currentPiece, 'D');
					start = clock();
				}

				if (currentPiece->isPlaced())
				{	//if the piece was placed in the board it is deleted and current piece
					//will now point to a new random piece
					delete currentPiece;
					randIndex = rand() % 7;
					currentPiece = new Tetromino(tetrominoChoices[randIndex]);
				}
				else
				{
					tetrisBoard.draw(currentPiece);
				}
			}
			catch (int)
			{	//ends the game if an int is thrown
				gameOver = true;
			}
		}
		std::cout << "game over" << std::endl;
		break;
	}
	return 1;
}