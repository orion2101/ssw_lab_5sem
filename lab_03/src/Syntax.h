#ifndef LECS_PARS_SYNTAX_H
#define LECS_PARS_SYNTAX_H

#include <algorithm>
#include <iostream>
#include <chrono>
#include <list>
#include <map>
#include <vector>
#include "Lexem.h"
#include "Variable.h"
#include "Tree.h"


class Syntax {
public:
    explicit Syntax(std::vector<Lexem> &&t_lex_table);
    int ParseCode();
    ~Syntax();
private:
    using lex_it = std::vector<Lexem>::iterator; // alias of vector iterator
    lex_it                          cursor;
    std::vector<Lexem>              lex_table;   // out table of lexemes
    std::map<std::string, Variable> id_map;      // our table of identifiers
    Tree                           *root_tree;

    std::map<std::string, int> operations;

    lex_it getNextLex(lex_it &iter);
    lex_it peekLex(int N, lex_it t_iter);


    int   expressionParse            (lex_it &t_iter, Tree *tree);
    Tree  *simplExprParse            (const lex_it &var_iter, lex_it &t_iter,
                                      Tree *tree);

    Tree* stateParse                 (lex_it &t_iter);
    Tree* compoundParse              (lex_it &t_iter);
    int   vardpParse                 (lex_it &t_iter, Tree *t_tree);
    std::list<std::string> vardParse (lex_it &t_iter);
    int   blockParse                 (lex_it &t_iter);
    int   programParse               (lex_it &t_iter);

    void printError    (errors t_err, Lexem lex);
    bool checkLexem    (const lex_it &t_iter, const tokens &t_tok);
    bool isVarExist    (const std::string &t_var_name);
    void updateVarTypes(const std::list<std::string> &t_var_list,
                        const std::string &t_type_name);
    void buildVarTree  (const std::list<std::string> &t_var_list, Tree *t_tree);

    void createVarTree(Tree *t_tree, Tree *t_donor_tree, int lvl);
    Tree* createLowestOpTree(Tree *t_parent_tree, std::string value);
};


#endif //LECS_PARS_SYNTAX_H
