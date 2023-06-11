#include <string>
using std::string;


class Token {
    public:
        Token(string p_text) {
            text = p_text;
        }

        string getText() const {
            return text;
        }

    private:
        string text;

};