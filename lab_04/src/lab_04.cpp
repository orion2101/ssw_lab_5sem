//
// Created by vldmr on 05.11.19.
//

#include "lab_04.h"


int Parse4(const std::string& file_path) {
    std::cout << "\tPart 4" << std::endl;

    Lexer lex(file_path.c_str());
    auto table = lex.ScanCode();

    Syntax syntx(std::move(table));
    auto tree = syntx.ParseCode();
    if (tree == nullptr) {
        std::cerr << "<E> Incorrect syntax tree, abort!" << std::endl;
        return -EXIT_FAILURE;
    }

    GenCode genCode(std::move(*tree));
    genCode.GenerateAsm();

    return EXIT_SUCCESS;
}
