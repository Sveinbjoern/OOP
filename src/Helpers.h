#pragma once
#include <iostream>
#include <type_traits>
#include <set>
#include <string>
#include <algorithm>


class OrderBook;

// /** Inputmanager takes care of user and data inputs
//  * Stored in Helpers.h
// */
// class InputManager
// {
//     public:
    
    
// };


/** Class product creates objects that store valid product string
 * In file: Helpers.h
 */
class Product
{
        std::string type;
    public:
    

        Product(std::string s, OrderBook& orderBook, bool add);

        Product() = default; 
        

        friend std::ostream& operator<<(std::ostream& os, const Product& pr); 
};

std::ostream& operator<<(std::ostream& os, const Product& pr)
{
    os << pr.type;
    return os;
}


/** Namespace for data to be shared across the program instead of it having global scope 
 * Stored in Helpers.h
*/
namespace dataSpace
{
    
    /**The enum OrderBookType available for every part of the app. Underlying values: ask: 0, bid:1 */
    enum class OrderBookType{ask,bid};


    // From https://stackoverflow.com/questions/8888748/how-to-check-if-given-c-string-or-char-contains-only-digits
    bool is_digits(const std::string &str)
    {
        return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
    }
};



/** ostream operator overload */ 
std::ostream& operator<< (std::ostream& os, const dataSpace::OrderBookType& obj )
{
    // std::cout << static_cast<std::underlying_type<dataSpace::OrderBookType>::type>(obj) << std::endl;
    if (static_cast<std::underlying_type<dataSpace::OrderBookType>::type>(obj) == 0)
    {
        os << "OrderBookType::ask";
        return os;
    } else if (static_cast<std::underlying_type<dataSpace::OrderBookType>::type>(obj) == 1)
    {
        os << "OrderBookType::bid"; 
        return os;
    } else
    {
        os << "Not valid OrderBookType";
        return os;
    }
    return os;
};

