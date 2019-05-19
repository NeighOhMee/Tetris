/*
Contains the data for a tetromino piece(a 4 block piece)
*/
#pragma once
#ifndef __tetromino_h_
#define __tetromino_h_

#include <vector>
#include<iostream>
class Tetromino
{
	public:
		Tetromino(char block_type);
		void rotateRight();
		void rotateLeft();
		void print() const;
		inline bool isPlaced() const { return placed; }
		friend class Board;
	private:
		std::vector<std::vector<bool> > data;
		int row, column;
		bool placed = false;
		void rotateCoordinate(int &row, int &column, char rotation) const;
		void indexToCart(int &row, int &column) const;
		void cartToIndex(int &row, int &column) const;
};

#endif