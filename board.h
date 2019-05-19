/*
contains all the data for a tetris board, handles displaying to a window by using a Window object
*/
#pragma once

#ifndef __board_h_
#define __board_h_
#include "tetromino.h"
#include "window.h"
class Board
{
	public:
		Board(int a_rows, int a_columns);
		void insertPiece(Tetromino &piece);
		void print() const;
		bool open() const { return !window.isClosed();}
		void pollEvents(Tetromino *piece); 
		void draw(Tetromino *piece);
		void erase(Tetromino *piece) const;
		void move(Tetromino *piece, char direction);
		void copyRow(int row1, int row2) const;
		void eraseRow(int row) const;
		void rotate(Tetromino *piece, char direction) const;
	private:
		void clearFreeRows();
	private:
		std::vector<std::vector<bool> > data;
		int rows, columns;
		std::vector<int> rowCount;
		Window window;
};
#endif 
