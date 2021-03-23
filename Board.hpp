#ifndef UNTITLED_BOARD_HPP
#define UNTITLED_BOARD_HPP

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "Direction.hpp"

namespace ariel
{

constexpr unsigned DEFAULT_ROW_SIZE = 1;
constexpr unsigned DEFAULT_COL_SIZE = 1;

class Board
{
	using Columns =  std::vector<char>;
	using Location = std::pair<unsigned int, unsigned int>;
	using Message = std::tuple<Location, Direction, std::string>;

public:

	explicit Board(unsigned rowSize = DEFAULT_ROW_SIZE, unsigned colSize= DEFAULT_COL_SIZE)
		noexcept(false);
	void post(unsigned row, unsigned column, Direction d, const std::string& msg);
	std::string read(unsigned r, unsigned c, Direction d, unsigned length);
	void show();
	~Board(){}

private:
	// creates a board with the size of the given rows and cols
	void initBoard(unsigned rowSize, unsigned colSize) noexcept (false);
	// fill the board with '_' signs
	void drawEmptyBoard();
	// update the min,max row and col size if a Message is outside the current board and need to enlarge it 
	void updateEdges(unsigned int row, unsigned int column, Direction d, unsigned length);
	// takes all the existing messages in the board by oreder, and generate the board
	// note: being used by read() and show()
	void generateBoard();
	// a part of the generate board - takes each time a message and hang it
	void hangMessage(const Message& message);
	// print the board to the screen
	void printBoard() const;
	// returns true if a given row, col is outside the board 
	bool isOutOfBoard(unsigned currRow, unsigned currCol) const;

	std::vector<Message> _messages;
	unsigned _minRow = 0, _maxRow = 0, _minColumn = 0, _maxColumn = 0;
	unsigned _currentBoardRowSize = 0, _currentBoardColSize = 0, _currentBoardSize = 0;
	bool _isFirstMessage = true;
	std::vector<Columns> _board;
};

} // namespace ariel

#endif //UNTITLED_BOARD_HPP
