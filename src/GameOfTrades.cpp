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
    
    // double a;
    // double b;
    // double c;
    // double d;
    // a = 1.234324525;
    // b = 0.0000000012;
    // c = 3123123.12;
    // d = 0;
    // std::string A;
    // std::string B;
    // std::string C;
    // std::string D;
    // A = HelpersNameSpace::doubleToStringPresicion(a);
    // B = HelpersNameSpace::doubleToStringPresicion(b);
    // C = HelpersNameSpace::doubleToStringPresicion(c);
    // D = HelpersNameSpace::doubleToStringPresicion(d);
    // std::cout << "double a: " << a << std::endl;
    // std::cout << "double A: " << A << std::endl;
    // std::cout << "double b: " << b << std::endl;
    // std::cout << "double B: " << B << std::endl;
    // std::cout << "double c: " << c << std::endl;
    // std::cout << "double C: " << C << std::endl;
    // std::cout << "double d: " << d << std::endl;
    // std::cout << "double D: " << D << std::endl;


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
    
    //print out every product in set of Products after loading in the files.
    orderBook.printSetOfProducts();

    //setup files in the orderBook
    orderBook.setupOrderbook();


    // getUserInputLine(userInputText);
    // getUserInputLine("Beautiful");
    // std::cout << std::endl << userInputText << std::endl;
    menuText.append("For errorlog see above\n\n");
    menuText.append(advisorString());
    menuText.append(standardAdvisorString());

    std::cout << advisorString();
    menuText = mainInput(menuText);
    

    
    // GameOfTrades::printIntroduction();
    while (userInputText != "QUIT" && userInputText != "EXIT")
    {
        clearScreen();
        std::cout << advisorName << "> ";
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
    userInputText = "";
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
    text.append("help CMD: You can get help with an individual command by\n");
    text.append("          writing help followed by the command.\n");
    text.append("min: display minimum bid or ask for a product pair.\n");
    text.append("max: display maximum bid or ask for a product pair.\n");
    text.append("avg: display average bid or ask for a product pair for some steps back\n");
    text.append("prod: Lists all available product\n");
    text.append("predict: predicts the minimum or maximum, ask or bid for products\n");
    text.append("time: Gives current timestep\n");
    text.append("step: Moves to the next timestep.\n");
    text.append("advice: Gives advice on what to bid or ask\n");
    text.append("exit/quit: ends the program. \n");
    return text;
}

std::string GameOfTrades::helpCMD(std::string &command)
{
    std::string text;
    if (command == "HELP")
    {
        text.append("The \"help\" command:\n");
        text.append("Takes another command as an argument.\n");
        text.append("Default gives you a list of all arguments.\n");
        text.append("Haven't you seen it already?\n");

        return text;
    } else if (command == "MIN")
    {
        text.append("The \"min\" command:\n");
        text.append("Takes a product pair seperated with \"/\" \n");
        text.append("as its first argument. \n");
        text.append("Takes \"bid\" or \"ask\" as its second argument.\n");
        text.append("Default gives both ask and bid.\n");
        text.append("Example line: min ETH/BTC ask\n");
        text.append("Example answer: The minimum ask for ETH/BTC is 1.0\n");

        return text;
    } else if (command == "MAX")
    {
        text.append("The \"max\" command:\n");
        text.append("Takes a product pair seperated with \"/\" \n");
        text.append("as its first argument. \n");
        text.append("Takes \"bid\" or \"ask\" as its second argument.\n");
        text.append("Default gives both ask and bid.\n");
        text.append("Example line: max ETH/BTC ask\n");
        text.append("Example answer: The maximum ask for ETH/BTC is 1.0\n");

        return text;
    } else if (command == "AVG")
    {
        text.append("The \"avg\" command:\n");
        text.append("Takes a product pair seperated with \"/\" \n");
        text.append("as its first argument. \n");
        text.append("Takes \"bid\" or \"ask\" as its second argument.\n");
        text.append("Default gives both ask and bid.\n");
        text.append("Takes a number of steps back as its third argument.\n");
        text.append("Default gives 10 steps.\n");
        text.append("Example line: avg ETH/BTC ask 10\n");
        text.append("Example answer: The average ask for ETH/BTC\n");
        text.append("over the last 10 timesteps is 1.0\n");

        return text;
    } else if (command == "PROD")
    {
        text.append("The \"prod\" command:\n");
        text.append("Does not take any arguments.\n");
        text.append("Lists all availble products.\n");

        return text;
    } else if (command == "PREDICT")
    {
        text.append("The \"predict\" command:\n");
        text.append("Takes \"max\" or \"min\" as its first argument.\n");
        text.append("Default gives both max and min.\n");
        text.append("Takes a product pair seperated with \"/\" \n");
        text.append("as its second argument. \n");
        text.append("Takes \"bid\" or \"ask\" as its third argument.\n");
        text.append("Default gives both ask and bid.\n");
        text.append("Example line: predict max ETH/BTC ask\n");
        text.append("Example answer: The expected maximum ask for ETH/BTC is 1.0\n");

        return text;
    } else if (command == "TIME")
    {
        text.append("The \"time\" command:\n");
        text.append("Does not take any arguments.\n");
        text.append("Prints current timeframe.\n");

        return text;
    } else if (command == "STEP")
    {
        text.append("The \"step\" command:\n");
        text.append("Does not take any arguments.\n");
        text.append("Moves current timeframe one step forward.\n");

        return text;
    } else if (command == "ADVICE")
    {
        text.append("The \"advice\" command:\n");
        text.append("Does not take any arguments.\n");
        text.append("Gives advice on what to ask/bid for next timeframe.\n");

        return text;
    } else if (command == "EXIT")
    {
        text.append("The \"exit\" command:\n");
        text.append("exit or quit ends the program\n");
        return text;
    } else if (command == "QUIT")
    {
        text.append("The \"quit\" command:\n");
        text.append("quit or exit ends the program\n");
        return text;
    } else 
    {
        text.append(command);
        text.append(" is not a recognized command\n");
        text.append(helpText());
        return text;
    } 
    return text;
}

