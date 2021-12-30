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

    // setup: neccessary files loaded. 
    CSVReader::readDocumentLineByLine( "data\\20200317T3.csv", orderBook );
    
   

    // getUserInputLine(userInputText);
    // getUserInputLine("Beautiful");
    // std::cout << std::endl << userInputText << std::endl;
    menuText.append("For errorlog see above\n\n");
    menuText.append(advisorName);
    menuText.append("> Please enter command, or type help for list of commands");

    // GameOfTrades::printIntroduction();
    while (userInputText != "QUIT" && userInputText != "EXIT")
    {
        // std::cout << userInputText;
        menuText = mainInput(menuText);
        // getUserInputMainMenu(userInputInt);
    }

}

GameOfTrades::GameOfTrades(){
    userInputInt = 0;
    numberOfOptions = 5;

    userInputText = "";
    userName = "user";
    advisorName = "advisorBot";
    menuText = "";
    
    
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
    cout << "\n";
}

// void GameOfTrades::getUserInputMainMenu(unsigned short int &userInputInt){
    
//     cout << "What will you do? Press a number between 0 and " << numberOfOptions << ", or the number 9 if you are done:";
    
//     if (! (cin >> userInputInt))
//     {
//         cin.clear(); 
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//     } 
    
//     // cout << GameOfTrades::userInputInt << endl;

//     switch (userInputInt)
//     {
//         case 0:
//             printHelpMenu();
//             break;
        
//         case 1:
//             printStatsMenu();
//             break;
        
//         case 2:
//             printPlaceAnAskMenu();
//             break;
        
//         case 3:
//             printPlaceABidMenu();
//             break;
        
//         case 4:
//             printWalletMenu();
//             break;
        
//         case 5:
//             updateTime();
//             break;

//         case 9:
//             break;
        
//         default:
//             printHelpMenu();
//             break;
    
//     }
    
// }

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

void GameOfTrades::getUserInputLine(std::string &userInputText)
{
    cout << userName << "> ";
    cin.clear(); 
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, userInputText);
    // cout << userInputText << endl;
    HelpersNameSpace::toUpper(userInputText);
    // cout << userInputText << endl;
    // cout << endl << userInputText << endl;
    // getch();
    
}

std::string GameOfTrades::helpText()
{
    std::string text;
    text.append("All available commands:\n");
    text.append("help: this list\n");
    text.append("help CMD: You can get help with the individual command by\n");
    text.append("writing help followed by the command.\n");
    text.append("min: \n");
    text.append("max: \n");
    text.append("avg: \n");
    text.append("prod: Lists all available product\n");
    text.append("predict: \n");
    text.append("time: \n");
    text.append("step: \n");
    text.append("advice: \n");
    text.append("exit/quit: ends the program. \n");
    return text;
}

std::string GameOfTrades::helpCMD(std::string &command)
{
    std::string text;
    if (command == "HELP")
    {
        text.append("Help gives the help menu\n");
        text.append("Haven't you seen it already?\n");
        return text;
    } else if (command == "MIN")
    {
        text.append("Min gives \n");
        text.append("Haven't you seen it already?\n");
        return text;
    } else if (command == "MAX")
    {

    } else if (command == "AVG")
    {

    } else if (command == "PROD")
    {

    } else if (command == "PREDICT")
    {

    } else if (command == "TIME")
    {

    } else if (command == "STEP")
    {

    } else if (command == "ADVICE")
    {

    } else if (command == "EXIT")
    {
        text.append("exit or quit ends the program\n");
        return text;
    } else if (command == "QUIT")
    {
        text.append("quit or exit ends the program\n");
    } else 
    {
        text.append(command);
        text.append(" is not a recognized command\n");
        text.append(helpText());
        return text;
    } 
    return text;
}

std::string GameOfTrades::mainInput(std::string overText)
{
    std::cout << overText << std::endl;
    GameOfTrades::getUserInputLine(userInputText);
    std::vector<std::string> tokens = CSVReader::tokenize(userInputText, ' ');

    if (tokens.size() > 0)
    {
        if(tokens[0] == "HELP")
        {
            if (tokens.size() > 1)
            {
                overText = helpCMD(tokens[1]);
                return overText;
            } else 
            {
                overText = helpText();
                clearScreen();
                return overText;
            }
          

        } else if (tokens[0] == "MIN")
        {

        } else if (tokens[0] == "MAX")
        {

        } else if (tokens[0] == "AVG")
        {

        } else if (tokens[0] == "PROD")
        {

        } else if (tokens[0] == "PREDICT")
        {

        } else if (tokens[0] == "TIME")
        {

        } else if (tokens[0] == "STEP")
        {

        } else if (tokens[0] == "ADVICE")
        {

        } else if (tokens[0] == "EXIT")
        {
            printEndScreen();
            return "";

        } else if (tokens[0] == "QUIT")
        {
            printEndScreen();
            return "";
        } else if (tokens[0] == "HELP")
        {

        } else if (tokens[0] == "HELP")
        {

        } else
        {
            overText = "";
            overText.append(advisorName);
            overText.append("> ");
            overText.append(tokens[0]);
            overText.append(" is not a valid command. Please enter command, or type help for list of commands");
            return overText;
        }
            
        
    } else 
    {
        overText = "";
        overText.append(advisorName);
        overText.append("> Please enter command, or type help for list of commands");

        return overText;
    }
    overText = "";
    return overText;
} 