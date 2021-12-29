#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <type_traits>
#include "Helpers.h"
#include "OrderBook.h"




#include <map>
/*
    Make something with the map library
    // map from ints to function pointers
    std::map<int,void(*)()> menu;
    // connect 1 to the printHelp function
    menu[1] = printHelp;
    // call option 1
    menu[1]();
*/

/** Main class of the whole app*/
class GameOfTrades 
{
    public: // parts of the class that can be seen from outside
        GameOfTrades();
        /** Call this to start the sim */
        void init();

        //The enum OrderBookType available for every part of the app
        enum class OrderBookType{ask,bid};
        
        //Create an orderbook
        OrderBook orderBook;
        

    private:

        unsigned short int userInputInt;
        unsigned short int numberOfOptions;
        std::string userInputText;

        void printIntroduction();
        void printMenu();

        /** Help menu appears when the user gives a number out of range 
         * or any other random input(interpreted to 0)
         */
        void printHelpMenu();
        void printStatsMenu();
        void printPlaceAnAskMenu();
        void printPlaceABidMenu();
        void printWalletMenu();
        void printEndScreen();

        void updateTime();

        /** Gets input from user. Returns */
        void getUserInputMainMenu(unsigned short int &userInputInt);
        void clearScreen();


};

