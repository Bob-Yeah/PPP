/*The error detection is too complicated which can be simplified.*/
#include <iostream>
#include <string>
#include <stack>
#include <limits>
#include <math.h>
#include "hw1_calculator.h"
using namespace std;

int main(int argc,char **argv){
  int CheckValidity(string &s_equation);
  string input_equation;
  while  (true) {
    cout<<"> ";
    getline(cin,input_equation);
    if (CheckValidity(input_equation)==0) {
      Calculator eqt(input_equation);
      // eqt.showString();
      double result = eqt.result();
      if (!isfinite(result)) cout<<"division by 0\n";
      else cout<< result << endl;
    }
    else {
      if (CheckValidity(input_equation)==-1) cout<<"invalid input\n";
      if (CheckValidity(input_equation)==-2) cout<<"division by 0\n";
      if (CheckValidity(input_equation)==-3) cout<<"can't handle this by now\n";
    }
  }
  return 0;
}



int CheckValidity(string &s_equation){
  //delete all the blank space in the equation:
  size_t blank_pos=s_equation.find(" ");
  while (blank_pos!=string::npos){
    s_equation.replace(blank_pos,1,"");
    blank_pos=s_equation.find(" ");
  }
  int num_lbracket=0, num_rbracket=0;
  //CheckValidity:
  for (int i=0;i<s_equation.length();i++){
    if((s_equation[i] > '9' || s_equation[i] < '0')
      && s_equation[i] != '+' && s_equation[i] != '-' && s_equation[i] != '*' && s_equation[i] != '/'
      && s_equation[i] != '(' && s_equation[i] != ')')
      return -1;
    else {
      if(s_equation[i] == '+' || s_equation[i] == '-'){
        if (i!=0 && i!=s_equation.length()-1){
          if (s_equation[i-1] == '+' || s_equation[i-1] == '-' 
          ||s_equation[i-1] == '*' || s_equation[i-1] == '/' 
          || s_equation[i+1] == '+' || s_equation[i+1] == '-' 
          ||s_equation[i+1] == '*' || s_equation[i+1] == '/' )
          return -1;
          if (s_equation[i-1]=='(') s_equation.insert(i,"0");
        }
        else{
          if (i==0){
            if(s_equation[i+1] == '+' || s_equation[i+1] == '-' 
            ||s_equation[i+1] == '*' || s_equation[i+1] == '/' )
              return -1;
            else s_equation.insert(i,"0");
          }
          else return -1;
        }
      }
      else if (s_equation[i]=='*' || s_equation[i]=='/') {
        if (i==0 || i==s_equation.length()-1) return -1;
        else {
          if (s_equation[i-1] == '+' || s_equation[i-1] == '-' 
          ||s_equation[i-1] == '*' || s_equation[i-1] == '/' || s_equation[i-1] == '('
          || s_equation[i+1] == '+' || s_equation[i+1] == '-' 
          ||s_equation[i+1] == '*' || s_equation[i+1] == '/' || s_equation[i+1] == ')')
          return -1;
          if (s_equation[i] == '/' && s_equation[i+1] == '0' ) return -2;
        }
      }
      else if (s_equation[i]=='('){
        num_lbracket++;
        if (i==s_equation.length()-1) return -1;
        else if (i!=0) {
          if ((s_equation[i-1] >='0' && s_equation[i-1] <='9') 
          ||s_equation[i+1] == '*' || s_equation[i+1] == '/' || s_equation[i+1] == ')')
          return -1;
          if ( s_equation[i+1]== '-' || s_equation[i+1] == '+')
          s_equation.insert(i+1,"0");
        }
        else if (i==0){
          if ( s_equation[i+1] == '*' || s_equation[i+1] == '/' || s_equation[i+1] == ')')
          return -1;
          if ( s_equation[i+1]== '-' || s_equation[i+1] == '+')
          s_equation.insert(i+1,"0");
        }
      }
      else if (s_equation[i]==')'){
        num_rbracket++;
        if (i==0) return -1;
        else if (i!=s_equation.length()-1) {
          if ((s_equation[i+1] >='0' && s_equation[i+1] <='9') 
          || s_equation[i-1] == '+' || s_equation[i-1] == '-' 
          ||s_equation[i-1] == '*' || s_equation[i-1] == '/' || s_equation[i-1] == '(')
          return -1;
        }
        else if (i==s_equation.length()-1){
          if (s_equation[i-1] == '+' || s_equation[i-1] == '-' 
          ||s_equation[i-1] == '*' || s_equation[i-1] == '/' || s_equation[i-1] == '(')
          return -1;
        }
      } 
    }
  }
  if (num_lbracket != num_rbracket) return -1;
  return 0;
}
