//
// Created by Tobias on 2020-04-02.
//
#include "Puzzle.h"

Puzzle::Puzzle(){
    std::vector<int> inValues{3,2,1,4,5,6,7,8,0};

    for(size_t i = 0; i < 9; i++) {
        values.push_back(inValues.at(i));
        if (inValues.at(i) == 0) {
            zeroPos = i;
           
        }
    }
    g_score = 0;
}

Puzzle::Puzzle(std::vector<int>  InBoard, int gScore){
    for(size_t i = 0; i < 9; i++) {
        values.push_back(InBoard.at(i));
        if (InBoard.at(i) == 0) {
            zeroPos = i;
        }
    }
    g_score = gScore;
};

void Puzzle::A_Star(){


}

void Puzzle::Display(){
    for(size_t i = 0; i < values.size(); i++){
        std::cout << values.at(i) <<std::endl;
    }
}

int Puzzle::MisplacedTiles(std::vector<int> board){
    int counter = 0;
    for(size_t i = 0; i< board.size(); i++){
        if(board.at(i)-1 != i && board.at(i) != 0) {
            counter++;
        }
    }
    return counter;
}

int Puzzle::ManhattanDistance(){
    int Dist = 0;
    for(int i = 0; i < values.size(); i++){

        if(values.at(i) != 0){
            int col = i%3;
            int row = std::floor(i/3);
            int rightCol = (values[i]-1)%3;
            int rightRow = std::floor(values[i]-1)/3;

           Dist += abs(row-rightRow)+abs(col-rightCol);
        }
    }
    return Dist;
}

std::vector<int> Puzzle::moves() {
    std::vector<int> posMoves;
    switch(zeroPos){
        case 0:
            posMoves = {1,3};
            break;
        case 1:
            posMoves = {0,2,4};
            break;
        case 2:
            posMoves = {1,5};
            break;
        case 3:
            posMoves = {0,6,4};
            break;
        case 4:
            posMoves = {1,3,5,7};
            break;
        case 5 :
            posMoves = {2, 4, 8};
        case 6:
            posMoves = {3, 7};
            break;
        case 7:
            posMoves = {4, 8};
            break;
        case 8 :
            posMoves = {5, 7};
        default:
            break;


    }
    return posMoves;
}
