#include <iostream>
#include <vector>
// #include <fstream>
// #include <string>
// #include <stdexcept>
// #include <algorithm>
// #include <cctype>
#include "CSVReader.h"
// #include "Helpers.h"




// void CSVReader::readDocumentLineByLine(const std::string& documentName, OrderBook& orderBook)
// {
//     std::cout << documentName << std::endl;
//     unsigned int n = 1;
//     std::vector<OrderBookEntry> entries;
//     std::vector<std::string> products;
//     std::vector<std::string> tokens;

//     // std::string csvFilename{documentName};
//     std::ifstream csvFile{documentName};
//     std::string line;
//     if (csvFile.is_open())
//     {
//         while(std::getline(csvFile, line))
//         {
//             try 
//             {
//                 entries.push_back(CSVReader::parseOrderBookEntry(line,orderBook, true, false));
//             } catch(const std::exception& e)
//             {
//                 std::cout << "CSVReader::readCSV failed to parse linenumber: " << n  << " from "<< documentName << std::endl;
//                 std::cerr << "exception: " << e.what() << std::endl;
//             }
//             // if (n > 5) //Code to limit the amount of entries to the number here
//             // {break;}   //uncomment both lines to activate
//             ++n;
//         }// end of while
         
//          //print out every product in set of Products after loading in the files.
        
//         orderBook.printSetOfProducts();

//     } else{
//         std::cout << "CSVReader::readCSV could not read file: "  << documentName << std::endl;
//     }
//     csvFile.close();
//     // std::cout << entries[3].price << std::endl;
//     // std::cout << entries[3].amount << std::endl;

//     std::cout << "CSVReader::readCSV read " << entries.size() << " entries"  << std::endl;
// }   
// //     std::string csvFilename{"data/20200317T3.csv"};
// //     std::ifstream csvFile{csvFilename};
// //     std::string line;
// //     if (csvFile.is_open())
// //     {
// //         std::cout << "Opened file " << csvFilename << std::endl;
// //         std::string line;
// //         while (getline(csvFile, line))
// //         {
// //             std::vector<std::string> tokens = tokenise(line, ',');
// //             std::cout << "Read " << tokens.size() << " tokens " << std::endl;
// //             if (tokens.size() != 5)
// //                 continue;
// //             try
// //             {
// //                 std::string timestamp = tokens[0];
// //                 std::string product = tokens[1];
// //                 // what about tokens[2]?
// //                 double price = std::stod(tokens[3]);
// //                 double amount = std::stod(tokens[4]);
// //             }
// //             catch (const std::exception &e)
// //             {
// //                 continue;
// //             }
// //         }
// //     }
// //     else
// //     {
// //         std::cout << "Problem opening file " << csvFilename << std::endl;
// //     }
// //     csvFile.close();
// //     return OrderBookEntry obe (20,123,23,23,23)
// // }

// OrderBookEntry CSVReader::parseOrderBookEntry(std::string& line, OrderBook& orderBook, const bool add, const bool userBool )
// {

//     std::vector<std::string> tokens;
//     std::string s;
//     Product product1;
//     Product product2;
//     std::vector<std::string> products;
//     HelpersNameSpace::OrderBookType OBT;
//     std::vector<std::string> number;
//     double price;
//     double amount;

    
    
            
//     // OrderBookEntry obe = stringsToOBE(tokenise(line, ','));

//     // std::cout << line << std::endl;
//     tokens = CSVReader::tokenize(line, ',');
    
//     if (tokens.size() == 5)
//     {
//         if (tokens[0].length() == 26)
//         {
//             s = tokens[0];
//         }else {throw std::invalid_argument( "Length of time input is not valid" );}
        
        
        
        
//         //From https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case:
//         std::transform(tokens[2].begin(), tokens[2].end(), tokens[2].begin(),
//         [](unsigned char c){ return std::tolower(c); });
        
//         // std::cout << tokens[2] << std::endl;
        
