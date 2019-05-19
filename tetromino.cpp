#include "tetromino.h"

Tetromino::Tetromino(char block_type)
	:row(1), column(1)
{
	//initializes a 2d vector based on what block is specified
	//row and column refer to the spawn location of the top right square of the tetromino inside of the board
	if (block_type == 'O')
	{
		std::vector<std::vector<bool> > m_data(4, std::vector<bool>(4, false));
		data = m_data;
		data[1][1] = data[1][2] = data[2][1] = data[2][2] = true;
		row = -1;
		column = 3;
	}
	else if (block_type == 'I')
	{
		std::vector<std::vector<bool> > m_data(4, std::vector<bool>(4, false));
		data = m_data;
		data[1][0] = data[1][1] = data[1][2] = data[1][3] = true;
		row = 0;
		column = 3;
	}
	else if (block_type == 'J')
	{
		std::vector<std::vector<bool> > m_data(3, std::vector<bool>(3, false));
		data = m_data;
		data[0][0] = data[1][0] = data[1][1] = data[1][2] = true;
		row = 0;
		column = 3;
	}
	else if (block_type == 'S')
	{
		std::vector<std::vector<bool> > m_data(3, std::vector<bool>(3, false));
		data = m_data;
		data[0][1] = data[0][2] = data[1][0] = data[1][1] = true;
		row = 0;
		column = 3;
	}
	else if (block_type == 'T')
	{
		std::vector<std::vector<bool> > m_data(3, std::vector<bool>(3, false));
		data = m_data;
		data[0][1] = data[1][0] = data[1][1] = data[1][2] = true;
		row = 0;
		column = 3;
	}
	else if (block_type == 'Z')
	{
		std::vector<std::vector<bool> > m_data(3, std::vector<bool>(3, false));
		data = m_data;
		data[0][0] = data[0][1] = data[1][1] = data[1][2] = true;
		row = 0;
		column = 3;
	}
	else if (block_type = 'L')
	{
		std::vector<std::vector<bool> > m_data(3, std::vector<bool>(3, false));
		data = m_data;
		data[0][2] = data[1][0] = data[1][1] = data[1][2] = true;
		row = 0;
		column = 3;
	}
	else
	{
		std::cerr << "Error: No such block type" << std::endl;
	}
}

void Tetromino::rotateRight()
{	//rotates the tetromino block right by shifting around what values in data are true
	std::vector<std::vector<bool> > m_data(data.size(), std::vector<bool>(data.size(), false));
	int row, column;
	for (int i = 0; i < data.size(); ++i)
	{
		for (int j = 0; j < data[i].size(); ++j)
		{
			if (data[i][j])
			{
				row = i;
				column = j;
				rotateCoordinate(row, column, 'R');
				m_data[row][column] = true;
			}
		}
	}
	data = m_data;
}

void Tetromino::rotateLeft()
{	//rotates the tetromino block right by shifting around what values in data are true
	std::vector<std::vector<bool> > m_data(data.size(), std::vector<bool>(data.size(), false));
	int row, column;
	for (int i = 0; i < data.size(); ++i)
	{
		for (int j = 0; j < data[i].size(); ++j)
		{
			if (data[i][j])
			{
				row = i;
				column = j;
				rotateCoordinate(row, column, 'L');
				m_data[row][column] = true;
			}
		}
	}
	data = m_data;
}

void Tetromino::print() const
{	//prints the board in text(used for debugging)
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

void Tetromino::rotateCoordinate(int &row, int &column, char rotation) const
{	//changes row and column by rotating it into the nearby quadrant depending
	//on which direction rotation indicates
	indexToCart(row, column);
	int temp = column;
	if (rotation == 'R')
	{
		column = row;
		row = temp * -1;
	}
	else
	{
		column = row * -1;
		row = temp;
	}
	//change back to array indexes
	cartToIndex(row, column);
}

void Tetromino::indexToCart(int &row, int &column) const
{	//translate row and column to cartesian plane format with the center of the array as the orgin
	if (data.size() == 4)
	{	
		switch (row)
		{
		case 0:
			row = 2;
			break;
		case 1:
			row = 1;
			break;
		case 2:
			row = -1;
			break;
		case 3:
			row = -2;
			break;
		}
		switch (column)
		{
		case 0:
			column = -2;
			break;
		case 1:
			column = -1;
			break;
		case 2:
			column = 1;
			break;
		case 3:
			column = 2;
			break;
		}
	}
	if (data.size() == 3)
	{
		switch (row)
		{
		case 0:
			row = 1;
			break;
		case 1:
			row = 0;
			break;
		case 2:
			row = -1;
			break;
		}
		switch (column)
		{
		case 0:
			column = -1;
			break;
		case 1:
			column = 0;
			break;
		case 2:
			column = 1;
			break;
		}
	}
}

void Tetromino::cartToIndex(int &row, int &column)const
{	//translate row and column to index format with the center of the array as the orgin
	if (data.size() == 4)
	{	//translate row and column to cartesian plane format with the center of the array as the pivot
		switch (row)
		{
		case -2:
			row = 3;
			break;
		case -1:
			row = 2;
			break;
		case 1:
			row = 1;
			break;
		case 2:
			row = 0;
			break;
		}
		switch (column)
		{
		case -2:
			column = 0;
			break;
		case -1:
			column = 1;
			break;
		case 1:
			column = 2;
			break;
		case 2:
			column = 3;
			break;
		}
	}
	if (data.size() == 3)
	{
		switch (row)
		{
		case -1:
			row = 0;
			break;
		case 0:
			row = 1;
			break;
		case 1:
			row = 2;
			break;
		}
		switch (column)
		{
		case -1:
			column = 2;
			break;
		case 0:
			column = 1;
			break;
		case 1:
			column = 0;
			break;
		}
	}
}