#include <string>
#include <iostream>



// Checks if a char is a char used in IDs
static bool isIDChar(char testChar) {
    // True if char is from alphabet
    if (isalpha(testChar)) {
        return true;
    }

    const char otherChars[] = {'_', '-'};

    // True if char is one of predefined chars
    for (char c : otherChars) {
        if (testChar == c) {
            return true;
        }
    }

    // False if any other char
    return false;
}

// Checks if the next Token is an ID
static int isID(std::string str, int startingIndex) {

    // Bool to make sure the token contains at least 1 id char and not just numbers
    bool contIDChar = false;

    for (int i = startingIndex; i < str.length(); i++) {
        // Sets IDChar Var if it contains one
        // Returns the length of token if char is neither id char or digit
        if (isIDChar(str[i])) {
            contIDChar = true;
        }
        else if (!isdigit(str[i])) {
            if (contIDChar) {
                return i - startingIndex;
            }
            else {
                return 0;
            }
        }
    }

    // Returns the length if it contains an ID Char and it reached the end of the line
    if (contIDChar) {
        return str.length() - startingIndex;
    }

    return 0;
}

// Checks if the string from the index to the next blank is a number
// Returns 0 if it is not a number
static int isNum(std::string str, int startingIndex) {

    // Stops if the preceding char is a letter
    if (startingIndex != 0) {
        if (isIDChar(str[startingIndex - 1])) {
            return 0;
        }
    }

    // Checks if it is not directly connected to an ID Char
    // Returns when the number is over
    for (int i = startingIndex; i < str.length(); i++) {
        if (isIDChar(str[i])) {
            return 0;
        }

        if (!isdigit(str[i])) {
            return i - startingIndex;
        }
    }
    
    // Returns if the number lasted to the end of the line
    return str.length() - startingIndex;
}

static int isOpp(std::string str, int startingIndex) {
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

static int isSyn(std::string str, int startingIndex) {

    const char synChars[] = {'(', ')', '{', '}', '[', ']', '\"', '\'', ',', '.'};

    // Checks if the char is a syntax char
    for (char c : synChars) {
        if (str[startingIndex] == c) {
            return 1;
        }
    }
    return 0;
}