#include <iostream>
#include <stdexcept>
#include "Board.hpp"
#include "Direction.hpp"
#include <iostream>
#include <ctime>
#include <thread>
#include <random>
#include <chrono>
#define EVER ; ;

using namespace std;
using namespace ariel;

constexpr int MAX_ROW = 12;
constexpr int MAX_COL = 12;
constexpr int MAX_COLOR_NUM = 3;

const string RED_COLOUR = "\e[1;31m";
const string PURPLE_COLOUR = "\e[1;95m";
const string GREEN_COLOUR = "\e[1;92m";


void clearScreen()
{
    cout << string (100, '\n');
}

int main() {
	Board board;

	srand((unsigned) time(nullptr));
	string colors[] = {RED_COLOUR, PURPLE_COLOUR, GREEN_COLOUR};
	auto colorNum = 0;

	for (EVER)
	{
        unsigned int messageRow = (rand() % MAX_ROW);
         unsigned int messageCol = (rand() % MAX_COL);
        board.post( messageRow, messageCol, Direction::Vertical, "hello");
        
		colorNum = (rand() % MAX_COLOR_NUM);
        cout << colors[colorNum];
        board .show();

		this_thread::sleep_for(chrono::milliseconds(1200));
        clearScreen();

        messageRow = (rand() % MAX_ROW);
        messageCol = (rand() % MAX_COL);
        board.post(messageRow, messageCol, Direction::Horizontal, "sagi");

		colorNum = (rand() % MAX_COLOR_NUM);
        cout << colors[colorNum];
        board .show();

		this_thread::sleep_for(chrono::milliseconds(1200));


	}

    return 0;
}


