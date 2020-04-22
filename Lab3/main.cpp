#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

class Clauses{
public:
    Clauses() = default;
    Clauses(std::vector<std::string>  negative, std::vector<std::string> positive): neg(negative), pos(positive){}
    ~Clauses() = default;

    Clauses resolution(Clauses& A, Clauses& B);

    bool disjoint(std::vector<std::string> &vec1, std::vector<std::string> &vec2);
private:
    std::vector<std::string> neg;
    std::vector<std::string> pos;
};

bool Clauses::disjoint(std::vector<std::string> &vec1, std::vector<std::string> &vec2) {
    for(int i = 0; i < vec1.size(); i++){
        for(int j = 0; i < vec2.size(); j++){
            if(vec1.at(i) == vec2.at(j)){
                return false;
            }
        }
    }
    return true;
}

Clauses Clauses::resolution(Clauses &A, Clauses &B) {
    if(disjoint(A.pos, B.neg) && disjoint(A.neg, B.pos)){
        return Clauses();
    }


    if(!disjoint(A.pos, B.neg)){
        std::vector<std::string> conjList;

        for(int i = 0; i< A.pos.size(); i++){
            for(int j = 0; j < B.neg.size(); j++){
                if(A.pos.at(i) == B.neg.at(j)){
                    conjList.push_back(A.pos.at(i));
                }
            }
        }
        std::string a;
        int randIndex;
        randIndex = rand() % conjList.size();
        a = conjList.at(randIndex);

    }
}

int main() {

    Clauses c({"a", "a", "b"}, {"a", "b", "a"});
    
    return 0;
}
