//
// Created by vovan on 28.09.2019.
//

#include "Lexem.h"


/**
 * @brief Return name of lexeme
 * @param none
 *
 * @return name of lexeme
 */
const std::string& Lexem::GetName() const {
    return name;
}


/**
 * @brief Return type of lexeme
 * @param none
 *
 * @return type (token) of lexeme
 */
tokens Lexem::GetToken() const {
    return token;
}


/**
 * @brief Return line (from pascal file) of lexeme
 * @param none
 *
 * @return line of lexeme
 */
int Lexem::GetLine() const {
    return line;
}