//         if (tokens[2] == "ask")
//         {
//             OBT = HelpersNameSpace::OrderBookType::ask;
//         } else if (tokens[2] == "bid")
//         {
//             OBT = HelpersNameSpace::OrderBookType::bid;
//         } else {throw std::invalid_argument( "Order book type has to be bid or ask" );}

//         number = CSVReader::tokenize(tokens[3], '.');
//         // for (std::string& s : number)
//         // {
//         //     std::cout << s << std::endl;
//         // }

       
//         if (number.size() == 1)
//         {
//             if (HelpersNameSpace::is_digits(number[0]))
//             {
//                 price = std::stod(tokens[3]);
//             } else {throw std::invalid_argument( "Invalid number for price: non numeric values" );}
//         } else if (number.size() == 2)
//         {
//             if (HelpersNameSpace::is_digits(number[0]) &&  HelpersNameSpace::is_digits(number[1]))
//             {
//                 price = std::stod(tokens[3]);
//             } else {throw std::invalid_argument( "Invalid number for price: non numeric values" );}

//         } else {throw std::invalid_argument( "Invalid number for price: more than one '.'" );}

//         number = CSVReader::tokenize(tokens[4], '.');
//         if (number.size() == 1)
//         {
//             if (HelpersNameSpace::is_digits(number[0]))
//             {
//                 amount = std::stod(tokens[4]);
//             } else {throw std::invalid_argument( "Invalid number for amount: non numeric values" );}
//         } else if (number.size() == 2)
//         {
//             if (HelpersNameSpace::is_digits(number[0]) &&  HelpersNameSpace::is_digits(number[1]))
//             {
//                 amount = std::stod(tokens[4]);
//             } else {throw std::invalid_argument( "Invalid number for amount: non numeric values" );}

//         } else {throw std::invalid_argument( "Invalid number for amount: more than one '.'" );}

//         //Adapted from https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case:
//         std::transform(tokens[1].begin(), tokens[1].end(), tokens[1].begin(),
//         [](unsigned char c){ return std::toupper(c); });
        
//         // std::cout << tokens[1] << std::endl;
        
//         products = CSVReader::tokenize(tokens[1], '/');

//         if (products.size() == 2 && products[0] != products[1])
//         {
//             if (products[0] != "" && products[1] != "")
//             {
//                 Product product1(products[0], orderBook,add);
//                 Product product2(products[1], orderBook,add);

//             } else {throw std::invalid_argument( "Product cannot be empty" );}

//         } else {throw std::invalid_argument( "Not two distinct products entered" );}

//     } else {throw std::invalid_argument( "Line does not have the right amount of comma seperated values. Should be five" );}
//     // products = CSVReader::tokenize(tokens[1], '/');
//     // orderBook.addToSetOfProducts(products[0]);
//     // orderBook.addToSetOfProducts(products[1]);
    

//     OrderBookEntry OBE( s ,product1, product2,OBT ,price,amount, userBool );

//     // if(n >= 2) break;
//     return OBE;
    
// }


std::vector<std::string> CSVReader::tokenize(std::string& csvLine, const char separator)
{
    // string vector tokens ## stores the tokens
    std::vector<std::string> tokens;
    //temporary token storage
    std::string token;

    // tokens.push_back(token);
    // int start, end ## used to delineate the position of the tokens
    signed int start, end;
    
    std::cout << csvLine << std::endl; 
        
    start = csvLine.find_first_not_of(separator, 0);

    do
    {

        // end = next 'separator' after start
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length())
            break;
        
        //broke out this logic so that the function can deal with multiple seperators
        if (start == end)
        {
            ++start;
            continue;
        }

        // we found the separator
        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);
        
        
        // add token to the end of the tokens vector
        // tokens.push_back(token);
        // CSVReader::addToVector(tokens, token);

        start = end + 1;

    } while (end > 0);

    return tokens;
}


// CSVReader::addToVector(std::vector<std::string> &tokens, const std::string &token)
// {
//     tokens.push_back(token);
// }



