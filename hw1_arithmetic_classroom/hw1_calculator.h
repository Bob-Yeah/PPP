#ifndef HW1_CALCULATOR_H
#define HW1_CALCULATOR_H
#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;
enum _operator {LBRANCKET,ADD,SUB,MULTI,DIV,RBRANCKET,VALUE};
class Calculator{
    string equation;
    
    void doOp(_operator op, stack <double> &dataStack);
    enum _operator getOp(double &value,int &pos);
public:
    Calculator(string s_equation){
        equation=s_equation;
        // cout<<"create succeed";
    }
    void showString() {cout<<equation<<endl;}
    double result();
};
#endif