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
        return (pos == right.pos && neg == right.neg);

    }

    bool operator!=(Clauses right) const {
        return !(pos == right.pos && neg == right.neg);
    }

    bool operator<(Clauses right) const {
        return (pos < right.pos && neg < right.neg);
    }


    std::vector<std::string> neg;
    std::vector<std::string> pos;
};


//Functions
std::vector<Clauses> Solver(std::vector<Clauses> KB);

std::vector<Clauses> Incorporate(std::vector<Clauses> S, std::vector<Clauses> KB);

std::vector<Clauses> Incorporate_clause(Clauses A, std::vector<Clauses> KB);

Clauses resolution(Clauses A, Clauses B);

std::ostream &operator<<(std::ostream &out, Clauses &c);

std::vector<Clauses> removeDuplicates(std::vector<Clauses> &KB);

void display(std::vector<Clauses> KB);

std::vector<std::string> GetIntersection(std::vector<std::string> A, std::vector<std::string> B);

std::vector<std::string> GetUnion(std::vector<std::string> A, std::vector<std::string> B);

int main() {
    srand(time(NULL));
    Clauses A = Clauses({"sun", "money"}, {"ice"});
    Clauses B = Clauses({"money"}, {"ice", "movie"});
    Clauses C = Clauses({"movie"}, {"money"});
    Clauses D = Clauses({"movie", "ice"}, {});
    Clauses E = Clauses({}, {"movie"});

    std::vector<Clauses> KB = {A, C, D, E};
    KB = Solver(KB);

    return 0;
}


Clauses resolution(Clauses A, Clauses B) {

    std::vector<std::string> IntersectionApBn = GetIntersection(A.pos, B.neg);
    std::vector<std::string> IntersectionAnBp = GetIntersection(A.neg, B.pos);

    if (IntersectionApBn.size() == 0 && IntersectionAnBp.size() == 0) {
        return Clauses();
    }

    if (IntersectionApBn.size() != 0) {
        int randIndex = rand() % IntersectionApBn.size();
        std::string a = IntersectionApBn.at(randIndex);

        A.pos.erase(std::remove(A.pos.begin(), A.pos.end(), a), A.pos.end());
        B.neg.erase(std::remove(B.neg.begin(), B.neg.end(), a), B.neg.end());

    } else {
        int randIndex = rand() % IntersectionAnBp.size();
        std::string a = IntersectionAnBp.at(randIndex);

        A.neg.erase(std::remove(A.neg.begin(), A.neg.end(), a), A.neg.end());
        B.pos.erase(std::remove(B.pos.begin(), B.pos.end(), a), B.pos.end());
    }

    Clauses C;
    std::vector<std::string> UnionApBp = GetUnion(A.pos, B.pos);
    std::vector<std::string> UnionAnBn = GetUnion(A.neg, B.neg);


    C.pos = UnionApBp;
    C.neg = UnionAnBn;

    std::vector<std::string> IntersectionCpCn = GetIntersection(C.pos, C.neg);
    if (IntersectionCpCn.size() != 0) {
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

        for (int i = 0; i < KB.size() - 1; i++) {
            for (int j = i + 1; j < KB.size(); j++) {

                Clauses C = resolution(KB.at(i), KB.at(j));

                if (C.pos.size() > 0 || C.neg.size() > 0) {
                    S.push_back(C);
                }
            }
        }
        S = removeDuplicates(S);
        if (S.size() == 0) {

            return KB;
        }

        std::cout <<"S =  " ;
        display(S);
        std::cout << std::endl;

        //Incorporate S in KB
        KB = removeDuplicates(KB);
        KB = Incorporate(S, KB);
        std::cout << std::endl;

        std::cout << "KB =  " ;

        display(KB);
        std::cout << std::endl;
    }while(KBDot != KB);
}

std::vector<Clauses> Incorporate(std::vector<Clauses> S, std::vector<Clauses> KB) {
    for (auto A: S) {
        KB = Incorporate_clause(A, KB);
    }
    return KB;
}

std::vector<Clauses> Incorporate_clause(Clauses A, std::vector<Clauses> KB) {

    for (auto it = KB.begin(); it != KB.end();) {
        Clauses intersectionA_B;
        intersectionA_B.pos = GetIntersection(A.pos, it->pos);
        intersectionA_B.neg = GetIntersection(A.neg, it->neg);

        if (intersectionA_B.pos == it->pos && intersectionA_B.neg == it->neg) {
            return KB;
        }

        if (intersectionA_B == A) {
            it = KB.erase(it);
        } else {
            it++;
        }
    }
    KB.push_back(A);
    return KB;
}

std::vector<Clauses> removeDuplicates(std::vector<Clauses> &KB) {
    std::sort(KB.begin(), KB.end());
    KB.erase(std::unique(KB.begin(), KB.end()), KB.end());
    return KB;
}

std::ostream &operator<<(std::ostream &out, Clauses &c) {

    if (c.pos.size() == 0 && c.neg.size() == 0) {
        out << "false" << std::endl;
    } else {
        for (int i = 0; i < c.pos.size(); i++) {
            out << c.pos.at(i);
            if (i != c.pos.size() - 1) {
                out << " V ";
            }
        }

        if (c.neg.size() > 0 && c.pos.size() > 0) {
            out << " V ";
        }

        for (int i = 0; i < c.neg.size(); i++) {
            out << "-" << c.neg.at(i);
            if (i != c.neg.size() - 1) {
                out << " V ";
            }
        }

    }
    return out;
}

void display(std::vector<Clauses> KB) {
    std::cout<<"{";
    for (int i = 0; i < KB.size(); i++) {
        std::cout << KB.at(i)<< ", ";
    }
    std::cout<<"}";
}

std::vector<std::string> GetIntersection(std::vector<std::string> A, std::vector<std::string> B) {
    std::vector<std::string> intersection;
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), std::back_inserter(intersection));
    return intersection;
}

std::vector<std::string> GetUnion(std::vector<std::string> A, std::vector<std::string> B) {
    std::vector<std::string> intersection;
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    std::set_union(A.begin(), A.end(), B.begin(), B.end(), std::back_inserter(intersection));
    return intersection;
}