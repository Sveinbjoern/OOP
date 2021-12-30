#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <type_traits>
// #include "Helpers.h"
// #include "OrderBook.h"





/** Main class of the whole app*/
class GameOfTrades 
{
    public: // parts of the class that can be seen from outside
        GameOfTrades();
        /** Call this to start the sim */
        void init();

        //The enum OrderBookType available for every part of the app
        // enum class OrderBookType{ask,bid};
        
        //Create an orderbook
        // OrderBook orderBook;
        

    private:

        unsigned short int userInputInt;
        unsigned short int numberOfOptions;
        std::string userInputText;
        std::string userName;
        std::string advisorName;

        void printIntroduction();
        // void printMenu();

        /** Help menu appears when the user gives a number out of range 
         * or any other random input(interpreted to 0)
         */
        // void printHelpMenu();
        // void printStatsMenu();
        // void printPlaceAnAskMenu();
        // void printPlaceABidMenu();
        // void printWalletMenu();
        // void printEndScreen();

        // void updateTime();

        /** Functions to handle inputs that depend on menu*/
        void mainInput(std::string); 
        void optionsMenu();

        // void getUserInputOptionsMenu(unsigned short int &userInputInt);
        /** Gets input from user. Returns a complete line as a string*/
        void getUserInputLine(std::string &userInputText);

        void clearScreen();



        // Wallet wallet;

};

