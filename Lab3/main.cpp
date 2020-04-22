#include <iostream>
#include <vector>

class Clauses{
public:
    Clauses(){}
    Clauses(std::vector<std::string>  negative, std::vector<std::string> positive): neg(negative), pos(positive){}
    ~Clauses() = default;
private:
    std::vector<std::string> neg;
    std::vector<std::string> pos;
};

int main() {


    return 0;
}
