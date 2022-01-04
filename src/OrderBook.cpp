#include <iostream>
#include "OrderBook.h"


OrderBook::OrderBook(const std::string& filename)
{
    CSVReader::readDocumentLineByLine( filename, *this );
    
    // "data\\20200317T3.csv"
}


void OrderBook::addToSetOfProducts(OrderBook& orderBook,std::string s)
{
    if (!orderBook.get_setupHasRun())
    {
        orderBook.addToSetOfProducts(s);
    } else
    {
    
    }
    
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

double OrderBook::getHighOrLowPriceBid(std::string &minOrMax, Product &Pone, Product &Ptwo)
{
    
    if (minOrMax == "MIN")
    {
        //set the price to zero so that any price will be higher
        double min = std::numeric_limits<double>::infinity();
        for (OrderBookEntry x : currentBids)
        {
            if (x.firstProduct.get_type() == Pone.get_type())
            {
                if (x.secondProduct.get_type() == Ptwo.get_type())
                {
                    std::cout << "firstProduct " << x.firstProduct.get_type() << " secondProduct " << x.secondProduct.get_type() << std::endl;
                    // std::cout << x.price << std::endl;
                    if (x.price < min)
                    {
                        min = x.price;
                    }
                }
            }

        }
        return min;
    } else if (minOrMax == "MAX")
    {
        //set the max value to an extreme so that any actual price will be lower
        double max = 0.0;
        for (OrderBookEntry x : currentBids)
        {
            if (x.firstProduct.get_type() == Pone.get_type())
            {
                if (x.secondProduct.get_type() == Ptwo.get_type())
                {
                    // std::cout << x.price << std::endl;
                    if (x.price > max)
                    {
                        std::cout << "firstProduct " << x.firstProduct.get_type() << " secondProduct " << x.secondProduct.get_type() << std::endl;
                        max = x.price;
                    }
                }
            }

        }
        return max;
    } else
    {
        std::cout << "Error. Wrong \"minOrMax\" element passed to OrderBook::getHighOrLowPriceAsk" << std::endl;
        return 0.0;
    }
}

double OrderBook::getHighOrLowPriceAsk(std::string& minOrMax, Product& Pone, Product& Ptwo)
{
    if (minOrMax == "MIN")
    {
        double min = std::numeric_limits<double>::infinity();
        std::cout << "less than infinity " << ( 9999999999999 < min);
        for (OrderBookEntry x : currentAsks)
        {
            if (x.firstProduct.get_type() == Pone.get_type())
            {
                if (x.secondProduct.get_type() == Ptwo.get_type())
                {
                    // std::cout << x.price << std::endl;
                    if (x.price < min)
                    {
                        std::cout << "firstProduct " << x.firstProduct.get_type() << " secondProduct " << x.secondProduct.get_type() << std::endl;
                        min = x.price;
                    }
                }
            }

        }
        return min;
    } else if (minOrMax == "MAX")
    {
        double max = 0.0;
        
        
        
        

        // std::cout << "max value before funct: " << max << std::endl;
        // std::cout << "max > 999999999 value before f: " << (max > 999999999) << std::endl;

        // for (OrderBookEntry x : currentAsks)
        // {
        //     std::cout << "stored product:";
        //     std::cout << x.firstProduct.get_type();
        //     std::cout << x.secondProduct.get_type();
        // }

        for (OrderBookEntry x : currentAsks)
        {
            if (x.firstProduct.get_type() == Pone.get_type())
            {
                if (x.secondProduct.get_type() == Ptwo.get_type())
                {
                    // std::cout << x.price << std::endl;
                    if (x.price > max)
                    {
                        std::cout << "firstProduct " << x.firstProduct.get_type() << " secondProduct " << x.secondProduct.get_type() << std::endl;
                        max = x.price;
                    }
                }
            }

        }
         std::cout << "max value after funct: " << max << std::endl;
        return max;
    } else
    {
        std::cout << "Error. Wrong \"minOrMax\" element passed to OrderBook::getHighOrLowPriceAsk" << std::endl;
        return 0.0;
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
    if (!setupHasRun)
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

        setupHasRun = true;
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

bool OrderBook::get_setupHasRun()
{
    return setupHasRun;
}