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
        if (pos == right.pos && neg == right.neg) {
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
std::ostream &operator<<(std::ostream &out, Clauses &c);
std::vector<Clauses> removeDuplicates(std::vector<Clauses> KB);
void display(std::vector<Clauses> KB);
std::vector<std::string> GetIntersection(std::vector<std::string> A, std::vector<std::string> B);
std::vector<std::string> GetUnion(std::vector<std::string> A, std::vector<std::string> B);

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


Clauses resolution(Clauses A, Clauses B) {

    std::vector<std::string> IntersectionApBn = GetIntersection(A.pos,B.neg);
    std::vector<std::string> IntersectionAnBp = GetIntersection(A.neg,B.pos);

    if (IntersectionApBn.size() == 0 && IntersectionAnBp.size() == 0 ) {
        return Clauses();
    }

    if (IntersectionApBn.size() != 0) {
        int randIndex = rand() % IntersectionApBn.size();
        std::string a = IntersectionApBn.at(randIndex);

        A.pos.erase(std::remove(A.pos.begin(),  A.pos.end(), a), A.pos.end());
        B.neg.erase(std::remove(B.neg.begin(),  B.neg.end(), a), B.neg.end());

    }
    else {
        int randIndex = rand() % IntersectionAnBp.size();
        std::string a = IntersectionAnBp.at(randIndex);

        A.neg.erase(std::remove(A.neg.begin(),  A.neg.end(), a), A.neg.end());
        B.pos.erase(std::remove(B.pos.begin(),  B.pos.end(), a), B.pos.end());
    }

    Clauses C;
    std::vector<std::string> UnionApBp = GetUnion(A.pos,B.pos);
    std::vector<std::string> UnionAnBn = GetUnion(A.neg,B.neg);


    C.pos = UnionApBp;
    C.neg = UnionAnBn;


    std::vector<std::string> IntersectionCpCn = GetIntersection(C.pos,C.neg);
    if(IntersectionCpCn.size() != 0){
        return Clauses();
    }

    sort(C.pos.begin(), C.pos.end());
    sort(C.neg.begin(), C.neg.end());

    C.pos.erase(unique(C.pos.begin(), C.pos.end()), C.pos.end());
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
                
                if(C.pos.size() != 0 || C.neg.size() != 0 ){
                        S.push_back(C);
                }

            }
        }
        if (S.empty()){
            return KB;
        }

        std::cout <<std::endl<<"This is S in do: "<<std::endl;
        display(S);
        std::cout <<std::endl;

        //Incorporate S in KB
        KB = Incorporate(S, KB);

        std::cout <<"This is KB after incorporate: "<<std::endl;
        display(KB);
    } while (KBDot != KB);

}

std::vector<Clauses> Incorporate(std::vector<Clauses> S, std::vector<Clauses> KB) {

    for (auto A: S) {
        KB = Incorporate_clause(A, KB);
    }
    return KB;
}

std::vector<Clauses> Incorporate_clause(Clauses A, std::vector<Clauses> KB) {
    for (Clauses B:KB) {
        Clauses Comb;
        Comb.pos = GetIntersection(B.pos,A.pos);
        Comb.neg = GetIntersection(B.neg,A.neg);
        if (Comb.pos == A.pos && Comb.neg == A.neg) {
            return KB;
        }
    }

    for (Clauses B: KB) {
        Clauses aCombined;
        aCombined.pos = GetIntersection(A.pos,B.pos);
        aCombined.neg = GetIntersection(A.neg,B.neg);

        size_t orgP = B.pos.size();
        size_t orgN = B.neg.size();
        size_t size1 = aCombined.pos.size();
        size_t size2 = aCombined.neg.size();

        if ((aCombined.pos == A.pos && aCombined.neg == A.neg) && (size1 <orgP || size2 <orgN)) {
          KB.erase(std::remove(KB.begin(),KB.end(),B),KB.end());
        }
    }
    if (std::find(KB.begin(), KB.end(), A) == KB.end()){
        KB.push_back(A);
    }


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

std::vector<std::string> GetIntersection(std::vector<std::string> A, std::vector<std::string> B){
    std::vector<std::string> intersection;
    std::sort(A.begin(),A.end());
    std::sort(B.begin(),B.end());
    std::set_intersection(A.begin(),A.end(),B.begin(),B.end(),std::back_inserter(intersection));
    return intersection;
}

std::vector<std::string> GetUnion(std::vector<std::string> A, std::vector<std::string> B){
    std::vector<std::string> intersection;
    std::sort(A.begin(),A.end());
    std::sort(B.begin(),B.end());
    std::set_union(A.begin(),A.end(),B.begin(),B.end(),std::back_inserter(intersection));
    return intersection;
}