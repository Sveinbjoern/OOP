#include "Helpers.h"


Product::Product(std::string s, OrderBook& orderBook, bool add)
{
    if (add)
    {
        orderBook.addToSetOfProducts(s);
        type = s;
    } else
    {
        if (orderBook.isInSetOfProducts(s))
        {
            type = s;
        } else{
            throw std::invalid_argument( s.append( " is not a valid product. Product::Constructor") );
        }
    }
    
}



// #include <type_traits>

// std::ostream& operator<< (std::ostream& os, const HelpersNameSpace::OrderBookType& obj )
// {

//     if (static_cast<underlying_type<HelpersNameSpace::OrderBookType>::type>(obj) == 0)
//     {
//         os << "OrderBookType::ask";
//     } else if (static_cast<underlying_type<HelpersNameSpace::OrderBookType>::type>(obj) == 1)
//     {
//         os << "OrderBookType::bid"; 
//     } else
//     {
//         os << "Not valid OrderBookType";
//     }
// };
