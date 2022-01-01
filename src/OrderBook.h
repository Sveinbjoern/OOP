#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <type_traits>


class OrderBookEntry;
class Products;

class OrderBook
{
    public:

         /** Class constuctor*/
        OrderBook() = default;


        int orderCount();



       /** construct, reading a csv data file */
        OrderBook(const std::string& filename);

        /** OVERLOADED function for returning vector of Orders from this orderBook according to the sent filters
         * arg1: type
         * arg2: product
         * arg3: timestamp
         * arg4: source vector of orders to serach
        */
        std::vector<OrderBookEntry> getOrders(  const HelpersNameSpace::OrderBookType& type,
                                                const Product& product,
                                                const std::string& timestamp,
                                                const std::vector<OrderBookEntry>& source );
        /** OVERLOADED function for returning vector of Orders from this orderBook according to the sent filters
         * arg1: timestamp
         * arg2: source vector of orders to serach
        */
        std::vector<OrderBookEntry> getOrders(const std::string& timestamp,
                                                const std::vector<OrderBookEntry>& source );

        /** OVERLOADED function for returning vector of Orders from this orderBook according to the sent filters
         * arg1: timestamp
         * arg2: type
         * arg3: source vector of orders to serach
        */
        std::vector<OrderBookEntry> getOrders(  const std::string& timestamp,
                                                const HelpersNameSpace::OrderBookType& type,
                                                const std::vector<OrderBookEntry>& source );

        /** OVERLOADED function for returning vector of Orders from this orderBook according to the sent filters
         * arg1: type
         * arg2: product1 type
         * arg3: product2 type
         * arg4: timestamp
        */
        std::vector<OrderBookEntry> getOrders(  const HelpersNameSpace::OrderBookType& type,
                                                const std::string& product1,
                                                const std::string& product2,
                                                const std::string& timestamp,
                                                const std::vector<OrderBookEntry>& source );

        /** return the price of the highest bid in the sent set */
        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        /** return the price of the lowest bid in the sent set */
        static double getLowPrice(std::vector<OrderBookEntry>& orders);
        
         /** return vector of all know products in the dataset*/
        std::vector<Products> getKnownProducts();

        
       
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

        /** funciton that prints setOfProducts of this objects orderbook 
         * Does not take any arguments.
        */
        void printSetOfProducts();
       
        /** funciton that returns if a vector of string with every product in this objects orderbook 
          * Does not take any arguments.
        */
        std::vector<std::string> getVectorOfProducts();

        

        /** Put an order in the private orders vector*/
        void addOrderBookEntry( OrderBookEntry entry);


        /**if setup has not been run before */
        void setupOrderbook();

    private:
        /** Load the set of currentBids and currentAsks for the currentTime
         * Should be loaded once every time movement.
        */
        void loadCurrentEntries();

       // Set of all stored values
        std::vector<OrderBookEntry> orders;
        std::vector<OrderBookEntry> currentBids;
        std::vector<OrderBookEntry> currentAsks;
        std::string currentTime;
        int currentEntryIndex;
        std::set<std::string> setOfProducts;
        std::set<std::string>::iterator setIterator;

        bool setup = false;
};

