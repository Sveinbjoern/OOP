#include "OrderBookEntry.h"



//When intiated the values are stored in the new entry object with this constructor
OrderBookEntry::OrderBookEntry( std::string _dateTimeString,
                                Product _product,
                                HelpersNameSpace::OrderBookType _typeOfEntry,
                                double _price, 
                                double _amount,
                                bool _playerOwned)
:   dateTimeString(_dateTimeString), 
    product(_product),
    typeOfEntry(_typeOfEntry),
    price(_price), 
    amount(_amount), 
    playerOwned(_playerOwned)
{

}

