//
// Created by Tobias on 2020-04-02.
//
#include "Puzzle.h"

Puzzle::Puzzle(){
    std::vector<int> inValues{8,6,7,2,5,4,3,0,1};
   // std::vector<int> inValues{1,2,3,0,4,6,7,5,8};
    for(int i = 0; i < 9; i++) {
        values.push_back(inValues.at(i));
        if (inValues.at(i) == 0) {
            zeroPos = i;
        }
    }
    h_score = ManhattanDistance();
    g_score = 0;
    f_score = h_score + g_score;

}

Puzzle::Puzzle(Puzzle inPuzzle, int gScore){
    for(int i = 0; i < 9; i++) {
        values.push_back(inPuzzle.values.at(i));
        if (inPuzzle.values.at(i) == 0) {
            zeroPos = i;
        }
    }
    h_score = ManhattanDistance()-1;
    g_score = gScore;
    f_score = h_score + g_score;
};


void Puzzle::updateZero(int NewPos){
    std::swap(this->values.at(zeroPos),this->values.at(NewPos));
    this->zeroPos = NewPos;
}

void Puzzle::A_Star(Puzzle In){
    std::priority_queue<Puzzle, std::vector<Puzzle>, PriorityFunc> OpenList;
    std::vector<Puzzle> ClosedList;

    OpenList.push(In);
    std::make_heap(ClosedList.begin(),ClosedList.end());

    while(OpenList.size() != 0){
        Puzzle CurrentPuzzle = OpenList.top();
        OpenList.pop();
        ClosedList.push_back(CurrentPuzzle);

        if(CurrentPuzzle.h_score == 0){
            std::cout << "-:Solved:-" <<std::endl;
            CurrentPuzzle.Display();

           // std::cout << "Displaying right path:" <<std::endl;
            break;
        }

        std::sort(ClosedList.begin(),
                  ClosedList.end(),
                  [](const Puzzle& lhs, const Puzzle& rhs)
                  {
                      return lhs.ManhattanDistance() <  rhs.ManhattanDistance();
                  });

        std::vector<int> Moves = CurrentPuzzle.moves();

       for(int i = 0; i < Moves.size(); i++){
           Puzzle newPuzzles = Puzzle(CurrentPuzzle, CurrentPuzzle.g_score+1);
           newPuzzles.updateZero(Moves.at(i));
           bool visited = false;
           for(int j = 0; j < ClosedList.size(); j++){
               if(newPuzzles.values == ClosedList.at(j).values){
                   visited = true;
                   break;
               }
           }
           if(!visited){
               OpenList.push(newPuzzles);
           }
       }
        std::make_heap(ClosedList.begin(),ClosedList.end());

    }

}



void Puzzle::Display(){
    for(size_t i = 0; i < values.size(); i++){
        if((i+1)%3 == 0){
            std::cout <<values.at(i)<< std::endl;
        }
        else
            std::cout << values.at(i)  <<" | ";
    }
    std::cout <<std::endl;
}

int Puzzle::MisplacedTiles(std::vector<int> board) const{
    int counter = 0;
    for(size_t i = 0; i< board.size(); i++){
        if(board.at(i)-1 != i && board.at(i) != 0) {
            counter++;
        }
    }
    return counter;
}


int Puzzle::ManhattanDistance() const{
    int Dist = 0;
    for(int i = 0; i < values.size(); i++){

        if(values.at(i) != 0){
            int col = i%3;
            int row = std::floor(i/3);
            int rightCol = (values[i]-1)%3;
            int rightRow = std::floor(values[i]-1)/3;
           Dist += abs(rightRow-row)+abs(rightCol-col);
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
            posMoves = {0,4,6};
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
            posMoves = {4,6, 8};
            break;
        case 8 :
            posMoves = {5, 7};
            break;
        default:
            break;
    }
    return posMoves;
}

Puzzle& Puzzle::operator = ( Puzzle inPuzzle){
    std::swap(values,inPuzzle.values);
    std::swap(zeroPos,inPuzzle.zeroPos);
    std::swap(g_score,inPuzzle.g_score);
    std::swap(h_score,inPuzzle.h_score);
    return *this;
}

bool Puzzle::operator<(const Puzzle &Puzzle2){
    int f1 = this->g_score + this->ManhattanDistance();
    int f2 = Puzzle2.g_score + Puzzle2.ManhattanDistance();
    return f1 < f2;
}
