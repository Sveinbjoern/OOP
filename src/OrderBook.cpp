#include <iostream>
#include "OrderBook.h"


OrderBook::OrderBook(const std::string& filename)
{
    CSVReader::readDocumentLineByLine( filename, *this );
    
    // "data\\20200317T3.csv"
}


void OrderBook::addToSetOfProducts(OrderBook& orderBook,std::string s)
{
    orderBook.addToSetOfProducts(s);
}

void OrderBook::addToSetOfProducts(std::string s)
{
    setOfProducts.insert(s);
}

bool OrderBook::isInSetOfProducts( std::string s)
{
    return (setOfProducts.find(s) != setOfProducts.end());
}

void OrderBook::printSetOfProducts()
{
    std::cout << "All the possible product types:" << std::endl;
    for(setIterator = setOfProducts.begin(); setIterator != setOfProducts.end() ; ++setIterator) 
        {
            // if (*setIterator != "INVALID/INPUT")
            std::cout << *setIterator << std::endl; // Note the "*" here
        } 
}

void OrderBook::loadCurrentEntries()
{
    //get values from entries
}

void OrderBook::addOrderBookEntry( OrderBookEntry& entry)
{
    orders.push_back(entry);
}