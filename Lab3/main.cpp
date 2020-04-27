#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <time.h>

struct Clauses {

    Clauses() = default;

    Clauses(std::vector<std::string> negative, std::vector<std::string> positive) : neg(negative), pos(positive) {}

    ~Clauses() = default;

    bool operator==(Clauses right) const {
        if (pos == right.pos) {
            return true;
        }
        return false;
    }

    bool isSubset(Clauses c);

    std::vector<std::string> neg;
    std::vector<std::string> pos;
};


//Functions
std::vector<Clauses> Solver(std::vector<Clauses> KB);
std::vector<Clauses> Incorporate(std::vector<Clauses> S, std::vector<Clauses> KB);
std::vector<Clauses> Incorporate_clause(Clauses A, std::vector<Clauses> KB);
Clauses resolution(Clauses A, Clauses B);
bool disjoint(std::vector<std::string> &vec1, std::vector<std::string> &vec2);
std::ostream &operator<<(std::ostream &out, Clauses &c);
std::vector<Clauses> removeDuplicates(std::vector<Clauses> KB);
void display(std::vector<Clauses> KB);


int main() {
    srand (time(NULL));
    Clauses A = Clauses({"sun","money"}, {"ice"});
    Clauses B = Clauses({"money"}, {"ice","movie"});
    Clauses C = Clauses({"movie"}, {"money"});
    Clauses D = Clauses({"movie","ice"}, {});
    Clauses E = Clauses({}, {"movie"});



    std::vector<Clauses> KB = {A,B,C,D,E};
    KB = Solver(KB);
    std::cout << "Solved: " << std::endl;
    for (Clauses S: KB) {
        std::cout << S << std::endl;
    }
    return 0;
}


bool disjoint(std::vector<std::string> &vec1, std::vector<std::string> &vec2) {

    for (int i = 0; i < vec1.size(); i++) {
        for (int j = 0; j < vec2.size(); j++) {
            if (vec1.at(i) == vec2.at(j)) {
                return false;
            }
        }
    }
    return true;
}

Clauses resolution(Clauses A, Clauses B) {

    if (disjoint(A.pos, B.neg) && disjoint(A.neg, B.pos)) {
        return Clauses();
    }

    if (!disjoint(A.pos, B.neg)) {
        std::vector<std::string> conjList;

        for (int i = 0; i < A.pos.size(); i++) {
            for (int j = 0; j < B.neg.size(); j++) {
                if (A.pos.at(i) == B.neg.at(j)) {
                    conjList.push_back(A.pos.at(i));
                }
            }
        }

        int randIndex = rand() % conjList.size();

        std::string a = conjList.at(randIndex);

        A.pos.erase(std::remove(A.pos.begin(), A.pos.begin(), a), A.pos.end());
        B.neg.erase(std::remove(B.neg.begin(), B.neg.begin(), a), B.neg.end());

    }
    else {
        std::vector<std::string> conjList;
        for (int i = 0; i < A.neg.size(); i++) {
            for (int j = 0; j < B.pos.size(); j++) {
                if (A.neg.at(i) == B.pos.at(j)) {
                    conjList.push_back(A.neg.at(i));
                }
            }
        }

        int randIndex = rand() % conjList.size();
        std::string a = conjList.at(randIndex);

        A.neg.erase(std::remove(A.neg.begin(),  A.neg.end(), a), A.neg.end());
        B.pos.erase(std::remove(B.pos.begin(),  B.pos.end(), a), B.pos.end());
    }

    Clauses C;
    std::vector<std::string> unPos = {};
    std::vector<std::string> unNeg = {};

    for (std::string A: A.pos) {
        for (std::string B: B.pos) {
            unPos.push_back(A);

        }
    }

    for (std::string A: A.neg) {
        for (std::string B: B.neg) {
                unNeg.push_back(A);
        }
    }

    C.pos = unPos;
    C.neg = unNeg;

    if (!disjoint(C.pos, C.neg)) {
        return Clauses();
    }

    sort(C.pos.begin(), C.pos.end());
    C.pos.erase(unique(C.pos.begin(), C.pos.end()), C.pos.end());

    sort(C.neg.begin(), C.neg.end());
    C.neg.erase(unique(C.neg.begin(), C.neg.end()), C.neg.end());


    return C;

}

std::vector<Clauses> Solver(std::vector<Clauses> KB) {

    std::vector<Clauses> KBDot;
    do {
        std::vector<Clauses> S = {};
        KBDot = KB;

        for (int i= 0; i < KB.size()-1; i++) {
            for (int j= i+1; j < KB.size(); j++) {

                Clauses C = resolution(KB.at(i), KB.at(j));

                if (C.pos.size() != 0 || C.neg.size() != 0) {
                    S.push_back(C);
                }
            }
        }

        std::cout <<std::endl<<"This is S in do: "<<std::endl;
        display(S);

        if (S.size() == 0){
            return KB;
        }

        std::cout <<"This is KB before incorporate: "<<std::endl;
        display(KB);

        //Incorporate S in KB
        KB = Incorporate(S, KB);
        KB = removeDuplicates(KB);

        std::cout <<"This is KB after incorporate: "<<std::endl;
        display(KB);
    } while (KBDot != KB);

}

std::vector<Clauses> Incorporate(std::vector<Clauses> S, std::vector<Clauses> KB) {
    for (int i = 0; i < S.size(); i++) {
        KB = Incorporate_clause(S.at(i), KB);
    }
    return KB;
}

std::vector<Clauses> Incorporate_clause(Clauses A, std::vector<Clauses> KB) {
    for (int i = 0; i < KB.size(); i++) {
        if (KB.at(i) == A) {
            return KB;
        }

    }
    for (int i = 0; i < KB.size(); i++) {
        if (A.isSubset(KB.at(i))) {
            KB.erase(KB.begin() + i);
        }
    }

    KB.push_back(A);


    return KB;
}

bool Clauses::isSubset(Clauses c) {
    for (int i = 0; i < c.pos.size(); i++) {
        std::vector<std::string>::iterator it = std::find(c.pos.begin(), c.pos.end(), c.pos.at(i));
        if (it == c.pos.end())
            return false;
    }

    for (int i = 0; i < c.neg.size(); i++) {
        std::vector<std::string>::iterator it = std::find(c.neg.begin(), c.neg.end(), c.neg.at(i));
        if (it == c.neg.end())
            return false;
    }

    return true;
}

std::vector<Clauses> removeDuplicates(std::vector<Clauses> KB){
    std::vector<Clauses>tempKB = KB;

    for (int i = 0; i < KB.size() -1; i++){
        for (int j = i + 1; j < tempKB.size(); j++){
            if (KB.at(i) == tempKB.at(i)){
                KB.erase(KB.begin() + i);
            }
        }
    }
    return KB;
}

std::ostream &operator<<(std::ostream &out, Clauses &c) {

    if (c.pos.size() == 0 && c.neg.size() == 0) {
        out << "false" << std::endl;
    }
    else {
        out << "{ ";
        for (int i = 0; i < c.pos.size(); i++) {
            out << c.pos.at(i) ;
            if(i != c.pos.size()-1){
                out << " V ";
            }
        }

        if(c.neg.size() > 0 && c.pos.size() > 0){
            out << " V ";
        }

        for (int i = 0; i < c.neg.size(); i++) {
            out <<"-" << c.neg.at(i) ;
            if(i != c.neg.size()-1){
                out << " V ";
            }
        }
        out << "} ";
    }
    return out;
}

void display(std::vector<Clauses> KB){
    for (int i = 0; i < KB.size(); i++){
        std::cout << KB.at(i) <<std::endl;
    }
}