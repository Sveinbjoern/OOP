#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <type_traits>


class OrderBookEntry;

class OrderBook
{
    public:

        
       
        
        

        
        /** Class constuctor*/
        OrderBook();

        /** static funciton that inserts an element to the setOfProducts of an orderbook 
         * arg1: The orderbook
         * arg2: The string to add
        */
        static void addToSetOfProducts(OrderBook& orderBook, std::string s);
        
        /** funciton that inserts an element to the setOfProducts of this objects orderbook 
         * arg1: The string to add
        */
        void addToSetOfProducts( std::string s);

        /** funciton that checks if a string is in the setOfProducts of this objects orderbook 
         * arg1: The string to check
        */
        bool isInSetOfProducts( std::string s);

        /** funciton that checks if a string is in the setOfProducts of this objects orderbook 
         * arg1: The string to check
        */
        void printSetOfProducts();
        
        /** Load the set of currentBids and currentAsks for the currentTime
         * Should be loaded once every time movement.
        */
        void loadCurrentEntries();

        /** Put an order in the private orders vector*/
        void addOrderBookEntry( OrderBookEntry& entry);

    private:
       // Set of all stored values
        std::vector<OrderBookEntry> orders;
        std::vector<OrderBookEntry> currentBids;
        std::vector<OrderBookEntry> currentAsks;
        std::string currentTime;
        std::set<std::string> setOfProducts;
        std::set<std::string>::iterator setIterator;
};

