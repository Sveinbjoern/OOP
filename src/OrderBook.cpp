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
std::vector<std::string> OrderBook::getVectorOfProducts()
{
    std::vector<std::string> returnVector;
    for(setIterator = setOfProducts.begin(); setIterator != setOfProducts.end() ; ++setIterator) 
    {
        returnVector.push_back(*setIterator);
    } 
    return returnVector;
}

void OrderBook::loadCurrentEntries()
{
    //get values from entries
}

void OrderBook::addOrderBookEntry( OrderBookEntry entry)
{
    orders.push_back(entry);
}

void OrderBook::setupOrderbook()
{
    if (!setup)
    {
        // std::cout << orders.size() << std::endl;
        // for (OrderBookEntry x :orders)
        // {
        //     std::cout << x.dateTimeString ;
        // }
        currentTime = orders[0].dateTimeString;

        std::cout << "first timestep is " << currentTime << std::endl;
        currentEntryIndex = 0;
       

        
        //test the order of dataTimeStrings
        std::string testString = orders[0].dateTimeString;
        int length = orders.size();
        int greater = 0;
        int smaller = 0;
        for (int i = 0; i < length; ++i)
        {
            std::string currentDTString = orders[i].dateTimeString;
            if (testString > currentDTString)
            {
                ++ greater;
            } else
            {
                ++smaller;
            }
            if (testString > currentDTString)
            {
                std::cout << "Error: wrong order of dateTime string at order number " << i <<  std::endl;
                std::cout << "DateTime string should always be getting larger." << std::endl;
                std::cout << "Program will not function properly." << std::endl;

            } else
            {
                testString = currentDTString;
            }
        }
        std::cout << "Times that dateTime string was in incorrect order. Should be zero: " << greater <<  std::endl;
        std::cout << "Times that dateTime string was in correct order: " << smaller <<  std::endl;
        

        while (currentTime == orders[currentEntryIndex].dateTimeString)
        {
            if (orders[currentEntryIndex].typeOfEntry == HelpersNameSpace::OrderBookType::ask)
            {
                currentAsks.push_back(orders[currentEntryIndex]);
            } else
            {
                currentBids.push_back(orders[currentEntryIndex]);
            }
            ++currentEntryIndex;
        }
        
        std::cout << "Size of currentBids: " << currentBids.size() <<  std::endl;
        std::cout << "Size of currentAsks: " << currentAsks.size() <<  std::endl;
     
        // std::vector<OrderBookEntry> currentBids;
        // std::vector<OrderBookEntry> currentAsks;

        setup = true;
    } else
    {
        std::cout << "Error: Setup cannot be run more than once!" << std::endl;
    }

    // std::cout << "first dateTimeSting" << orders[0].dateTimeString << std::endl;
    // std::cout << "laterTimeSting" << orders[500].dateTimeString << std::endl;
    // std::cout << "evenLaterTimeSting" << orders[2000].dateTimeString <<std::endl;
    
    // std::cout << "firstdateTimeSting < laterTimeString" << (orders[0].dateTimeString < orders[500].dateTimeString)  << std::endl;
    // std::cout << "firstTimeSting < evenLaterTimeString" << (orders[0].dateTimeString < orders[2000].dateTimeString) <<std::endl;
    // std::cout << "laterTimeSting < evenlaterTimeString" << (orders[500].dateTimeString < orders[2000].dateTimeString ) << std::endl;
   
    // std::cout << "firstdateTimeSting > laterTimeString" << (orders[0].dateTimeString > orders[500].dateTimeString)  << std::endl;
    // std::cout << "firstTimeSting > evenLaterTimeString" << (orders[0].dateTimeString > orders[2000].dateTimeString) <<std::endl;
    // std::cout << "laterTimeSting > evenlaterTimeString" << (orders[500].dateTimeString > orders[2000].dateTimeString ) << std::endl;

}

int OrderBook::orderCount()
{
    return orders.size();
}