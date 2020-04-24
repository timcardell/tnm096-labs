#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

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

int CardinalLess(Clauses A);

std::vector<Clauses> UnionClauses(Clauses A, std::vector<Clauses> KB);

Clauses resolution(Clauses A, Clauses B);

bool disjoint(std::vector<std::string> &vec1, std::vector<std::string> &vec2);

std::ostream &operator<<(std::ostream &out, Clauses &c);

int main() {

    Clauses A = Clauses({"c"}, {"a","b"});
    Clauses B = Clauses({}, {"c", "b"});

    Clauses C = resolution(A,B);
    Clauses D = Clauses({}, {"a", "b"});
    std::cout << C <<std::endl;

   // std::vector<Clauses> KB = {A,B,C,D,E};
    //KB = Solver(KB);

    //for (Clauses S: KB) {
    //    std::cout << S << std::endl;
   // }
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

/*
function Solver(KB) return set of clauses
        Input: set of clauses KB
repeat
        S = {}
KB0 ← KB
for each A, B in KB :
C ← Resolution(A,B)
if C = false do
S ← S ∪ {C}
if S = {}
return KB
        KB ← Incorporate(S, KB)
until KB0 = KB
 */

std::vector<Clauses> Solver(std::vector<Clauses> KB) {

    std::vector<Clauses> KBap;
    do {
        std::vector<Clauses> S = {};
        KBap = KB;

        for (int i= 0; i < KB.size()-1; i++) {

            for (int j= i+1; j < KB.size(); j++) {

                Clauses C = resolution(KB.at(i), KB.at(j));


                if (C.pos.size() != 0 || C.neg.size() != 0) {
                    S.push_back(C);
                }
            }
        }
        for(Clauses K: S){
            std::cout << K <<std::endl;
        }

        if (S.size() == 0) {
            return KB;
        }

        KB = Incorporate(S, KB);

    } while (KBap != KB);

}

/*
function Incorporate(S,KB) return set of clauses
        Input: set of clauses S, set of clauses KB
for each A in S :
KB ← Incorporate clause(A, KB)
return KB
 */

std::vector<Clauses> Incorporate(std::vector<Clauses> S, std::vector<Clauses> KB) {
    for (Clauses A: S) {
        KB = Incorporate_clause(A, KB);
    }
    return KB;
}

/*function Incorporate clause(A,KB) return set of clauses
Input: clause A, set of clauses KB
if there is a clause B ∈ KB such that B ≺= A do
return KB
for each B in KB :
if A ≺ B do
KB ← KB − {B}
KB ← KB ∪ {A}
return KB
*/

std::vector<Clauses> Incorporate_clause(Clauses A, std::vector<Clauses> KB) {
    for (Clauses B: KB) {
        if (B.isSubset(A)) {
            return KB;
        }
    }
    for (Clauses B: KB) {
        if (A.isSubset(B)) {
            KB.erase(std::remove(KB.begin(), KB.end(), B), KB.end());
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

std::ostream &operator<<(std::ostream &out, Clauses &c) {

    if (c.pos.size() == 0 && c.neg.size() == 0) {
        out << "false" << std::endl;
    } else {

        for (int i = 0; i < c.pos.size(); i++) {
            if (c.pos.size() >= 1) {
                out << c.pos.at(i) ;
            }
            if(i != c.pos.size()-1){
                out << " V ";
            }
        }

        if(c.neg.size() > 1 && c.pos.size() > 1){
            out << " V ";
        }

        for (int i = 0; i < c.neg.size(); i++) {

            if (c.neg.size() >= 1) {
                out <<"-" << c.neg.at(i) ;
            }
            if(i != c.neg.size()-1){
                out << " V ";
            }

        }

    }


    return out;
}