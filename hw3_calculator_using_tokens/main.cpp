/*
    Simple calculator
    Author: Bob_Yeah
    A simple imitaion of Bjarne Stroustrup's work

    This program implements a basic expression calculator:
    Input from cin; output to cout.
    The garmmar for input is:
    Statement:
        Expression
        Print
        Quit
    Print:
        ;
    Quit:
        q
    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary
    Primary:
        Number
        ( Expression )
        - Primary
        + Primary
    Number:
        floating-point-literal

    Input comes from cin through the Token_stream called ts.
*/

#include "parser.h"
//global variables
Token_stream ts;
// vector <Variable> var_table;
double MR = 0;
void clean_up_mess() {
    ts.ignore(print);
}
void calculate(){

    do{
        try{
            cout<<prompt;
            Token t=ts.get();
            while (t.kind==print) t=ts.get(); //eat ;
            if (t.kind==quit) return ;
            else ts.putback(t);
            cout << result << expression() << endl;
        }
        catch (exception & e){
            cerr << e.what() <<endl;
            clean_up_mess();
        }
    
    }while(cin);
    
    
}
int main(int argc,char ** argv){
    try {
        calculate();
        return 0;
    }
    catch (exception &e){
        cerr << "out " << e.what() << endl;
        return 1;
    }
    catch (...){
        cerr << "exception \n";
        return 2;
    }
    return 0;
}