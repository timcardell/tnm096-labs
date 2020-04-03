//
// Created by Tobias on 2020-04-02.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#ifndef TNM096_LABS_PUZZLE_H
#define TNM096_LABS_PUZZLE_H


struct Puzzle {

    Puzzle();
    Puzzle(std::vector<int>  Board, int gScore);
    virtual ~Puzzle(){};

    Puzzle solve(std::vector<int> board,std::vector<int> move,int steps);

    Puzzle A_Star();

    void Display();
    std::vector<int> moves();

    int ManhattanDistance();

    int MisplacedTiles(std::vector<int> board);

    Puzzle& Puzzle::operator= (Puzzle &inPuzzle);

    //Variables
    std::vector<int> values;
    int zeroPos;
    int g_score = 0;
    int h_score = 0;

};


#endif //TNM096_LABS_PUZZLE_H
