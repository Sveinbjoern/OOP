#pragma once

#include <vector>
#include <string>

/*
    The class implementations are there to resolve a loop of includes where
    several files includes eachother. This solution simply creates a promise
    to the compiler that there will be a class, but does not include anything.
*/
// class OrderBook;
// class OrderBookType;
// class OrderBookEntry;

/** Reads lines from a csv document and can tokenize strings and return Orderbook entries (OBE).
 * Only contains static functions, and does not store any data itself.
*/
class CSVReader
{
    public:


    
    /** Takes a line, checks that it has valid data and return an OrderBookEntry(OBE)
     * arg1: Line to analyze
     * arg2: Reference to the Orderbook you want to add the OrderBookEntry to
     * arg3: bool whether you want to add the products to setOfProdcuts or you want to check if the item is in setOfProducts
     * arg4 cont.: If add is true: Valid entries will add to products to setOfProducts. 
     * If add is false: Products will be tested if they belong to setOFProducts before creation of OBE
     * arg5: userBool decides if user  
    */
    // static OrderBookEntry parseOrderBookEntry(std::string& line, OrderBook& orderBook, const bool add, const bool userBool);

    
    /** Create a vector of strings from a string seperated by a char
     * arg1: String to tokenize
     * arg2: char seperator
    */
    static std::vector<std::string> tokenize(std::string& csvLine, const char separator);
    
    /** Read the document line by line and parse the input to valid OrderBookEntries in orderBook
     * arg1: string document name
     * arg2: orderbook to store procucts and OrderBook entries
     */
    // static void readDocumentLineByLine(const std::string& documentName, OrderBook& orderBook);

    
    private:

   
    // static void addToVector(std::vector<std::string> &tokens, const std::string &token);

    
};