#include <iostream>
#include <vector>
#include <algorithm>
struct Clauses{

    Clauses(){}
    Clauses(std::vector<std::string>  negative, std::vector<std::string> positive): neg(negative), pos(positive){}
    ~Clauses() = default;

    bool operator ==(Clauses A){
        if(this->pos == A.pos && this->neg == A.neg){
            return true;
        }
            return false;
    }

    std::vector<std::string> neg;
    std::vector<std::string> pos;
};

//Functions
std::vector<Clauses> Solver(std::vector<Clauses> KB);
std::vector<Clauses> Incorporate(std::vector<Clauses> S,std::vector<Clauses> KB);
std::vector<Clauses> Incorporate_clause(Clauses A,std::vector<Clauses> KB);
int CardinalLess (Clauses A);
std::vector<Clauses> UnionClauses(Clauses A,std::vector<Clauses> KB);

int main() {


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

std::vector<Clauses> Solver(std::vector<Clauses> KB){
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

std::vector<Clauses> Incorporate(std::vector<Clauses> S,std::vector<Clauses> KB){
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

std::vector<Clauses> Incorporate_clause(Clauses A,std::vector<Clauses> KB){

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

int CardinalLess (Clauses A) {
    int cardinalA = 0;
    cardinalA =  A.pos.size()+ A.neg.size();
    return  cardinalA;
}

std::vector<Clauses> UnionClauses(Clauses A,std::vector<Clauses> KB){
    std::vector<Clauses> Res;
    for(Clauses B: KB){
        if(A == B){
            Res.push_back(A);
        }
    }
    return Res;
}