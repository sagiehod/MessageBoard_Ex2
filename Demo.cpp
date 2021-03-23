/**
 * Demo program for message-board exercise.
 * 
 * Author: Erel Segal-Halevi
 * Since : 2021-03
 */

#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
	ariel::Board board;
	// board.post(/*row=*/100, /*column=*/200, Direction::Horizontal, "abcd");
	// cout << board.read(/*row=*/99, /*column=*/201, Direction::Vertical, /*length=*/3) << endl;  
	// 	// prints "_b_" (starts at row 99 which is empty; then at row 100 there is "b"; then row 101 is empty again).
	// board.post(/*row=*/99, /*column=*/202, Direction::Vertical, "xyz");
	// cout << board.read(/*row=*/100, /*column=*/200, Direction::Horizontal, /*length=*/6) << endl;  
	// 	// prints "abyd__" (First letters are ab; then y from the "xyz"; then d; then two empty cells).
    board.post(0, 0, Direction::Horizontal, "ssssssss");
    cout <<board.read(0, 0, Direction::Horizontal, 8) << endl;
    board.post(0, 0, Direction::Vertical, "ssssssss");
    cout <<board.read(0, 0, Direction::Horizontal, 8)  << endl;
    board.post(0, 1, Direction::Vertical, "aaaaaaaa");
    cout <<board.read(0, 0, Direction::Horizontal, 8) << endl;
    board.post(0, 2, Direction::Vertical, "gggggggg");
    cout <<board.read(0, 0, Direction::Horizontal, 8)  << endl;
    board.post(0, 3, Direction::Vertical, "iiiiiiii");
    cout <<board.read(0, 0, Direction::Horizontal, 8)  << endl;
    board.post(0, 4, Direction::Vertical, "eeeeeeee");
    cout <<board.read(0, 0, Direction::Horizontal, 8)   << endl;


	board.show(); // shows the board in a reasonable way. For example:
		//    98:  _________
		//    99:  ____x____
		//    100: __abyd___
		//    101: ____z____
		//    102: _________
}

