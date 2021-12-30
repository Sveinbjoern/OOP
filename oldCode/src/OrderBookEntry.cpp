#include "OrderBookEntry.h"



//When intiated the values are stored in the new entry object with this constructor
OrderBookEntry::OrderBookEntry( std::string _dateTimeString,
                                Product _firstProduct,
                                Product _secondProduct,
                                HelpersNameSpace::OrderBookType _typeOfEntry,
                                double _price, 
                                double _amount)
:   dateTimeString(_dateTimeString), 
    firstProduct(_firstProduct), 
    secondProduct(_secondProduct),
    typeOfEntry(_typeOfEntry),
    price(_price), 
    amount(_amount) 
{

}

