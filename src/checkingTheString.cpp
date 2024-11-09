#include "../include/checkingTheString.h"

bool checkingTheString(const std::string &str) {
    int open = 0, close = 0;
    
    if (str.length() > 100) throw std::invalid_argument("String limit");
    if (str.length() == 0) return true;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') open += 1;
        else if (str[i] == ')') close += 1;
        else throw std::invalid_argument("The string must consist only of '(' and ')'");

        if (close > open) break;
    }

    return open == close;
}
