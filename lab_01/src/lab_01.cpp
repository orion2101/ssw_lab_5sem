//
// Created by vldmr on 13.09.19.
//
#include "lab_01.h"


/**
 * Given grammar:
 * <Soft>        ::= program <id> ; <block> .
 * <block>       ::= <var part> <state part>
 * <var part>    ::= var <var dec> : <type> ;
 * <var dec>     ::= <id> { , <var dec> }
 * <state part>  ::= <compound>
 * <compound>    ::= begin <state> { ; <state> } end
 * <state>       ::= <assign> | <compound> | <your_other_operations>
 * <assign>      ::= <id> := <exp> ;
 * <exp>         ::= <id> | <constant>
 * <type>        ::= integer
 * <id>          ::= a-z
 * <constant>    ::= 0-9
 */
enum tokens {
    unknown_tk = -1,    // we get unknown token
    program_tk = 0,     // 'program'
    var_tk,             // 'var'
    begin_tk,           // 'begin'
    end_tk,             // 'end'
    type_tk,            // 'type'
    id_tk       = 8,    // any [aA-zZ][0-9]
    constant_tk = 9,    // 0-9
    dot_tk,             // '.'
    comma_tk,           // ','
    ddt_tk,             // ':'
    semi_tk,            // ';'
    eqv_tk,             // '='
    ass_tk              // ':='
    /**
     * TODO: Here is your +/-/etc tokens
     */
};

typedef std::pair<std::string, tokens> lexem;


struct synt_t {
    std::ifstream code;         // input stream of Pascal code

    char  GetCurrentCurs();     // get current character in stream
    lexem GetLex();             // get next lexem

    char  PeekChar(int n);      // peek on N symbols in stream
    lexem PeekLex(int n);       // peek N lexem;
private:
    char cursor { -1 };         // cursor of stream

    char getChar();            // get next character in stream
};


/**
 * @brief Get next character (symbol)
 * @param none
 *
 * @return current character
 * @note If stream is broken (eof or something), throw exception
 */
char synt_t::getChar() {
    if (code.fail()) {
        std::cerr << "<E> Can't read from the file" << std::endl;
        throw std::runtime_error("File doesn't available");
    }

    if (!code.eof()) {
        code >> std::noskipws >> cursor;
    } else {
        std::cerr << "<E> File is EOF early" << std::endl;
        throw std::runtime_error("File is EOF early");
    }

    return cursor;
}


/**
 * @brief Peek to forward in stream on @n symbols
 * @param[in] n - the number of symbols for peek
 *
 * @return symbol from stream
 * @return -1 - can't peek forward
 * @note Peek only forward
 */
char synt_t::PeekChar(int n) {
    try {
        char ch = -1;
        int curr_pos = code.tellg(); // get current position in stream

        code.seekg(curr_pos + n, code.beg); // set needed position in stream
        code >> std::noskipws >> ch;    // get character from stream with ' '
        code.seekg(curr_pos, code.beg); // return previous position in stream

        return ch;
    } catch (std::exception &exp) {
        std::cerr << "<E> Catch exception in " << __func__ << ": " << exp.what()
                  << std::endl;
        return -1;
    }
}


/**
 * @brief Get current value of cursor
 * @param none
 *
 * @return value of cursor
 */
char synt_t::GetCurrentCurs() {
    return cursor;
}


/**
 * @brief Get next lexem
 * @param none
 *
 * @return lexem value (token)
 */
lexem synt_t::GetLex() {
    try {
        auto ch = GetCurrentCurs();
        while (ch == -1 || ch == ' ' || ch == '\r' || ch == '\n' || ch == '\t') {
            ch = getChar();
        }

        auto isId = [](char ch) {
            return std::isalpha(static_cast<unsigned char>(ch)) ||
                   std::isdigit(static_cast<unsigned char>(ch));
        };


        std::string lex;
        if (std::isdigit(static_cast<unsigned char>(ch))) { // Constants (Numbers)
            while (std::isdigit(static_cast<unsigned char>(ch))) {
                lex += ch;
                ch = getChar();
            }

            return std::make_pair(lex, constant_tk);
        } else if (std::isalpha(static_cast<unsigned char>(ch))) { // Identificators
            while(isId(ch)) {
                lex += ch;
                ch = getChar();
            }

            if (lex == "program")      { return std::make_pair(lex, program_tk); }
            else if (lex == "var")     { return std::make_pair(lex, var_tk);     }
            else if (lex == "begin")   { return std::make_pair(lex, begin_tk);   }
            else if (lex == "integer") { return std::make_pair(lex, type_tk);    }
            else if (lex == "end")     { return std::make_pair(lex, end_tk);     }
            else { // it is ID
                return std::make_pair(lex, id_tk);
            }
        } else if (std::ispunct(static_cast<unsigned char>(ch))) { // Other symbols
            tokens tok;
            switch (ch) {
                case ',' : tok = comma_tk; break;
                case '.' : tok = dot_tk;   break;
                case ':' : tok = ddt_tk;   break;
                case ';' : tok = semi_tk;  break;
                case '=' : tok = eqv_tk;   break;
                default:
                    std::cerr << "<E> Unknown token " << ch << std::endl; break;
            }
            lex += ch;

            if (tok == ddt_tk) {
                ch = getChar();
                if (ch == '=') {
                    lex += ch;
                    tok = ass_tk;
                }
            }

            getChar(); // some kind of k o s t y l; here we look on \n
            return std::make_pair(lex, tok);
        } else {
            std::cerr << "<E> Unknown token " << ch << std::endl;
        }

        return std::make_pair("", unknown_tk);
    } catch (const std::exception &exp) {
        return std::make_pair("", unknown_tk);
    }
}


