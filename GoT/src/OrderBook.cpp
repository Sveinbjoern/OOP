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

double OrderBook::getHighOrLowPriceBid(std::string &minOrMax, Product &product)
{
    n = 0;
    
    if (minOrMax == "MIN")
    {
        //set the price to zero so that any price will be higher
        double min = std::numeric_limits<double>::infinity();
        for (OrderBookEntry x : currentBids)
        {
            if (x.product.get_type() == product.get_type())
            {
                ++n;
                    // std::cout << x.price << std::endl;
                    if (x.price < min)
                    {
                        // std::cout << "Product " << x.product.get_type() << std::endl;
                        min = x.price;
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
            // std::cout << "Prod == prod" << product.get_type() << std::endl;
            if (x.product.get_type() == product.get_type())
            {
                ++n;
                    // std::cout << x.price << std::endl;
                    if (x.price > max)
                    {
                        // std::cout << "Product " << x.product.get_type() << std::endl;
                        max = x.price;
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

double OrderBook::getHighOrLowPriceAsk(std::string& minOrMax,  Product &product)
{
    n = 0;
    if (minOrMax == "MIN")
    {
        double min = std::numeric_limits<double>::infinity();
        // std::cout << "less than infinity " << ( 9999999999999 < min);
        for (OrderBookEntry x : currentAsks)
        {
            if (x.product.get_type() == product.get_type())
            {
                ++n;
                    // std::cout << x.price << std::endl;
                    if (x.price < min)
                    {
                        // std::cout << "Product " << x.product.get_type() << std::endl;
                        min = x.price;
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
            //  std::cout << "Product " << x.product.get_type() << std::endl;
            if (x.product.get_type() == product.get_type())
            {
                ++n;
                
                    // std::cout << x.price << std::endl;
                    if (x.price > max)
                    {
                        // std::cout << "Product " << x.product.get_type() << std::endl;
                        max = x.price;
                    }
                
            }

        }
        
        //  std::cout << "max value after funct: " << max << std::endl;
         
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



std::string OrderBook::matchEntries()
{
    
    //Adapted from starterCode
    std::string returnString;
     if (currentAsks.size() == 0 | currentBids.size() == 0)
    {
        returnString = "OrderBook::matchAsksToBids no bids or asks\n";
        return returnString;
    } 
    


        std::vector<std::string> products = getVectorOfProducts();
        int size = products.size();
        // std::vector<std::vector<OrderBookEntry>> bids;  
        // std::vector<std::vector<OrderBookEntry>> asks;

        std::vector< std::vector <OrderBookEntry> > asks;
        std::vector< std::vector <OrderBookEntry> > bids;

        for ( std::string x : products)
        {
             std::vector <OrderBookEntry> temp1;
             asks.push_back(temp1);
             std::vector <OrderBookEntry> temp2;
             bids.push_back(temp2);
        }

        for(OrderBookEntry entry : currentAsks)
        {
            for (int i = 0; i < size; ++i)
            {

                if (entry.product.get_type() == products[i])
                {
                    asks[i].push_back(entry);
                    break;
                }
            }    
        }
        // std::cout << asks[0][0].dateTimeString << std::endl;

        for(OrderBookEntry entry : currentBids)
        {
            for (int i = 0; i < size; ++i)
            {
                if (entry.product.get_type() == products[i])
                {
                    bids[i].push_back(entry);
                    break;
                }
            }
            
        }
        // int amount = 0;

         for (int i = 0; i < size; ++i)
            {
                std::sort(bids[i].begin(), bids[i].end(), OrderBook::compareDescending);
                // for (OrderBookEntry entry : bids[i]  )
                // {
                    
                //     ++amount;
                //     std::cout << entry.price << " ";
                // }

                std::sort(asks[i].begin(), asks[i].end(), OrderBook::compareAscending);
                //  for (OrderBookEntry entry : asks[i]  )
                // {
                    
                //     ++amount;
                //     std::cout << entry.price << " ";
                // }

            }
        int trades = 0;
        for (int i = 0; i < size;++i)
        {
            while (bids[i][0].price >= asks[i][0].price)
            {
                ++trades;
                if (bids[i][0].amount  == asks[i][0].amount )
                {
                    if (bids[i][0].playerOwned)
                    {
                        //Wallet stuff
                    }
                    if (asks[i][0].playerOwned)
                    {
                        //Wallet stuff
                    }
                    bids[i].erase(bids[i].begin());
                    asks[i].erase(asks[i].begin());
                    if (bids[i].size() == 0 | asks[i].size() == 0)
                    {
                        break;
                    }

                } else if (bids[i][0].amount  < asks[i][0].amount )
                {
                     if (bids[i][0].playerOwned)
                    {
                        //Wallet stuff
                    }
                    if (asks[i][0].playerOwned)
                    {
                        //Wallet stuff
                    }
                    asks[i][0].amount -= bids[i][0].amount;
                    bids[i].erase(bids[i].begin());
                    if (bids[i].size() == 0 | asks[i].size() == 0)
                    {
                        break;
                    }

                } else
                {
                     if (bids[i][0].playerOwned)
                    {
                        //Wallet stuff
                    }
                    if (asks[i][0].playerOwned)
                    {
                        //Wallet stuff
                    }
                    bids[i][0].amount -= asks[i][0].amount;
                    asks[i].erase(asks[i].begin());
                    if (bids[i].size() == 0 | asks[i].size() == 0)
                    {
                        break;
                    }

                }
            }
        }
        
        // std::cout << amount << " ";

        // for (std::vector<OrderBookEntry>::iterator it=currentAsks.begin(); it!=currentAsks.end(); ++it)
        // {
        //     std::cout << " " << it->price;
        //     std::cout << '\n';
        // }
        
        
        // for (int i = 0; i < currentAsks.size(); ++i)  
        // {
        //     std::string product = currentAsks[i].product.get_type();
        //     for (OrderBookEntry& bid : currentBids)
        //     {
        //         // if (bid.product.get_type() == product)
        //         // {
        //         //     if (bid.price >= ask.price)
        //         //     {
                        

        //         //     } else
        //         //     {
        //         //         ++i;
        //         //         break;
        //         //     }
        //         // }
        //     }
        // }
        return returnString;
    
}

bool OrderBook::compareAscending (OrderBookEntry& entry1,OrderBookEntry& entry2) 
{ return (entry1.price < entry2.price); }

bool OrderBook::compareDescending (OrderBookEntry& entry1,OrderBookEntry& entry2) 
{ return (entry1.price > entry2.price); }


void OrderBook::loadCurrentEntries()
{
    //get values from entries

    // std::string currentTimestep = orders[ ];
    int timestepIndex = *(std::next(allTimeStepsIndex.begin() , stepCounter ));
    int nextTimestepIndex;
    if (stepCounter >= allTimeStepsIndex.size()-1)
    {
        nextTimestepIndex = orders.size()-1;
    } else
    {
        nextTimestepIndex =  *(std::next(allTimeStepsIndex.begin() , stepCounter +1 ));
    }
    currentAsks.clear();
    currentBids.clear();

      while (timestepIndex++ != nextTimestepIndex)
        {
            if (orders[timestepIndex].typeOfEntry == HelpersNameSpace::OrderBookType::ask)
            {
                currentAsks.push_back(orders[timestepIndex]);
            } else
            {
                currentBids.push_back(orders[timestepIndex]);
            }
        }

}

void OrderBook::addOrderBookEntry( OrderBookEntry entry)
{
    if (!setupHasRun)
    {
         orders.push_back(entry);
    } else
    {
        std::cout << "Error: Setup has already been run. New entries no longer available." ;
    }
   
}

void OrderBook::setupOrderbook()
{
    if (!setupHasRun)
    {
        
        setupHasRun = true;
        // std::cout << orders.size() << std::endl;
        // for (OrderBookEntry x :orders)
        // {
        //     std::cout << x.dateTimeString ;
        // }
        
        stepCounter = 0;
        int currentEntryIndex = 0;
        
       
       

        
        //test the order of dataTimeStrings
        std::string testString = orders[0].dateTimeString;
        allTimeStepsString.insert(orders[0].dateTimeString);
        allTimeStepsIndex.insert(0);
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
                allTimeStepsString.insert(currentDTString);
            }
            if (testString > currentDTString)
            {
                std::cout << "Error: wrong order of dateTime string at order number " << i <<  std::endl;
                std::cout << "DateTime string should always be getting larger." << std::endl;
                std::cout << "Program will not function properly." << std::endl;

            } else
            {
                
                allTimeStepsString.insert(currentDTString);
                testString = currentDTString;
            }
        }
        std::cout << "Times that dateTime string was in incorrect order. Should be zero: " << greater <<  std::endl;
        std::cout << "Times that dateTime string was in correct order: " << smaller <<  std::endl;
        

        std::string firstTimestep = orders[0].dateTimeString;
        std::cout << "first timestep is " << firstTimestep << std::endl;
        

       

        std::string currentTimestep = *( std::next(allTimeStepsString.begin(),stepCounter));
        //Set currentEntryIndex to the step of the first currentTimestep 
        while ( currentTimestep !=  orders[currentEntryIndex].dateTimeString)
        {
            ++currentEntryIndex;
            /* code */
        }
        

        while (currentTimestep == orders[currentEntryIndex].dateTimeString)
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
     

        std::string timestep = orders[0].dateTimeString;
        int counter=0;
       //Create the set of allTimeStepIndex for every index change to  
        for (int i = 0; i < allTimeStepsString.size(); ++i)
        {
            allTimeStepsIndex.insert(counter);
            // std::cout << counter << " ";
            while ( timestep ==  orders[counter].dateTimeString)
            {
                ++counter;
                /* code */
            }
            timestep = orders[counter].dateTimeString;
        }


        // std::vector<OrderBookEntry> currentBids;
        // std::vector<OrderBookEntry> currentAsks;
        if (allTimeStepsString.size() ==  allTimeStepsIndex.size())
        {
            std::cout << "Number of timeSteps: " << allTimeStepsString.size() << std::endl;
        } else
        {
            std::cout << "Error in count of timesteps OrderBook::setupOrderBook() :" << std::endl;
            std::cout << "Two different counting methods of number of times do not correspond." << std::endl;
            std::cout << "Index count: " << allTimeStepsIndex.size();
            std::cout << " String count: " << allTimeStepsString.size() << std::endl;
            std::cout << "Program will not work as expected." << std::endl;

        }
        
        
        
        // for (int x : allTimeStepsIndex )
        // {

        //     std::cout << x << std::endl;
        //     // std::cout << *( std::next(allTimeStepsString.begin(),stepCounter)) << std::endl;
        // }
        // std::cout << *( std::next(allTimeStepsIndex.begin(),stepCounter)) << std::endl;
        


        
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


std::string OrderBook::getCurrentTimeString()
{
     return *( std::next(allTimeStepsString.begin(),stepCounter));
}
int OrderBook::getCurrentTimeNumberIndex()
{
    return stepCounter;
}
int OrderBook::getCurrentTimeNumberTotal()
{
    return allTimeStepsIndex.size();
}

std::string OrderBook::goToNextTimestep()
{
    ++stepCounter;
    std::string returnString;
    if (stepCounter >= allTimeStepsIndex.size())
    {
        //End simulation
        stepCounter = allTimeStepsIndex.size() -1;
        returnString = "Last timestep reached. Simulation has ended: returnValue:0";
        return returnString;
    } else
    {
        returnString = matchEntries();
        loadCurrentEntries();
        return returnString;
    }
    
}