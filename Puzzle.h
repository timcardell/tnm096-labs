//
// Created by Tobias on 2020-04-02.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <queue>
#ifndef TNM096_LABS_PUZZLE_H
#define TNM096_LABS_PUZZLE_H


struct Puzzle {

    Puzzle();
    Puzzle(std::vector<int>  Board, int gScore);
    virtual ~Puzzle(){};

    bool operator < (const Puzzle& str) const
    {
        return (this->g_score + this->ManhattanDistance() < str.g_score + str.ManhattanDistance());
    }

    void A_Star(Puzzle In);
    void Shuffle();
    bool Solvable();

    void Display();
    std::vector<int> moves();

    int ManhattanDistance() const;
    void updateZero(int NewPos);
    bool operator<( const Puzzle &Puzzle);

    int MisplacedTiles(std::vector<int> board) const;

    Puzzle& operator= (Puzzle &inPuzzle);

    //Variables
    std::vector<int> values;
    int zeroPos;
    int g_score = 0;
    int h_score = 0;
    bool solvable;
};


class PriorityFunc{
public:
    bool operator()(Puzzle &Puzzle1, Puzzle &Puzzle2){
        int f1 = Puzzle1.g_score + Puzzle1.ManhattanDistance();
        int f2 = Puzzle2.g_score + Puzzle2.ManhattanDistance();
        return f1 > f2;
    }
};

#endif //TNM096_LABS_PUZZLE_H
