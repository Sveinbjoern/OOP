#pragma once
#include "Helpers.h"


class Product;


class OrderBookEntry
{
    public: // parts of the class that can be seen from outside
    
    OrderBookEntry() = default;

    OrderBookEntry( std::string _dateTimeString,
                    Product _firstProduct,
                    Product _secondProduct,
                    HelpersNameSpace::OrderBookType _typeOfEntry,
                    double _price, 
                    double _amount);

    
    
    //numeric data
    double price; 
    double amount;
    
    //Date values
    std::string dateTimeString;

    //Meta dat
    HelpersNameSpace::OrderBookType typeOfEntry;
    Product firstProduct;
    Product secondProduct;


};