/**
 * @brief Peek to forward on the N lexem
 * @param[in] n - the number of skipped tokens
 *
 * @return N-th lexem (token)
 * @note Return cursor of stream to previous position
 */
lexem synt_t::PeekLex(int n) {
    int curr_pos   = code.tellg(); // get current position in stream
    auto curr_curs = GetCurrentCurs();
    try {
        lexem res;
        for (int i = 0; i < n; i++) {
            res = GetLex();
        }
        code.seekg(curr_pos, code.beg);
        cursor = curr_curs;

        return res;
    } catch (const std::exception &exp) {
        std::cerr << "<E> You try to peek too much forward, get back" << std::endl;
        code.seekg(curr_pos, code.beg);
        cursor = curr_curs;

        return std::make_pair("", unknown_tk);
    }
}

/********** prototypes of functions ***************/
void  buildTreeStub  (lexem lex);
int   expressionParse(lexem lex,  synt_t &parser);
int   stateParse     (lexem &lex, synt_t &parser);
int   compoundParse  (lexem lex,  synt_t &parser);
lexem vardParse      (lexem lex,  synt_t &parser);
int   blockParse     (lexem lex,  synt_t &parser);
int   programParse   (synt_t &parser);
/*************************************************/


/**
 * @brief Stub for building tree
 * @param[in] lex - current lexem
 *
 * @return none
 * @note: in future here you will be building tree node
 */
void buildTreeStub(lexem lex) {
    /*std::cout << "<D> stub, get lexem " << lex.first << " (" << lex.second << ")"
              << std::endl;*/
}


/**
 * @brief Parse expression part
 * @param[in]    lex    - current lexem
 * @param[inout] parser - our lexical and syntax analyzer
 *
 * @return  EXIT_SUCCESS - if expression part is matched to grammar
 * @return -EXIT_FAILURE - if expression part doesn't matched to grammar
 */
