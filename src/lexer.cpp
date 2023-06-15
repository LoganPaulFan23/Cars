#include "../h/Token.h"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

std::vector<Token> tokens = {};

// Adds a token to the list
void sendToken(std::string type, std::string text) {
    Token token(type, text);
    tokens.push_back(token);
}

// Checks if the string from the index to the next blank is a number
// Returns 0 if it is not a number
int isNum(std::string str, int startingIndex) {

    for (int i = startingIndex; i < str.length(); i++) {
        if (isalpha(str[i])) {
            return 0;
        }

        if (!isdigit(str[i])) {
            return i - startingIndex;
        }
    }
    
    return str.length() - startingIndex;
}

int isOpp(std::string str, int startingIndex) {
    char testChar = str[startingIndex];
    char nextChar = 0x00;

    // Sets the next char to a value if the current char isn't the last
    if (str.length() > startingIndex + 1) {
        nextChar = str[startingIndex + 1];
    }

    const char oppChars[] = {'+', '-', '=', '<', '>', '/', '*', '&', '|'};
    const int COMBO_AMOUNT = 6;
    const char combos[COMBO_AMOUNT][2] = {{'>', '='}, {'<', '='}, {'+', '='}, {'-', '='}, {'*', '='}, {'/', '='}};

    // Checks if the char is an opp char
    for (char c : oppChars) {
        if (testChar == c) {
            // Checks if the char is part of a combo
            for (int i = 0; i < COMBO_AMOUNT; i++) {
                if (testChar == combos[i][0] && nextChar == combos[i][1]) {
                    return 2;
                }
            }

            // Says the opp is 1 char long if not a combo
            return 1;
        }
    }

    return 0;
}





void lexLine(string line) {

    // checks if the line is blank or if its an end line
    bool blankLine = true;
    for (char c : line) {
        if (c != ' ') {
            blankLine = false;
        }

        // Checks if the line is a function terminator
        if (c == '!') {
            sendToken("FUNE", "");
            return;
        }
    }

    // Stops lexing if it is blank
    if (blankLine) {
        return;
    }


    std::string tempString;

    std::string tokenType = "ID  ";

    for (int i = 0; i < line.length(); i++) {

        tempString += line[i];

        // Checks if the char is blank
        if (line[i] == ' ') {
            // Removes the blank char off the token
            tempString.pop_back();

            // Makes sure the token isn't blank before sending
            if (tempString.length() > 0) {
                sendToken(tokenType, tempString);
            }
            tempString = "";
            tokenType = "ID  ";
        }

        // Checks if the next token is a number if at start of token
        if (tempString.length() == 1) {
            if (isNum(line, i) != 0) {
                tokenType = "NUM ";
            }
        }

        
        // Checks if the next token is an operation
        int oppNum = isOpp(line, i);
        if (oppNum != 0) {
            std::string tempOppStr = "";
            tempOppStr += line[i];

            // Removes the opp char off the token
            tempString.pop_back();

            // Makes sure the token isn't blank before sending
            if (tempString.length() > 0) {
                sendToken(tokenType, tempString);
            }
            
            tempString = "";
            tokenType = "ID  ";


            // Extra steps if the opp is a char combo
            if (oppNum == 2) {
                tempOppStr += line[i + 1];

                i += 1;
            }

            // Sends the opp token
            sendToken("OPP ", tempOppStr);
        }
    }

    // Sends the remaining token
    if (tempString.length() > 0) {
        sendToken(tokenType, tempString);
    }

    // Line is over
    sendToken("ENDL", "");
}



void lexFile(string fileName) {
    std::fstream file;
    file.open(fileName, std::ios::in);


    std::string line;

    // Lexes each line
    while (std::getline(file, line)) {
        lexLine(line);
    }

    // Prints out the token info
    for (Token token : tokens) {
        std::cout << "[" << token.getType() << ": " << token.getText() << "]\n";
    }

}
