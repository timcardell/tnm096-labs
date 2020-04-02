//
// Created by Tobias on 2020-04-02.
//
#include <iostream>
#include <vector>
#include <cmath>
#ifndef TNM096_LABS_PUZZLE_H
#define TNM096_LABS_PUZZLE_H


struct Puzzle {

    Puzzle();
    virtual ~Puzzle(){

    };
    Puzzle(std::vector<int>  Board, int gScore);


    void A_Star();

    void Display();

    int ManhattanDistance();

    int MisplacedTiles(std::vector<int> board);

    //Variables
    std::vector<int> values;
    int zeroPos;
    int g_score = 0;
    int h_score = 0;
    int f_score = 0;

};


#endif //TNM096_LABS_PUZZLE_H
