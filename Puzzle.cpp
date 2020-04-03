//
// Created by Tobias on 2020-04-02.
//
#include "Puzzle.h"

Puzzle::Puzzle(){
    std::vector<int> inValues{1,2,0,4,5,6,7,8,3};

    for(int i = 0; i < 9; i++) {
        values.push_back(inValues.at(i));
        if (inValues.at(i) == 0) {
            zeroPos = i;
        }
    }

    h_score = MisplacedTiles(values);
    g_score = 0;
}

Puzzle::Puzzle(std::vector<int>  InBoard, int gScore){
    for(int i = 0; i < 9; i++) {
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
    std::vector<std::vector<int>> OldBoards;
    while(h_score != 0){
        std::cout << OldBoards.size() <<std::endl;
        std::vector<int> PosMoves = moves();
        OldBoards.push_back(values);
        Puzzle WorkInProgressPuzzle = solve(values, PosMoves,steps, OldBoards) ;
        *this =  WorkInProgressPuzzle;
        steps++;
    }
    return *this;
}

Puzzle Puzzle::solve(std::vector<int> board, std::vector<int> moves, int gScore, std::vector<std::vector<int>> OldBoards){

    std::vector<Puzzle> DifferentBoards ;

    //Create new Puzzles
    for(int i = 0; i < moves.size(); i++){
        std::vector<int> tempValues = board;
        std::swap(tempValues.at(moves.at(i)),tempValues.at(zeroPos));
        DifferentBoards.push_back(Puzzle(tempValues, gScore));
    }

    std::vector<int> fScore;
    bool visited = false;
    std::vector<Puzzle> FilteredBoards;
    //CAlc f score
    for(size_t i = 0; i < DifferentBoards.size(); i++){
        for(size_t j = 0; j < OldBoards.size(); j++) {
            if ((DifferentBoards.at(i).values == OldBoards.at(j))) {
                visited = true;
                break;
            } else visited = false;
        }
        if(visited == false){
            FilteredBoards.push_back(DifferentBoards.at(i));
        }
    }

    for(int i = 0; i < FilteredBoards.size(); i++){
        std::cout << i << std::endl;
        fScore.push_back(FilteredBoards.at(i).ManhattanDistance() + FilteredBoards.at(i).g_score);
    }

    std::vector<int>::iterator it = std::find(fScore.begin(), fScore.end(), *std::min_element(fScore.begin(),fScore.end()));
    int index = std::distance(fScore.begin(), it);

    //Return puzzle with least f score;
    std::cout << "FScore: "<< *std::min_element(fScore.begin(),fScore.end()) <<std::endl;
    std::cout << "GScore: " << FilteredBoards.at(index).g_score <<", " << "HScore: " << FilteredBoards.at(index).h_score <<std::endl;
    FilteredBoards.at(index).Display();
    return FilteredBoards.at(index);
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
            break;
        case 6:
            posMoves = {3, 7};
            break;
        case 7:
            posMoves = {4, 8};
            break;
        case 8 :
            posMoves = {5, 7};
            break;
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