std::string GameOfTrades::standardAdvisorString()
{
    std::string returnString;
    returnString.append("Please enter command, or type \"help\" for list of commands");
    return returnString;
}

std::string GameOfTrades::advisorString()
{
    std::string returnString;
    returnString.append(advisorName);
    returnString.append("> ");
    return returnString;
}

std::string GameOfTrades::allProductsString()
{
    std::vector<std::string> products;
    std::string returnString = "";
    products = orderBook.getVectorOfProducts();
    returnString.append("All available products:\n");
    for (std::string prod : products)
    {
        returnString.append(prod);
        returnString.append("\n");
    }
    return returnString;
}

  

std::string GameOfTrades::mainInput(std::string overText)
{
    //Setting precision of cout with code from
    // https://stackoverflow.com/questions/554063/how-do-i-print-a-double-value-with-full-precision-using-cout
    typedef std::numeric_limits< double > dbl;
    std::cout.precision(dbl::max_digits10);

    std::cout << overText << std::endl;
    GameOfTrades::getUserInputLine(userInputText);
    std::vector<std::string> tokens = CSVReader::tokenize(userInputText, ' ');

    /**lambda functions for the function GameOfTrades::mainInput  
     * creates the return string for inputs min and max
    */
    auto lamMinMaxString = [&](std::string minOrMax)
    {
        std::cout << "runing lamda for minMax";
        std::string returnString;
        std::string example = "Example: ";
        example.append(minOrMax);
        example.append(" usd/doge bid");
        if (tokens.size() == 1)
        {
            returnString = helpCMD(minOrMax);
        } else
        {
            std::vector<std::string> products;
            try
            {
                products = CSVReader::tokenize(tokens[1], '/');
            }
            catch(const std::exception& e)
            {
                
                returnString.append("Input resulted in error:\n");
                returnString.append(e.what());
                returnString.append("\n");
                return returnString;
            }
            
            
              std::cout << products[0];
              std::cout << "products.size(): " << products.size();
              
            
           if (products.size() == 1)
            {
                returnString.append("Products must be seperated by \"/\",\n");
                returnString.append("or you need to give two products.\n");
                returnString.append(example);
                return returnString;
            } else if (products.size() == 0)
            {
                returnString.append(tokens[1]);
                returnString.append(" is not a product pair.\n");
                returnString.append(example);
                return returnString;
            } 

            Product prod1;
            Product prod2;


            try
            {
                Product prod1 {products[0], orderBook};
            }
            catch(const std::exception& e)
            {
                try
                {
                     Product prod2 (products[1], orderBook);
                }
                catch(const std::exception& e)
                {
                    returnString.append(products[0]);
                    returnString.append(" and ");
                    returnString.append(products[1]);
                    returnString.append("\nare not valid products\n");
                    returnString.append(allProductsString());
                    return returnString;std::cerr << e.what() << '\n';
                }
                returnString.append(products[0]);
                returnString.append(" is not a valid product\n");
                returnString.append(allProductsString());
                return returnString;
            }

            try
            {
                 Product prod2 (products[1], orderBook);
            }
            catch(const std::exception& e)
            {
                returnString.append(products[1]);
                returnString.append(" is not a valid product\n");
                returnString.append(allProductsString());
                return returnString;
            }
            
            //If both prod1 and prod2 are not false we have two valid products
            if (products[0] == products[1])
            {
                returnString.append("You have to give two different products.\n");
                returnString.append(allProductsString());
                return returnString;
            }


           


            if (tokens.size() == 2 )
            {
                double bid = orderBook.getHighOrLowPriceBid(minOrMax, prod1, prod2);
                double ask = orderBook.getHighOrLowPriceAsk(minOrMax, prod1, prod2);
                
                returnString.append("The ");
                returnString.append(minOrMax);
                returnString.append(" bid for ");
                returnString.append(products[0]);
                returnString.append("/");
                returnString.append(products[1]);
                returnString.append(" is ");
                returnString.append(HelpersNameSpace::doubleToStringPresicion(bid));
                returnString.append(".\n");

                returnString.append("The ");
                returnString.append(minOrMax);
                returnString.append(" ask for ");
                returnString.append(products[0]);
                returnString.append("/");
                returnString.append(products[1]);
                returnString.append(" is ");
                returnString.append(HelpersNameSpace::doubleToStringPresicion(ask));
                returnString.append(".\n");
                std::cout.precision(15);
                std::cout << "ask " << ask << " bid " << bid<< endl; 

                return returnString;
            } else if (tokens[2] == "ASK" | tokens[2] == "ASKS")
            {
                double ask = orderBook.getHighOrLowPriceAsk(minOrMax, prod1, prod2);
                returnString.append("The ");
                returnString.append(minOrMax);
                returnString.append(" ask for ");
                returnString.append(products[0]);
                returnString.append("/");
                returnString.append(products[1]);
                returnString.append(" is ");
                returnString.append(HelpersNameSpace::doubleToStringPresicion(ask));
                returnString.append(".\n");
                return returnString;
            } else if (tokens[2] == "BID" | tokens[2] == "BIDS")
            {
                double bid = orderBook.getHighOrLowPriceBid(minOrMax, prod1, prod2);
                 returnString.append("The ");
                returnString.append(minOrMax);
                returnString.append(" bid for ");
                returnString.append(products[0]);
                returnString.append("/");
                returnString.append(products[1]);
                returnString.append(" is ");
                returnString.append(HelpersNameSpace::doubleToStringPresicion(bid));
                returnString.append(".\n");
                return returnString;
            } else
            {
                double bid = orderBook.getHighOrLowPriceBid(minOrMax, prod1, prod2);
                double ask = orderBook.getHighOrLowPriceAsk(minOrMax, prod1, prod2);

                
                returnString.append("The ");
                returnString.append(minOrMax);
                returnString.append(" bid for ");
                returnString.append(products[0]);
                returnString.append("/");
                returnString.append(products[1]);
                returnString.append(" is ");
                returnString.append(HelpersNameSpace::doubleToStringPresicion(bid));
                returnString.append(".\n");

                returnString.append("The ");
                returnString.append(minOrMax);
                returnString.append(" ask for ");
                returnString.append(products[0]);
                returnString.append("/");
                returnString.append(products[1]);
                returnString.append(" is ");
                returnString.append(HelpersNameSpace::doubleToStringPresicion(ask));
                returnString.append(".\n");


                return returnString;

            }
        }
        
        return returnString;
    };
   


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
            overText = "MIN";
            return lamMinMaxString(overText);
        } else if (tokens[0] == "MAX")
        {
            overText = "MAX";
            return lamMinMaxString(overText);
        } else if (tokens[0] == "AVG")
        {

        } else if (tokens[0] == "PROD")
        {
            std::vector<std::string> products;
            products = orderBook.getVectorOfProducts();
            overText = allProductsString();
            
            overText.append(advisorString());
            overText.append(standardAdvisorString());
            return overText;
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
            overText.append(advisorString());
            overText.append(tokens[0]);
            overText.append(" is not a valid command. ");
            overText.append(standardAdvisorString());
            return overText;
        }
            
        
    } else 
    {
        overText = "";
        overText.append(advisorString());
        overText.append(standardAdvisorString());

        return overText;
    }
    overText = "";
    return overText;



}