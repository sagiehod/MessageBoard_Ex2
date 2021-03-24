#include "Board.hpp"

namespace ariel
{

const char EMPTY_MARK = '_';

/**
 * ctor: initialize an empty board and fill it with '_' signs
 * warning: might throw exception if allocation failed when resize the
 */
Board::Board(unsigned rowSize, unsigned colSize)
{
	_currentBoardRowSize = rowSize;
	_currentBoardColSize = colSize;
	_currentBoardSize = _currentBoardRowSize * _currentBoardColSize;
	initBoard(rowSize, colSize);
	drawEmptyBoard();
}

void Board::post(unsigned row, unsigned column, Direction d, const std::string& msg)
{
	updateEdges(row, column, d, msg.length());
	const auto location = std::make_pair(row, column);
	_messages.emplace_back(location, d, msg);
}

std::string Board::read(unsigned r, unsigned c, Direction d, unsigned length)
{
	std::string strToReturn;
	auto horizontal = (d == Direction::Horizontal) ? 1 : 0;
	generateBoard();

	// read each character from the board.
	for(unsigned i = 0; i < length; i++)
	{
		auto currRow = r + i * (1 - horizontal);
		auto currCol =  c + i * horizontal;
		// if outside board, mark with '_' . otherwise, just read
		strToReturn += isOutOfBoard(currRow, currCol) ? EMPTY_MARK :
				_board[currRow - _minRow][currCol - _minColumn];
	}
	return strToReturn;
}

void Board::show()
{
	generateBoard();
	printBoard();
}

/* private section */

void Board::initBoard(unsigned rowSize, unsigned colSize)
{
	_board.clear();
	_board.resize(rowSize, Columns (colSize));
}

bool Board::isOutOfBoard(unsigned currRow, unsigned currCol) const
{
	return currRow < _minRow || currRow > _maxRow  ||
	 currCol < _minColumn || currCol > _maxColumn;
}

void Board::drawEmptyBoard()
{
	for(unsigned i = 0; i < _currentBoardRowSize; i++)
	{
		for(unsigned j = 0; j < _currentBoardColSize; j++)
		{
			_board[i][j] = EMPTY_MARK;
		}
	}
}

/**
 * put all messages one by one on the board, in order to read from it or show it later on
 */
void Board::generateBoard()
{
	const auto rowLength = _maxRow - _minRow + 1;
	const auto columnLength = _maxColumn - _minColumn + 1;
	const auto boardSize = rowLength * columnLength;

	// resize the board if needed
	if (boardSize > _currentBoardSize)
	{
		_currentBoardRowSize = rowLength;
		_currentBoardColSize = columnLength;
		_currentBoardSize = _currentBoardRowSize * _currentBoardColSize;
		initBoard(rowLength, columnLength);
		drawEmptyBoard();
	}

	for(const auto& currMessage : _messages)
	{
		hangMessage(currMessage);
	}
}

// print the message on the board (according to the instructions inside the Message tuple)
void Board::hangMessage(const Message& message)
{
	unsigned horizontal=0;

	// unpack from the tuple
	horizontal = std::get<Direction>(message) == Direction::Horizontal ? 1 : 0;
	auto text = std::get<std::string>(message);
	auto messageLength = text.size();
	auto initialRow = std::get<Location>(message).first - _minRow;
	auto initialCol = std::get<Location>(message).second - _minColumn;

	// print the message on the board
	for(unsigned i = 0; i < messageLength; i++)
	{
		_board[initialRow + i * (1 - horizontal)][initialCol + i * horizontal] = text[i];
	}
}

void Board::updateEdges(unsigned int row, unsigned int column, Direction d, unsigned length)
{
	// if first message, define the min, max rows/cols values according to this message
	if (_isFirstMessage)
	{
		_minRow = row;
		_minColumn = column;
		if (d == Direction::Horizontal)
		{
			_maxRow = row;
			_maxColumn = column + length - 1;
		}
		else
		{
			_maxRow = row + length - 1;
			_maxColumn = column;
		}
		_isFirstMessage = false;
		return;
	}

	// if not first message, update edges only if needed
	if (row < _minRow){
		_minRow = row;
	}
	if (column < _minColumn){
		_minColumn = column;
	}
	if(row > _maxRow){
		_maxRow = row;
	}
	if(column > _maxColumn){
		_maxColumn = column;
	}
	if (d == Direction::Vertical && (row + length - 1) > _maxRow){
		_maxRow = (row + length - 1);
	}
	else if (d == Direction::Horizontal && (column + length - 1) > _maxColumn){
		_maxColumn = (column + length - 1);
	}
}

void Board::printBoard() const
{
	std::cout << "   ";
	for(unsigned j = 0; j < _currentBoardColSize; j++)
	{
		std::cout << _minColumn + j + 1;
	}	

	std::cout << std::endl;
	for(unsigned i = 0; i < _currentBoardRowSize; i++)
	{
		std::cout << std::to_string(_minRow + i) + ": ";
		for(unsigned j = 0; j < _currentBoardColSize; j++)
		{
			std::cout << _board[i][j];
		}
		std::cout << std::endl;
	}
}

} // namespace ariel