int expressionParse(lexem lex, synt_t &parser) {
    lex = parser.GetLex();
    switch(lex.second) {
        case id_tk:
        case constant_tk: {
            /**
             * TODO: Here you have to check existence of operations (+/-/etc)
             */

            buildTreeStub(lex); // Here is your future Tree realization
            break;
        }
        default: {
            std::cerr << "<E> Must be identificator or constant or '-' or '('"
                      << std::endl;
            return -EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}


/**
 * @brief Parse state part
 * @param[in]    lex    - current lexem
 * @param[inout] parser - our lexical and syntax analyzer
 *
 * @return  EXIT_SUCCESS - if state part is matched to grammar
 * @return -EXIT_FAILURE - if state part doesn't matched to grammar
 */
int stateParse(lexem &lex, synt_t &parser) {
    lex = parser.GetLex();
    switch(lex.second) {
        case id_tk: { // a := b (assign part)
            /**
             * TODO: Here you have to check existence of variable
             */

            lex = parser.GetLex();
            if (lex.second != ass_tk) {
                std::cerr << "<E> := is absent" << std::endl;
                return -EXIT_FAILURE;
            }

            expressionParse(lex, parser);

            lex = parser.GetLex();
            if (lex.second != semi_tk) {
                std::cerr << "<E> ; is absent" << std::endl;
                return -EXIT_FAILURE;
            }
            break;
        }
        case begin_tk: { // compound statements
            compoundParse(lex, parser);
            lex = parser.GetLex();
            if (lex.second != semi_tk) {
                std::cerr << "<E> ';' is absent" << std::endl;
                return -EXIT_FAILURE;
            }
            break;
        }
        default: {

            break;
        }
    }

    return EXIT_SUCCESS;
}


/**
 * @brief Parse compound part
 * @param[in]    lex    - current lexem
 * @param[inout] parser - our lexical and syntax analyzer
 *
 * @return  EXIT_SUCCESS - if compound part is matched to grammar
 * @return -EXIT_FAILURE - if compound part doesn't matched to grammar
 */
int compoundParse(lexem lex, synt_t &parser) {
    static int compound_count = 0;
    compound_count++;
    while (lex.second != end_tk) {
        buildTreeStub(lex); // Here is your Tree realization
        if (parser.code.eof()) {
            std::cerr << "<E> Each begin must be closed by 'end'" << std::endl;
            return -EXIT_FAILURE;
        }
        stateParse(lex, parser);
    }

    if (compound_count == 1) {
        if (parser.PeekLex(1).second == unknown_tk) {
            std::cerr << "<E> '.' is absent" << std::endl;
            return -EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}


/**
 * @brief Parse variable declaration part
 * @param[in]    lex    - current lexem
 * @param[inout] parser - our lexical and syntax analyzer
 *
 * @return lexem - last parsed lexem (will actually return ':')
 */
lexem vardParse(lexem lex, synt_t &parser) {
    lex = parser.GetLex();
    if (lex.second != id_tk) {
        std::cerr << "<E> Here must be identificator" << std::endl;
        return lex;
    }

    /**
     *  TODO: Here save list of identificators
     */

    lex = parser.GetLex();
    if (lex.second == comma_tk)
        return vardParse(lex, parser); // Раскручивая стек обратно,
                                       // будет возвращено последнее значение

    return lex;
}


/**
 * @brief Parse block part
 * @param[in]    lex    - current lexem
 * @param[inout] parser - our lexical and syntax analyzer
 *
 * @return  EXIT_SUCCESS - if block part is matched to grammar
 * @return -EXIT_FAILURE - if block part doesn't matched to grammar
 * @return 1 - we get last lexem ('.'), end of parse
 */
int blockParse(lexem lex, synt_t &parser) {
    lex = parser.GetLex();
    switch(lex.second) { // var / begin
        case var_tk: {   // var a, b: integer;
            lex = vardParse(lex, parser);
            if (lex.second != ddt_tk)
                std::cerr << "<E> : is absent" << std::endl;

            lex = parser.GetLex();
            if (lex.second != type_tk)
                std::cerr << "<E> Identificator must have type" << std::endl;

            lex = parser.GetLex();
            if (lex.second != semi_tk) {
                std::cerr << "<E> ; is absent" << std::endl;
                return -EXIT_FAILURE;
            }

            buildTreeStub(lex); // Here is your Tree realization

            break;
        }
        case begin_tk: {
            compoundParse(lex, parser);
            break;
        }
        case dot_tk: {
            std::cout << "Program was parse successfully" << std::endl;
            return 1;
        }
        default: {
            std::cerr << "<E> Unknown lexem" << std::endl;
            return -EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}


/**
 * @brief Entry point in grammar
 * @param[inout] parser - our lexical and syntax analyzer
 *
 * @return  EXIT_SUCCESS - if input program part is correct
 * @return -EXIT_FAILURE - if input program part is incorrect
 * @note Wait input like: program <id_tk> ;
 */
int programParse(synt_t &parser) {
    auto lex = parser.GetLex();
    if (lex.second == program_tk) {
        lex = parser.GetLex();
        if (lex.second != id_tk) {
            std::cerr << "<E> Name of program is absent" << std::endl;
            if (lex.second != semi_tk) {
                std::cerr << "<E> ; is absent" << std::endl;
                return -EXIT_FAILURE;
            }
        }

        lex = parser.GetLex();
        if (lex.second != semi_tk) {
            std::cerr << "<E> ; is absent" << std::endl;
            return -EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    } else {
        std::cerr << "<E> Undefined type of program" << std::endl;
        return -EXIT_FAILURE;
    }
}


/**
 * @brief Start parse incoming pascal file
 * @param[in] file_path - path to a pascal file (code.p)
 *
 * @return  EXIT_SUCCESS - if file was successful parsed
 * @return -EXIT_FAILURE - if can't parse incoming file
 */
int Parse2(const std::string &file_path) {
    try {
        synt_t example_synt;

        example_synt.code.open(file_path);
        if (!example_synt.code.is_open()) {
            std::cerr << "<E> Can't open file" << std::endl;
            return -EXIT_FAILURE;
        }

        if (programParse(example_synt) != 0) {
            example_synt.code.close();
            return -EXIT_FAILURE;
        }

        lexem lex;
        while (!example_synt.code.eof() && !example_synt.code.fail()) {
            if (blockParse(lex, example_synt) == 1)
                break;
        }

        example_synt.code.close();
        return EXIT_SUCCESS;
    } catch (const std::exception &exp) {
        std::cerr << "<E> Catch exception in " << __func__ << ": " << exp.what()
                  << std::endl;
        return -EXIT_FAILURE;
    }
}


/**
 * What you have to do:
 *  - rewrite synt structure (set more encapsulated);
 *  - add struct for work with variables;
 *  - add variable check (check of existen);
 *  - add + and - operations (with variadic number of values);
 *  - add function of error information (must pass the number line of code
 *      with error, type of error);
 *  - rewrite work with table of lexemes (get lexemes directly from table);
 *  - implement all TODO tips (start with 'TODO: Here you have to ...')
 */
