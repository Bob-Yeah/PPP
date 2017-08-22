#include <string>
#include <iostream>
using namespace std;
void mystery(string a, string &b){
    a.erase(0,1);
    b += a[0];
    b.insert(3,"FOO");

}
int main(int argc,char ** argv){
    string a = "Stanford";
    string b = "Tree";
    mystery(a,b);
    cout<< a << " " << b <<endl;
    return 0;
}