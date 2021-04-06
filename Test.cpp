

#include "doctest.h"
#include "Board.hpp"
#include <iostream>
#include <ctime>
#include <stdexcept>
#include <string>

using namespace ariel;
using namespace std;




TEST_CASE("checks  post and read ")
{
    Board b;
    CHECK_NOTHROW(b.post(15, 3, Direction::Horizontal, "SAGIE"));
    CHECK(b.read(15, 3, Direction::Horizontal, 5) == "SAGIE");

    CHECK_NOTHROW(b.post(10,5, Direction::Horizontal, "sagie"));
    CHECK_NOTHROW(b.post(9,9, Direction::Vertical, "barhod"));
    CHECK(b.read(10, 5, Direction::Horizontal, 5) == "sagia");

    CHECK_NOTHROW(b.post(0, 0, Direction::Horizontal, "hello"));
    CHECK_NOTHROW(b.post(0, 0, Direction::Vertical, "HELLO"));
     CHECK(b.read(0, 0, Direction::Horizontal, 5) == "Hello");
 }


TEST_CASE(" checking Overwriting letters  "){
    Board b;
    b.post(0, 0, Direction::Horizontal, "ssssssss");
    CHECK(b.read(0, 0, Direction::Horizontal, 8) == "ssssssss");
    b.post(0, 0, Direction::Horizontal, "ssssssss");
    CHECK(b.read(0, 0, Direction::Horizontal, 8) == "ssssssss");
    b.post(0, 0, Direction::Vertical, "aaaaaaaa");
    CHECK(b.read(0, 0, Direction::Horizontal, 8) == "asssssss");
    b.post(0, 1, Direction::Vertical, "ggggggggg");
    CHECK(b.read(0, 0, Direction::Horizontal, 8) == "agssssss");
    b.post(0, 2, Direction::Vertical, "iiiiiiii");
    CHECK(b.read(0, 0, Direction::Horizontal, 8) == "agisssss");
    b.post(0, 3, Direction::Vertical, "eeeeeeee");
    CHECK(b.read(0, 0, Direction::Horizontal, 8) == "agiessss");
   
}

TEST_CASE( "checking length 0 -empty board")
{
    Board b;
    CHECK(b.read(0, 0, Direction::Horizontal, 0) == "");
    CHECK(b.read(5, 1, Direction::Horizontal, 0) == "");
    CHECK(b.read(7, 0, Direction::Horizontal, 1) == string("_"));
    CHECK(b.read(8, 0, Direction::Vertical, 1) == string("_"));
    CHECK(b.read(1, 1, Direction::Horizontal, 2) == string("__"));
    CHECK(b.read(10, 1, Direction::Vertical, 2) == string("__"));
    CHECK(b.read(2, 55, Direction::Horizontal, 3) == string("___"));
    CHECK(b.read(21, 46, Direction::Vertical, 3) == string("___"));
    CHECK(b.read(23, 74, Direction::Horizontal, 6) == string("______"));
    CHECK(b.read(12, 4, Direction::Vertical, 6) == string("______"));
    CHECK(b.read(1, 6, Direction::Horizontal, 9) == string("_________"));
    CHECK(b.read(5, 7, Direction::Vertical, 9) == string("_________"));
}

TEST_CASE(" Checking strings and overriding text")
{
    Board b;

    b.post(0, 0, Direction::Horizontal, "Sagie");
	b.post(1, 0, Direction::Vertical, "hod");
    CHECK(b.read(0, 0, Direction::Horizontal, 5) + " "
    + b.read(1, 0, Direction::Vertical, 3) == "Sagie hod");
   
//Sagie hod  
//0: sagie
//1: h____
//2: o____
//3: d____

} 

TEST_CASE(" - row and coulmn"){
    Board b;
    
    CHECK_NOTHROW(b.post(-2, -1, Direction::Horizontal, "ssss"));
    CHECK_NOTHROW(b.post(-1, 3, Direction::Horizontal, "ssss"));
    CHECK_NOTHROW(b.post(0, -1, Direction::Horizontal, "ssss"));
}

TEST_CASE("Unusual and bad invaild")
{
    Board b;
    CHECK_NOTHROW(b.post(12, 12, Direction::Horizontal, "*"));
    CHECK(b.read(12, 12, Direction::Horizontal, 1) == "*");
    CHECK_NOTHROW(b.post(10, 10, Direction::Horizontal, "!"));
    CHECK(b.read(10, 10, Direction::Horizontal, 1) == "!");
    CHECK_NOTHROW(b.post(30, 5, Direction::Vertical, "1325%"));
    CHECK(b.read(30, 5, Direction::Vertical, 5) == "1325%");
}



