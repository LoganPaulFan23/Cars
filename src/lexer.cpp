#include "../h/Token.h"
#include "../src/tokenDetermine.cpp"

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
            //sendToken("ENDL", "");
            return;
        }
    }

    // Stops lexing if it is blank
    if (blankLine) {
        return;
    }


    // Goes through each char in the line
    // May skip over chars if they are part of a multi-char token
    for (int i = 0; i < line.length(); i++) {
        int synLen, numLen, oppLen, idLen;

        // Checks if the char is blank
        if (line[i] == ' ') {

        }

        // Syntax is a single char and activates any time a syntax char shows up
        else if ((synLen = isSyn(line, i)) != 0) {

            std::string tempSynStr = "";
            tempSynStr += line[i];
            sendToken("SYN ", tempSynStr);
        }

        // IDs can contain letters, _s, -s, and numbers
        // Must contain at least one non number char
        else if ((idLen = isID(line, i)) != 0)  {
            std::string tempIDStr = "";

            int tempI = i;
            // Because there was already an incriment for the first char
            i -= 1;

            for (int j = 0; j < idLen; j++) {
                tempIDStr += line[tempI + j];
                i += 1;
            }

            // Sends the ID token
            sendToken("ID  ", tempIDStr);
        }

        // Numbers contain only digits and can not be touching an ID specified char
        else if ((numLen = isNum(line, i)) != 0) {

            std::string tempNumStr = "";

            int tempI = i;
            // Because there was already an incriment for the first char
            i -= 1;

            for (int j = 0; j < numLen; j++) {
                tempNumStr += line[tempI + j];
                i += 1;
            }

            // Sends the opp token
            sendToken("NUM ", tempNumStr);
        }

        // Opperations are 1 or 2 chars and activate any time they appear
        else if ((oppLen = isOpp(line, i)) != 0) {

            std::string tempOppStr = "";
            tempOppStr += line[i];

            // Extra steps if the opp is a char combo
            if (oppLen == 2) {
                tempOppStr += line[i + 1];

                i += 1;
            }

            // Sends the opp token
            sendToken("OPP ", tempOppStr);
        } 
        
        // Sends a unkown token when no other token types are found
        else {
            sendToken("UNK ", std::string(1, line[i]));
        }
    }

    // ---------------End of For Loop-------------------- //

    // Line is over
    sendToken("ENDL", "");
}



std::vector<Token> lexFile(string fileName) {
    std::fstream file;
    file.open(fileName, std::ios::in);


    std::string line;

    // Lexes each line
    while (std::getline(file, line)) {
        lexLine(line);
    }


    std::cout << "TOKENS: \n\n";
    // Prints out the token info
    for (Token token : tokens) {
        std::cout << "[" << token.getType() << ": " << token.getText() << "]\n";
    }
    std::cout << "\n";

    return tokens;
}
