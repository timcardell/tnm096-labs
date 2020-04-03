#include <iostream>
#include <vector>
#include <algorithm>

#include "Puzzle.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Puzzle newPuzzle;
    std::cout << "--: Begin puzzle :--" <<std::endl;
    newPuzzle.Display();
    newPuzzle.A_Star();
    return 0;
}




void left(){}
void right(){}
void up(){}
void down(){}