#include "board.h"
#include <cassert>
Board::Board(int a_rows, int a_columns)
:window("Tetris", 800, 600)
{
	std::vector<std::vector<bool> > m_data(a_rows, std::vector<bool>(a_columns, false));
	std::vector<int> m_rowCount(a_rows, 0);
	data = m_data;
	rowCount = m_rowCount;
	rows = a_rows;
	columns = a_columns;
	window.clear();
	window.drawGrid();
}

void Board::insertPiece(Tetromino &piece)
{
	//row column starts from the top left of the Tetromino
	//assumes all inserted blocks can't go down any further
	
	int row = piece.row;
	int column = piece.column;
	int startColumn = column;
	//error checks to make sure the piece is placed in a legal spot
	for (int i = 0; i < (piece.data).size(); ++i)
	{
		column = startColumn;
		for (int j = 0; j < (piece.data).size(); ++j)
		{
			//makes sure that the out of range pieces have nothing in them/are false
			if (row < 0 || row >= rows || column<0 || column > columns) assert(!piece.data[i][j]);
			else
			{
				//makes sure the place where a block is about to be placed has nothing in it
				if (piece.data[i][j])
				{
					if (data[row][column])
					{	//throws an error if the block is being inserted on another one
						throw - 1;
					}
					//changes coresponing spot in the board to true
					data[row][column] = true;
					++rowCount[row];
				}
			}
			++column;
		}
		++row;
	}
	piece.placed = true;
	draw(&piece);
	clearFreeRows();
}

void Board::print() const
{	//prints the board in text format, used for debugging
	std::cout << data.size() << std::endl;
	for (int i = 0; i < data.size(); ++i)
	{
		for (int j = 0; j < data[i].size(); ++j)
		{
			if (data[i][j] == false) std::cout << ".";
			else std::cout << "X";
		}
		std::cout << std::endl;
	}
}

void Board::clearFreeRows()
{	//checks for any free rows and deletes them then shifts the other rows down
	//TODO: make more efficient for multiple row clears
	for (int i = 0; i < rowCount.size();++i)
	{	//if a row is completley filled clear it and shift every vector above down 1
		if (rowCount[i] == columns)
		{
			rowCount[i] = 0;
			for (int j= i;j!=0;--j)
			{
				copyRow(j, j-1);
				data[j] = data[j-1];
				rowCount[j] = rowCount[j - 1];
			}
			data[0] = std::vector<bool>(columns, false);
			eraseRow(0);
		}
	}
}

void Board::draw(Tetromino *piece)
{	//draws the tetris piece on the window based on its location
	int row = piece->row;
	int column = piece->column;
	for (int i = 0; i < (piece->data).size(); ++i)
	{
		column = piece->column;
		for (int j = 0; j < (piece->data[i]).size(); ++j)
		{
			if (piece->data[i][j])
			{
				//makes sure the piece is not out of range of the board
				assert(0 <= row < rows && 0<= column <columns);
				window.drawSquare(column, row,200,0,200);
			}
			column++;
		}
		row++;
	}
	window.update();
}

void Board::erase(Tetromino *piece) const
{	//erases the given piece from the board
	int row = piece->row;
	int column = piece->column;
	for (int i = 0; i < (piece->data).size(); ++i)
	{
		column = piece->column;
		for (int j = 0; j < (piece->data[i]).size(); ++j)
		{
			if (piece->data[i][j])
			{
				//makes sure tie piece is not out of range
				assert(0 <= row < rows && 0 <= column < columns);
				window.drawSquare(column, row,0,0,0);
			}
			column++;
		}
		row++;
	}
}

void Board::move(Tetromino *piece, char direction)
{	//moves the piece in the specified direction if able to
	erase(piece);
	int row = piece->row;
	int column = piece->column;
	if (direction == 'D')
	{
		//checks if at the bottom of the board or about to collide with another piece
		for (int i = 0; i < (piece->data).size(); ++i)
		{
			column = piece->column;
			for (int j = 0; j < (piece->data[i]).size(); ++j)
			{
				if (piece->data[i][j] && (row == 19 ||data[row+1][column] ))
				{
					std::cout << "inserted" << std::endl;
					insertPiece(*piece);
					return;
				}
				column++;
			}
			row++;
		}
		piece->row++;
	}
	else if (direction == 'R')
	{
		for (int i = 0; i < (piece->data).size(); ++i)
		{
			column = piece->column;
			for (int j = 0; j < (piece->data[i]).size(); ++j)
			{
				if (piece->data[i][j] && (column == 9 || data[row][column+1]))
				{
					return;
				}
				column++;
			}
			row++;
		}
		piece->column++;
	}
	else if (direction == 'L')
	{
		for (int i = 0; i < (piece->data).size(); ++i)
		{
			column = piece->column;
			for (int j = 0; j < (piece->data[i]).size(); ++j)
			{
				if (piece->data[i][j] && (column == 0 || data[row][column - 1]))
				{
					return;
				}
				column++;
			}
			row++;
		}
		piece->column--;
	}
}

void Board::pollEvents(Tetromino *piece)
{	//check for the key events from the window and either rotates, moves the piece or does nothing
	//based on the event
	char direction = 'N';
	char rotation = 'N';
	window.pollEvents(direction, rotation);
	if (direction != 'N')
	{
		move(piece, direction);
	}
	if (rotation != 'N')
	{
		rotate(piece, rotation);
	}
}

void Board::eraseRow(int row) const
{	//erases an entire row from the window
	for (int i = 0; i < data[row].size(); ++i)
	{
		window.drawSquare(i, row, 0, 0, 0);
	}
}

void Board::copyRow(int row1, int row2) const
{	//copies row1 and draws it onto row2 on the window
	eraseRow(row1);
	for (int i = 0; i < data[row2].size(); ++i)
	{
		if (data[row2][i])
		{
			window.drawSquare(i, row1, 200, 0, 200);
		}
	}
}

void Board::rotate(Tetromino *piece, char rotation) const
{	//Checks to see if when the pice is rotated it doesn't collide with other pieces then rotates it
	//make more efficient if it slows down the game
	erase(piece);
	int row = piece->row;
	int column = piece->column;
	if (rotation == 'R')
	{
		piece->rotateRight();
	}
	else if (rotation == 'L')
	{
		piece->rotateLeft();
	}
	for (int i = 0; i < (piece->data).size(); ++i)
	{
		column = piece->column;
		for (int j = 0; j < (piece->data[i]).size(); ++j)
		{
			if (piece->data[i][j] && (!(0<=column && column <columns) || !(0 <= row && row < rows) ||data[row][column]))
			{
				switch (rotation)
				{
					case 'R':
						piece->rotateLeft();
						return;
					case 'L':
						piece->rotateRight();
						return;
				}
			}
			column++;
		}
		row++;
	}
}