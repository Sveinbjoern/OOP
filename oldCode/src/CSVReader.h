#pragma once

#include <vector>
#include <string>


class OrderBook;
class OrderBookType;

/** Reads lines from a csv document and can tokenize strings and return Orderbook entries (OBE).
 * Only contains static functions, and does not store any data itself.
*/
class CSVReader
{
    public:


    
    /** Takes a line, checks that it has valid data and return an OrderBookEntry(OBE)
     * arg1: Line to analyze
     * arg2: String with name of document to handle
     * arg3: set of strings of products
     * arg4: bool whether you want to add the products to setOfProdcuts or you want to check if the item is in setOfProducts
     * arg4 cont.: If add is true: Valid entries will add to products to setOfProducts. 
     * If add is false: Products will be tested if they belong to setOFProducts before creation of OBE  
    */
    static OrderBookEntry CheckValidData__ParseOBE(std::string& line,  const std::string& documentName, OrderBook& orderBook, const bool add);

    
    /** Create a vector of strings from a string seperated by a char
     * arg1: String to tokenize
     * arg2: char seperator
    */
    static std::vector<std::string> tokenize(std::string& csvLine, const char separator);
    
    /** Read the document line by line and parse the input to valid OrderBookEntries in orderBook
     * arg1: string document name
     * arg2: orderbook to store procucts and OrderBook entries
     */
    static void readDocumentLineByLine(const std::string& documentName, OrderBook& orderBook);

    
    private:

    
    

    
};