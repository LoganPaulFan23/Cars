#include "../h/Token.h"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

std::vector<Token> tokens = {};

void lexLine(string line) {
    std::cout << "line \n";

    Token token(line);

    tokens.push_back(token);
}

void lexFile(string fileName) {
    std::fstream file;
    file.open(fileName, std::ios::in);

    std::string line;

    while (std::getline(file, line)) {
        lexLine(line);
    }

    for (Token token : tokens) {
        std::cout << token.getText() << std::endl;
    }

}
