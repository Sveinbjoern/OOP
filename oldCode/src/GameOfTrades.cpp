#include <iostream>
#include <conio.h>
#include <limits>
#include <vector>
#include "GameOfTrades.h"
#include "CSVReader.h"


using namespace std;


void GameOfTrades::init(){

  
    // HelpersNameSpace::OrderBookType type1 = HelpersNameSpace::OrderBookType::bid;
    // cout << (type1 == HelpersNameSpace::OrderBookType::ask) << endl;
    // cout << static_cast<underlying_type<HelpersNameSpace::OrderBookType>::type>(type1) << endl;

    

    // OrderBookEntry order1 (22.23,123.345,HelpersNameSpace::OrderBookType::bid, "sdfg","dfg","FGH");
    // cout << order1.price << endl;
    // cout << order1.amount << endl;
    // cout << static_cast<underlying_type<HelpersNameSpace::OrderBookType>::type>(order1.typeOfEntry) << endl;
    // cout << order1.firstProduct << endl;
    // cout << order1.secondProduct << endl;
    // cout << order1.dateTimeString << endl;

    // orderBook.products.insert("pipp");
    // orderBook.products.insert("aaaa");
    // orderBook.products.insert("qual");
    // orderBook.products.insert("pipp");
    // orderBook.products.insert("pipp");
    // orderBook.products.insert("pipp");
    // orderBook.products.insert("papp");
    // orderBook.products.insert("popp");
    // orderBook.products.insert("pipp"); 
    


    // for(orderBook.setIterator = orderBook.products.begin(); orderBook.setIterator != orderBook.products.end() ; ++orderBook.setIterator) {
    //         cout << *orderBook.setIterator << endl; // Note the "*" here
    //     }    

    // cout << *orderBook.products.begin() << endl;

    // string s = "pipp";

    // if (orderBook.products.find(s) != orderBook.products.end())
    // {
    //     cout << "is in the set" << s << endl;
    // } else
    // {
    //     cout << "is not in the set" << s << endl;
    // }
    
    // s = "qack";
    // if (orderBook.products.find(s) != orderBook.products.end())
    // {
    //     cout << "is in the set" << s << endl;
    // } else
    // {
    //     cout << "is not in the set" << s << endl;
    // }


    // GameOfTrades::printIntroduction();
    while (userInputInt != 9)
    {

        
        printMenu();
        getUserInputMainMenu(userInputInt);
    }
    
    printEndScreen();
}

GameOfTrades::GameOfTrades(){
    userInputInt = 0;
    numberOfOptions = 5;

    
    
}


void GameOfTrades::printIntroduction(){
    clearScreen();
    cout << "Welcome to the Game of Trade or GoT for short." << endl;
    cout << "A pleasant simulation of the peacful world of trading." << endl;   
    cout << "You will place yourself in the shoes of a trader." << endl;   
    cout << "You will be given multiple choices." << endl;   
    cout << "Simulation start end and what market!!!!!." << endl;   
    cout << "Type the number in front of the choice to select it." << endl;   
    cout << "And if you need help. Any kind of help! Go to the help section!" << endl;
    getch(); 

}

void GameOfTrades::printMenu()
{
    clearScreen();
    cout << "Welcome to the Game of Trade:" << endl;
    cout << "A pleasant simulation of the peacful world of trading" << endl;
    cout << "//////////////////////////////////////" << endl;
    cout << "0: Help!" << endl;
    cout << "1: Print exchange stats" << endl;
    cout << "2: Place an ask" << endl;
    cout << "3: Place a bid" << endl;
    cout << "4: Print wallet" << endl;
    cout << "5: Let some time pass" << endl;
    cout << "9: I am giving up!" << endl;
    cout << "//////////////////////////////////////" << endl;
}


void GameOfTrades::clearScreen(){
    for (int i = 0; i < 30; i++)
    cout << endl;
}

void GameOfTrades::getUserInputMainMenu(unsigned short int &userInputInt){
    
    cout << "What will you do? Press a number between 0 and " << numberOfOptions << ", or the number 9 if you are done:";
    
    if (! (cin >> userInputInt))
    {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } 
    
    // cout << GameOfTrades::userInputInt << endl;

    switch (userInputInt)
    {
        case 0:
            printHelpMenu();
            break;
        
        case 1:
            printStatsMenu();
            break;
        
        case 2:
            printPlaceAnAskMenu();
            break;
        
        case 3:
            printPlaceABidMenu();
            break;
        
        case 4:
            printWalletMenu();
            break;
        
        case 5:
            updateTime();
            break;

        case 9:
            break;
        
        default:
            printHelpMenu();
            break;
    
    }
    
}

void GameOfTrades::printHelpMenu()
{
    clearScreen();
    cout << "Help!" << endl;
    getch(); 
}
void GameOfTrades::printStatsMenu()
{
    clearScreen();
    cout << "Stats!" << endl;
    getch(); 
}
void GameOfTrades::printPlaceAnAskMenu()
{
    clearScreen();
    cout << "Ask!" << endl;
    getch(); 
}
void GameOfTrades::printPlaceABidMenu()
{
    clearScreen();
    cout << "Bid!" << endl;
    getch(); 
}
void GameOfTrades::printWalletMenu()
{
    clearScreen();
    cout << "Wallet!" << endl;
    getch(); 
}

void GameOfTrades::updateTime()
{
    clearScreen();
    cout << "Moving time!" << endl;
    getch(); 
}
void GameOfTrades::printEndScreen()
{
    clearScreen();
    cout << "/////////////////////////////////////////////////" << endl;
    cout << "Do you think this is over?! It is never over!" << endl;
    cout << "You will be back, because you need the money!" << endl;
    cout << "You will be back!" << endl;
    cout << "/////////////////////////////////////////////////" << endl << endl << endl << endl << endl;
}