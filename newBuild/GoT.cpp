#include <iostream>
#include <vector>
#include <string>
#include "src\GameOfTrades.h"

// using namespace std;
  
int main(int argc, char *argv[])
{     

    std::vector<int> barmaid;
    std::vector<std::string> barmaid2;
    std::string faulty;
    faulty.append("asdfs");
    std::cout << faulty << "/n";
    barmaid.push_back(23423);
    // barmaid2.push_back(faulty);

    // std::cout << barmaid[0];
    GameOfTrades GoT{};
    GoT.init();
    return 0;
}

#include "src\GameOfTrades.cpp"
#include "src\CSVReader.cpp"



    // std::string start;
    // std::string csvLine = "";
    // char separator = ',';

    // start = csvLine.find_first_not_of(separator, 0);

    // std::cout << start << std::endl;


   
    // OrderBook orderbook;
    // CSVReader::readDocumentLineByLine("data\\20200317T3.csv", orderbook );