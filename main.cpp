#include <iostream>
#include <vector>
#include <algorithm>

#include "Puzzle.h"

int main() {
    Puzzle newPuzzle;
    int counter = 0;
    while(!(newPuzzle.Solvable()) || newPuzzle.ManhattanDistance() > 6){
        std::cout << "Not solvable, shuffling!" <<std::endl;
        newPuzzle.Shuffle();

        if(counter> 25){
            std::vector<int> board {1,2,3,4,5,0,6,7,8};
            newPuzzle = Puzzle(board,0);
            std::cout << std::endl;

        }
        counter++;
    }

    newPuzzle.A_Star(newPuzzle);
//newPuzzle.Display();

    return 0;
}