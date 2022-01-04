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
    

        Product(std::string s, OrderBook& orderBook);
        
        void set(std::string s, OrderBook& orderBook);

        Product() = default; 
        
        std::string get_type();

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
namespace HelpersNameSpace
{
    
    /**The enum OrderBookType available for every part of the app. Underlying values: ask: 0, bid:1 */
    enum class OrderBookType{ask,bid};

    /**
     * @brief Takes a string and transforms it to an upper case version
     * Adapted from https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case:
     */
    void toUpper(std::string &string)
    {
        // std::cout << string << "from toUpper" <<std::endl;
        std::transform(string.begin(), string.end(), string.begin(),
        [](unsigned char c){ return std::toupper(c); });
    }

    // From https://stackoverflow.com/questions/8888748/how-to-check-if-given-c-string-or-char-contains-only-digits
    bool is_digits(const std::string &str)
    {
        return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
    }

    /**Convert a double to string with greater precission than to_stirng
        https://stackoverflow.com/questions/20196351/convert-double-to-string-keeping-high-precision-of-the-digits-c/20215087*/
    std::string doubleToStringPresicion(const double & value)
    {
        //Original code
        // double digits = 1.12345123451234;
        // char buff[100];
        // sprintf(buff, "%1.14f", digits);
        // std::string a(buff);
    
        
        char buff[100];
        sprintf(buff, "%1.14f", value);
        std::string returnString(buff);
        // if (returnString.back() == '0')
        // {
             returnString.erase( returnString.find_last_not_of('0')+1, returnString.size()-1);
        // }
        if (returnString.back() == '.')
        {
            returnString.erase(returnString.size()-1);
        }
        return returnString;

    }
};



/** ostream operator overload 
 * makes it so that std::cout prints out a message giving a string of what kind of orderbooktype*/ 
std::ostream& operator<< (std::ostream& os, const HelpersNameSpace::OrderBookType& obj )
{
    // std::cout << static_cast<std::underlying_type<HelpersNameSpace::OrderBookType>::type>(obj) << std::endl;
    if (static_cast<std::underlying_type<HelpersNameSpace::OrderBookType>::type>(obj) == 0)
    {
        os << "OrderBookType::ask";
        return os;
    } else if (static_cast<std::underlying_type<HelpersNameSpace::OrderBookType>::type>(obj) == 1)
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

