#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;
const char number = '8';
const char quit = 'q';
const char print = ';';
const string prompt = "> ";
const string result = "= ";
class Token{
public:
    char kind;
    double value;
    Token(char ch)
        :kind(ch),value(0){}
    Token(char ch,double val)
        :kind(ch),value(val){}
};
class Token_stream{
public: 
    Token_stream();
    Token get();
    void putback(Token t);
    void ignore(char c);
private: 
    bool full; //is there a Token in the buffer?
    Token buffer;
} extern ts; //just a declaration 
double primary();
double term();
double expression();

// class Variable{
// public:
//     string name;
//     double value;
//     Variable(string n, double v) : name(n),value(v){}
// } extern vector <Variable> var_table;

#endif