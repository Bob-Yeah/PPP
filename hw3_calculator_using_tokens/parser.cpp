#include "parser.h"
void error (string s){
    throw runtime_error(s);
}
void error (string s1,string s2){
    throw runtime_error(s1+s2);
}
int fac(int input){
    if (input==0) return 1;
    else return input*fac(input-1);
}
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
            case 'M':
                t = ts.get();
                MR = left;
                return left;
            default: 
                ts.putback(t);  //put t back into the token stream 
                return left;
        }
    }
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
            case '%':
            {
                double d=primary();
                int i1 = int(left);
                if (i1!=left) error("left-hand operand of % not int");
                int i2 = int(d);
                if (i2!=d) error("right-hand operand of % not int");
                if (i2==0) error("the operation %: divide by zero");
                left = i1%i2;
                t=ts.get();
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
    double re;
    switch(t.kind){
        case '(': 
        {
            re = expression();
            t=ts.get();
            if(t.kind!=')') {
                ts.putback(t); 
                error("')' expected");
            }
            break;
        }
        case number: 
            re = t.value;
            break;
        case '-':
            re = 0 - primary();
            break;
        case '+':
            re = 0 + primary();
            break;
        case 'R':
            re = MR;
            break;
        default: 
            error("primary expected");

    }
    t=ts.get();
    if (t.kind=='!') {
        int fac_temp = int(re);
        if (fac_temp != re || fac_temp < 0 ) error("no-interger or negative-interger factorial error");
        else re = fac(fac_temp); 
    }
    else ts.putback(t);
    return re;
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
        case quit:case print:
        case '(': case ')': 
        case '+': case '-': 
        case '*': case '/':case '%':case '!':
        case 'M': 
            return Token(ch);
        case '.':
        case '0': case '1': case '2': case '3': case '4': 
        case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch); //put digt back into the input Token_stream
            double val;
            cin >> val; //pls pay attention to the great advantage of cin
            return Token(number,val);
        }
        case 'R':{
            return Token(number,MR);

        }
        default: 
            error("Bad token");
    }
}

void Token_stream::ignore(char c){  //c represents the kind of Token
    //first look in buffer:
    if (full && c == buffer.kind){
        full = false;
        return;
    }
    full = false;

    //now search input:
    char ch = 0;
    while (cin >> ch)
        if (ch == c) return;
}