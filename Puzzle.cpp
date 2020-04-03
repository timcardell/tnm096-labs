//
// Created by Tobias on 2020-04-02.
//
#include "Puzzle.h"

Puzzle::Puzzle(){
    std::vector<int> inValues{1,2,3,0,4,6,7,5,8};

    for(size_t i = 0; i < 9; i++) {
        values.push_back(inValues.at(i));
        if (inValues.at(i) == 0) {
            zeroPos = i;
        }
    }
    h_score = MisplacedTiles(values);
    g_score = 0;
}

Puzzle::Puzzle(std::vector<int>  InBoard, int gScore){
    for(size_t i = 0; i < 9; i++) {
        values.push_back(InBoard.at(i));
        if (InBoard.at(i) == 0) {
            zeroPos = i;
        }
    }
    h_score = MisplacedTiles(values);
    g_score = gScore;
};

Puzzle Puzzle::A_Star(){
    int steps = 1;

    while(h_score != 0){
        std::vector<int> PosMoves = moves();
        Puzzle WorkInProgressPuzzle = solve(values, PosMoves,steps) ;
        *this =  WorkInProgressPuzzle;
        steps++;
    }
    return *this;
}

Puzzle Puzzle::solve(std::vector<int> board, std::vector<int> moves, int gScore){

    std::vector<Puzzle> DifferentBoards ;

    //Create new Puzzles
    for(size_t i = 0; i < moves.size(); i++){
        std::vector<int> tempValues = board;
        std::swap(tempValues.at(moves.at(i)),tempValues.at(zeroPos));
        DifferentBoards.push_back(Puzzle(tempValues, gScore));
    }

    std::vector<int> fScore;
    //CAlc f score
    for(int i = 0; i < DifferentBoards.size(); i++){
        fScore.push_back(DifferentBoards.at(i).ManhattanDistance() + DifferentBoards.at(i).g_score);

    }

    std::vector<int>::iterator it = std::find(fScore.begin(), fScore.end(), *std::min_element(fScore.begin(),fScore.end()));
    int index = std::distance(fScore.begin(), it);

    //Reuturn puzzle with least f score;
    std::cout << "FScore: "<< *std::min_element(fScore.begin(),fScore.end()) <<std::endl;
    std::cout << "GScore: " << DifferentBoards.at(index).g_score <<", " << "HScore: " << DifferentBoards.at(index).h_score <<std::endl;
    DifferentBoards.at(index).Display();
    return DifferentBoards.at(index);
}


void Puzzle::Display(){
    std::cout <<"After :" << g_score << " steps" <<std::endl;
    for(size_t i = 0; i < values.size(); i++){

        if((i+1)%3 == 0){
            std::cout <<values.at(i)<< std::endl;
        }
        else
            std::cout << values.at(i)  <<" | ";
    }
    std::cout <<std::endl;
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

Puzzle& Puzzle::operator= (Puzzle &inPuzzle){
    std::swap(values,inPuzzle.values);
    std::swap(zeroPos,inPuzzle.zeroPos);
    std::swap(g_score,inPuzzle.g_score);
    std::swap(h_score,inPuzzle.h_score);
    return *this;
}