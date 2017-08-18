#include <iostream>
#include <string>
#include "parser.h"
using namespace std;
void error (string s){
    throw runtime_error(s);
}
void error (string s1,string s2){
    throw runtime_error(s1+s2);
}


double primary();
double term();
double expression();
Token_stream ts;
double expression(){
    double left = term();   //read and evaluate a term
    Token t = ts.get();     //get the next Token from the Token stream 
    while (true){
        switch(t.kind){
            case '+': 
                left += term(); //evaluate Term and Add
                t = ts.get();
                break;
            case '-':
                left -= term(); //evaluate Term and Sub
                t = ts.get();
                break;
            default: 
                ts.putback(t);  //put t back into the token stream 
                return left;
        }
    }
    return 0.0;
}

double term(){
    double left=primary();
    Token t =ts.get();  //get the next Token from the Token stream 
    while (true){
        switch(t.kind){
            case '*':
            {
                left *=primary();
                t=ts.get();
                break;
            }
            case '/':
            {
                double d=primary();
                if (d==0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
            default: 
                ts.putback(t);  //put t back into the Token stream 
                return left;
        }
    }
}

double primary(){
    Token t=ts.get();
    switch(t.kind){
        case '(': 
        {
            double d = expression();
            t=ts.get();
            if(t.kind!=')') error("')' expected");
        }
        case '8': 
            return t.value;
        default: 
            error("primary expected");

    }
}

Token_stream::Token_stream()
    :full(false),buffer(0){ //dummy token

    }

void Token_stream::putback(Token t){
    if (full) error("putback() into a full buffer"); //test if buffer is full
    buffer=t; //copy t to buffer
    full=true; //buffer is now full
}

Token Token_stream::get(){
    if (full) { //remove Token from buffer
        full=false;
        return buffer;
    }
    char ch;
    cin>>ch;
    switch(ch){
        case ';' : //for 'print'

        case 'q' : //for 'quit'

        case '(': case ')': case '+': case '-': case '*': case '/':
            return Token(ch);
        case '.':
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
        {
            cin.putback(ch); //put digt back into the input Token_stream
            double val;
            cin >> val; //pls pay attention to the great advantage of cin
            return Token('8',val);
        }
        default: 
            error("Bad token");
    }
}