#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

struct Clauses{

    Clauses() = default;
    Clauses(std::vector<std::string>  negative, std::vector<std::string> positive): neg(negative), pos(positive){}
    ~Clauses() = default;

//Functions
    std::vector<Clauses> Solver(std::vector<Clauses> KB);
    std::vector<Clauses> Incorporate(std::vector<Clauses> S,std::vector<Clauses> KB);
    std::vector<Clauses> Incorporate_clause(Clauses A,std::vector<Clauses> KB);
    int CardinalLess (Clauses A);
    std::vector<Clauses> UnionClauses(Clauses A,std::vector<Clauses> KB);
    Clauses resolution(Clauses& A, Clauses& B);

    bool disjoint(std::vector<std::string> &vec1, std::vector<std::string> &vec2);
    bool operator ==(Clauses A){
        if(this->pos == A.pos && this->neg == A.neg){
            return true;
        }
            return false;
    }

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
                if(A.pos.at(i) != B.neg.at(j)){
                    conjList.push_back(A.pos.at(i));
                }
            }
        }

        int randIndex = rand() % conjList.size();
        std::string a = conjList.at(randIndex);
        A.pos.erase(std::remove(A.pos.begin(),A.pos.begin(),a),A.pos.end());
        B.pos.erase(std::remove(B.pos.begin(),B.pos.begin(),a),B.pos.end());
    }
    else{
        std::vector<std::string> conjList;

        for(int i = 0; i< A.neg.size(); i++){
            for(int j = 0; j < B.pos.size(); j++){
                if(A.neg.at(i) != B.pos.at(j)){
                    conjList.push_back(A.pos.at(i));
                }
            }
        }
        int randIndex = rand() % conjList.size();
        std::string a = conjList.at(randIndex);
        A.neg.erase(std::remove(A. neg.begin(),A.neg.begin(),a),A.neg.end());
        B.pos.erase(std::remove(B.pos.begin(),B.pos.begin(),a),B.pos.end());

    }
    Clauses C;
    std::vector<std::string> unPos = {};
    std::vector<std::string> unNeg = {};
    for(std::string A: A.pos){
        for(std::string B: B.pos){
            if(A == B){
                unPos.push_back(A);
            }
        }
    }
    for(std::string A: A.neg){
        for(std::string B: B.neg){
            if(A == B){
                unNeg.push_back(A);
            }
        }
    }

    C.pos = unPos;
    C.neg = unNeg;

    if(!disjoint(C.pos, C.neg)){
        return Clauses();
    }

    sort( C.pos.begin(), C.pos.end() );
    C.pos.erase( unique(  C.pos.begin(), C.pos.end() ), C.pos.end() );

    sort( C.neg.begin(), C.neg.end() );
    C.neg.erase( unique(  C.neg.begin(), C.neg.end() ), C.neg.end() );

    return C;

}

int main() {

    Clauses c({"a", "a", "b"}, {"a", "b", "a"});
    Clauses B({"a", "a", "b"}, {"a", "b", "a"});
    c.resolution(c,B);
    return 0;
}


/*
function Solver(KB) return set of clauses
        Input: set of clauses KB
repeat
        S = {}
KB0 ← KB
for each A, B in KB :
C ← Resolution(A,B)
if C 6= false do
S ← S ∪ {C}
if S = {}
return KB
        KB ← Incorporate(S, KB)
until KB0 = KB
 */

std::vector<Clauses> Clauses::Solver(std::vector<Clauses> KB){
    std::vector<Clauses> S = {};
    std::vector<Clauses> KBap;
do{
    for(Clauses A: KB){
        for(Clauses B: KB){
            Clauses C = resolution(A,B);
            if(C.pos.size() != 0){
                S = UnionClauses(C,S);
            }
        }
    }
    if(S.size() == 0){
        return KB;
    }
    KB = Incorporate(S,KB);
}
while(KBap != KB);

}

/*
function Incorporate(S,KB) return set of clauses
        Input: set of clauses S, set of clauses KB
for each A in S :
KB ← Incorporate clause(A, KB)
return KB
 */

std::vector<Clauses> Clauses::Incorporate(std::vector<Clauses> S,std::vector<Clauses> KB){
    for(Clauses A: S){
        KB = Incorporate_clause(A,KB);
    }
    return KB;
}

/*function Incorporate clause(A,KB) return set of clauses
Input: clause A, set of clauses KB
if there is a clause B ∈ KB such that B < A do
return KB
for each B in KB :
if A ≺ B do
KB ← KB − {B}
KB ← KB ∪ {A}
return KB
*/

std::vector<Clauses> Clauses::Incorporate_clause(Clauses A,std::vector<Clauses> KB){
    for(Clauses B: KB){
        if(CardinalLess(B) - CardinalLess(A) < 0){
            return KB;
        }
    }

    for(Clauses B: KB){
        if(CardinalLess(A) - CardinalLess(B) < 0){
            KB.erase(std::remove(KB.begin(),KB.end(),B),KB.end());
        }
    }

    KB = UnionClauses(A,KB);
    return KB;
}

int Clauses::CardinalLess (Clauses A) {
    int cardinalA = 0;
    cardinalA =  A.pos.size()+ A.neg.size();
    return  cardinalA;
}

std::vector<Clauses> Clauses::UnionClauses(Clauses A,std::vector<Clauses> KB){
    std::vector<Clauses> Res;
    for(Clauses B: KB){
        if(A == B){
            Res.push_back(A);
        }
    }
    return Res;
}
