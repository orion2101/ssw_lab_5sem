//
// Created by vovan on 28.09.2019.
//

#ifndef LECS_PARS_LEXEM_H
#define LECS_PARS_LEXEM_H

#include <string>


enum tokens {
    unknown_tk = -1,    // we get unknown token
    program_tk = 0,     // 'program'
    var_tk,             // 'var'
    begin_tk,           // 'begin'
    end_tk,             // 'end'
    type_tk,            // 'type'
    id_tk       = 8,    // any [aA-zZ][0-9]
    constant_tk = 9,    // 0-9
    bool_tk,            // true/false
    dot_tk,             // '.'
    comma_tk,           // ','
    ddt_tk,             // ':'
    semi_tk,            // ';'
    eqv_tk,             // '='
    ass_tk,             // ':='
    add_tk,             // '+'
    sub_tk,             // '-'
    mul_tk,             // '*'
    div_tk,             // '/'
    opb_tk,             // '('
    cpb_tk,             // ')'
    array_tk,           // array
    of_tk,              // of
    square_op_tk,       // [
    square_cl_tk,       // ]
    range_tk,           // ..

    eof_tk
};


enum errors {
    ALL_OK,          // No error, all OK
    UNKNOWN_LEXEM,   // Unknown lexeme
    EOF_ERR,         // End of file error
    MUST_BE_ID,      // Error: Must be identifier
    MUST_BE_DIGIT,   // Error: Must be digit value (0-9)
    MUST_BE_BOOL,    // Error: Must be true/false
    MUST_BE_SEMI,    // Error: Must be ';'
    MUST_BE_PROG,    // Error: Must be 'program'
    MUST_BE_COMMA,   // Error: Must be ','
    MUST_BE_TYPE,    // Error: Must be type of identifier
    MUST_BE_DOT,     // Error: Must be '.'
    MUST_BE_ASS,     // Error: Must be ':='
    DUPL_ID_ERR,     // Error: Duplicate declaration on identifier
    UNKNOWN_ID,      // Error: Undefined identifier
    MUST_BE_OF,      // Error: Must be 'of'
    MUST_BE_OS,      // Error: Must be (,[,],)
    // TODO: and also
};


class Lexem {
public:
    Lexem() : name(""), token(unknown_tk), line(0) {};
    Lexem(std::string &&t_name, tokens t_tok, int t_line) : name(t_name),
                                              token(t_tok), line(t_line) {};

    std::string GetName();
    tokens      GetToken();
    int         GetLine();
private:
    std::string name;
    tokens      token;
    int         line;
};


#endif //LECS_PARS_LEXEM_H
