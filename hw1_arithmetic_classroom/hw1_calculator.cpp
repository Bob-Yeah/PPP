#include "hw1_calculator.h"
#include <iostream>
using namespace std;

void Calculator::doOp(_operator op, stack <double> &dataStack){
    double data1,data2;
    if (dataStack.empty()){
        cout<<"not enough data!"<<endl;
        return;
    }
    else {
        data2=dataStack.top();
        dataStack.pop();
    }
    if (dataStack.empty()){
        cerr<<"not enough data!";
        return;
    }
    else {
        data1=dataStack.top();
        dataStack.pop();
    }
    switch (op){
        case ADD:dataStack.push(data1+data2);break;
        case SUB:dataStack.push(data1-data2);break;
        case MULTI:dataStack.push(data1*data2);break;
        case DIV:dataStack.push(data1/data2);break;
    }
}

enum _operator Calculator::getOp(double & value,int &pos){
    while (pos<equation.length()){
        while (equation[pos]==' ') pos++;
        if (equation[pos]<='9' && equation[pos]>='0'){
            value=0;
            while (equation[pos]<='9' && equation[pos]>='0'){
                value=value*10.0+equation[pos]-'0';
                pos++;
            }
            return VALUE;
        }
        switch (equation[pos]){
            case '(': pos++;return LBRANCKET;
            case ')': pos++;return RBRANCKET;
            case '+': pos++;return ADD;
            case '-': pos++;return SUB;
            case '*': pos++;return MULTI;
            case '/': pos++;return DIV;
        }
    }
}

double Calculator::result(){
    int i = 0;
    double currentValue=0,resultValue;
    _operator currentOp,topOp;
    stack <double> dataStack;
    stack <_operator> opStack;
    string eqt=equation;
    // cout<<"in result:eqt: "<<eqt<<endl;
    while (i<eqt.length()){
        currentOp=getOp(currentValue,i);
        // cout<<"in result:currentOp: "<<currentOp<<" currentValue: "<<currentValue<<endl;
        switch(currentOp){
            case VALUE: dataStack.push(currentValue);break;
            case LBRANCKET: opStack.push(currentOp);break;
            case RBRANCKET: 
                topOp=opStack.top();
                opStack.pop();
                while(!opStack.empty() && topOp!=LBRANCKET){
                    doOp(topOp,dataStack);
                    topOp=opStack.top();
                    opStack.pop();
                }
                    
                if (topOp!=LBRANCKET) cout<<"invalid input(branckets don't meet)"<<endl;
                break;
            case MULTI: case DIV: 
                while (!opStack.empty()&& opStack.top()>=MULTI){
                    topOp=opStack.top();
                    opStack.pop();
                    doOp(topOp,dataStack);
                }
                    
                opStack.push(currentOp);
                break;
            case ADD: case SUB: 
                while (!opStack.empty() && opStack.top()!=LBRANCKET){
                    topOp=opStack.top();
                    opStack.pop();
                    doOp(topOp,dataStack);
                }
                opStack.push(currentOp);
                break;
        }
    }
    while (!opStack.empty()) {
        topOp=opStack.top();
        opStack.pop();
        doOp(topOp,dataStack);
    }
    if (dataStack.empty()) {
        cout<<"no result";
        return 0;
    }
    resultValue=dataStack.top();
    dataStack.pop();
    if (!dataStack.empty()){
        cout<<"not enough operators!Now::"<<resultValue<<endl;
        return 0;
    }
    return resultValue;
}

