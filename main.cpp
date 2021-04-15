#include <iostream>
#include <fstream>
#include "Edge.hpp"
#include "Slitherlink.hpp"
#include "Zdd.hpp"

template <typename T>
void printFamily(Family<T>& f) {
    std::cout << "[\n";
    for (auto s : f) {
        std::cout << "  {";
        for (auto e : s) {
            std::cout << e << ", ";
        }
        std::cout << "}\n";
    }
    std::cout << "]" << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Expected <exe> <slitherlink_file>" << std::endl;
        exit(1);
    }
    std::ifstream slitherlink_in;
    slitherlink_in.open(argv[1]);
    Slitherlink s(slitherlink_in);
    Family<Edge> f = s.generateFamily();
    printFamily(f);

    return 0;
}
