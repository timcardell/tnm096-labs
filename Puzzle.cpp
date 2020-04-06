//
// Created by Tobias on 2020-04-02.
//
#include "Puzzle.h"

Puzzle::Puzzle(){
    std::vector<int> inValues{1,2,3,4,5,0,6,7,8};

    for(int i = 0; i < 9; i++) {
        values.push_back(inValues.at(i));
        if (inValues.at(i) == 0) {
            zeroPos = i;
        }
    }
    h_score = ManhattanDistance();
    g_score = 0;
    solvable = true;
}

Puzzle::Puzzle(std::vector<int>  InBoard, int gScore){
    for(int i = 0; i < 9; i++) {
        values.push_back(InBoard.at(i));
        if (InBoard.at(i) == 0) {
            zeroPos = i;

        }
    }
    h_score = ManhattanDistance();
    g_score = gScore;
    solvable = true;
};

void Puzzle::Shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle ( values.begin(), values.end(),g );
    solvable = this->Solvable();
}





void Puzzle::updateZero(int NewPos){
    std::swap(this->values.at(zeroPos),this->values.at(NewPos));
    this->zeroPos = NewPos;
}

void Puzzle::A_Star(Puzzle In){

    std::cout << "Begin A* Algorithm" << std::endl;
    std::priority_queue<Puzzle, std::vector<Puzzle>, PriorityFunc> OpenList;
    std::vector<Puzzle> ClosedList;

    OpenList.push(In);

    std::make_heap(ClosedList.begin(),ClosedList.end());

    std::cout << "Open list size:" << OpenList.size() << std::endl;
    std::cout << "Closed list size:" << ClosedList.size() << std::endl;

    while( OpenList.size() != 0 ){

        Puzzle CurrentPuzzle = OpenList.top();
        CurrentPuzzle.Display();

        OpenList.pop();
        ClosedList.push_back(CurrentPuzzle);

        if(CurrentPuzzle.ManhattanDistance() == 0){
            std::cout << "-:Solved:-" <<std::endl;

            break;
        }

       std::sort(ClosedList.begin(),ClosedList.end());
       std::vector<int> Moves = CurrentPuzzle.moves();
        bool visited = false;
       for(int i = 0; i < Moves.size(); i++){
           Puzzle newPuzzles = Puzzle(CurrentPuzzle.values, CurrentPuzzle.g_score+1);
           newPuzzles.updateZero( Moves.at(i));

           for(int j = 0; j < ClosedList.size(); j++){
               if(newPuzzles.values != ClosedList.at(j).values){
                   OpenList.push(newPuzzles);
                   break;
               } else{
                    break;
               }
           }
       }
        std::make_heap(ClosedList.begin(),ClosedList.end());

    }

}



void Puzzle::Display(){
    std::cout <<"G_score is :" << g_score << " steps" <<std::endl;
    std::cout <<"H_score is :" << this->ManhattanDistance()  <<std::endl;
    std::cout <<"F_score is :" << g_score + this->ManhattanDistance() <<std::endl;
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

bool Puzzle::Solvable(){
    int counter = 0;
    for (size_t i  =0; i < 9; i++){
        if(values.at(i) != 0){
            int checkElement = values.at(i);
            for(size_t j = i+1; j < 9; j++){
                if(checkElement < values.at(j) ||  values.at(j) == 0 ){
                    continue;

                }
                else {
                    counter++;
                }
            }
        }
    }
    if(counter %2 ==0){
        return true;
    } else{
        return false;
    }
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
            posMoves = {6,4, 8};
            break;
        case 8 :
            posMoves = {5, 7};
            break;
        default:
            break;


    }
    return posMoves;
}

Puzzle& Puzzle::operator= ( Puzzle inPuzzle){
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

/* Misplaced tiles
//
// Created by Tobias on 2020-04-02.
//
#include "Puzzle.h"

Puzzle::Puzzle(){
    std::vector<int> inValues{1,2,3,4,5,0,6,7,8};

    for(int i = 0; i < 9; i++) {
        values.push_back(inValues.at(i));
        if (inValues.at(i) == 0) {
            zeroPos = i;
        }
    }
    h_score = ManhattanDistance();
    g_score = 0;
    solvable = true;
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
    solvable = true;
};

void Puzzle::Shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle ( values.begin(), values.end(),g );
    solvable = this->Solvable();
}





void Puzzle::updateZero(int NewPos){
    std::swap(this->values.at(zeroPos),this->values.at(NewPos));
    this->zeroPos = NewPos;
}

void Puzzle::A_Star(Puzzle In){

    std::cout << "Begin A* Algorithm" << std::endl;
    std::priority_queue<Puzzle, std::vector<Puzzle>, PriorityFunc> OpenList;
    std::vector<Puzzle> ClosedList;

    OpenList.push(In);

    std::make_heap(ClosedList.begin(),ClosedList.end());

    std::cout << "Open list size:" << OpenList.size() << std::endl;
    std::cout << "Closed list size:" << ClosedList.size() << std::endl;

    while( OpenList.size() != 0 ){

        Puzzle CurrentPuzzle = OpenList.top();
        CurrentPuzzle.Display();

        OpenList.pop();
        if(CurrentPuzzle.ManhattanDistance() == 0){
            std::cout << "-:Solved:-" <<std::endl;
            break;
        }
        ClosedList.push_back(CurrentPuzzle);



        std::sort(ClosedList.begin(),ClosedList.end());
        std::vector<int> Moves = CurrentPuzzle.moves();
        bool visited = false;
        for(int i = 0; i < Moves.size(); i++){
            Puzzle newPuzzles = Puzzle(CurrentPuzzle.values, CurrentPuzzle.g_score+1);
            newPuzzles.updateZero( Moves.at(i));

            for(int j = 0; j < ClosedList.size(); j++){
                if(newPuzzles.values != ClosedList.at(j).values){
                    OpenList.push(newPuzzles);
                    break;
                } else{
                    break;
                }
            }
        }
        std::make_heap(ClosedList.begin(),ClosedList.end());

    }

}



void Puzzle::Display(){
    std::cout <<"G_score is :" << g_score << " steps" <<std::endl;
    std::cout <<"H_score is :" << this->MisplacedTiles(values) <<std::endl;
    std::cout <<"F_score is :" << g_score + this->MisplacedTiles(values) <<std::endl;
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

bool Puzzle::Solvable(){
    int counter = 0;
    for (size_t i  =0; i < 9; i++){
        if(values.at(i) != 0){
            int checkElement = values.at(i);
            for(size_t j = i+1; j < 9; j++){
                if(checkElement < values.at(j) ||  values.at(j) == 0 ){
                    continue;

                }
                else {
                    counter++;
                }
            }
        }
    }
    if(counter %2 ==0){
        return true;
    } else{
        return false;
    }
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
            posMoves = {6,4, 8};
            break;
        case 8 :
            posMoves = {5, 7};
            break;
        default:
            break;


    }
    return posMoves;
}

Puzzle& Puzzle::operator= ( Puzzle inPuzzle){
    std::swap(values,inPuzzle.values);
    std::swap(zeroPos,inPuzzle.zeroPos);
    std::swap(g_score,inPuzzle.g_score);
    std::swap(h_score,inPuzzle.h_score);
    return *this;
}

bool Puzzle::operator<(const Puzzle &Puzzle2){
    int f1 = this->g_score + this->MisplacedTiles(values);
    int f2 = Puzzle2.g_score + Puzzle2.MisplacedTiles(Puzzle2.values);
    return f1 < f2;
}
 */