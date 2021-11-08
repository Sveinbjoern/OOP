#include <iostream>
#include "OrderBook.h"


OrderBook::OrderBook()
{
    // OrderBookEntry order1 = OrderBookEntry {200,10,OrderBook::OrderBookType::ask,"fasdfs","SFD","GOFF"};
    // cout << "order1.amount: " << order1.amount <<endl;
    // cout << "order1.price: " << order1.price <<endl;

    // orders.push_back(
    //     OrderBookEntry{200,10,OrderBookType::ask,"fasdfs","SFD","GOFF"}
    // );
    
    // OrderBook::addToSetOfProducts("INVALID/INPUT");
    
    

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