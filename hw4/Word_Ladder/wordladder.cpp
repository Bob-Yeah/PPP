#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include <cctype>
using namespace std;

void printInst(){
    cout<<"Welcome to Word Ladder."<<endl
    <<"Please give me two words, and I will chage the"<<endl
    <<"first into the second by chaning one letter at a time."<<endl;
}

void toLowerString(string &str){
    transform(str.begin(),str.end(),str.begin(),::tolower);
}

void getDict(ifstream &ifs, unordered_set <string> &dictSet){
    while (ifs.good()){
        string word;
        getline(ifs,word);
        toLowerString(word);
        dictSet.insert(word);
    }
    
}

int checkWords(const string fromWord,const string toWord,const unordered_set <string> dictSet){
    if (dictSet.find(toWord)==dictSet.end() || dictSet.find(fromWord)==dictSet.end()) return 1;
    if (fromWord.length()!=toWord.length()) return 2;
    if (fromWord == toWord) return 3;
    return 0;
}

int countStringDis(const string str1,const string str2){
    int dis=0;
    if (str1.length()!=str2.length()) return -1;
    for (int i=0;i<str1.length();i++){
        if (str1[i]!=str2[i]) dis++;
    }
    return dis;
}

multimap <string,string> findNeighbour(const string home_string,const string toWord,
    unordered_set <string> &tempDict,int &flag){
        multimap <string,string> layerMap;
        stack <string> deleteWord;
        for (const string& it : tempDict) {
            if (countStringDis(home_string,it)==1){
                if (it == toWord) flag = 0;
                layerMap.insert(pair<string,string>(home_string,it));
                deleteWord.push(it);
            }
        }
        while (!deleteWord.empty()) {
            tempDict.erase(deleteWord.top());
            deleteWord.pop();
        }
        return layerMap;
}

stack <multimap <string,string>> getLadder(const string fromWord,const string toWord,
    const unordered_set <string> dictSet,int &flag){
        stack <multimap <string,string>> wordLadder;
        unordered_set <string> tempDict;
        for (auto it : dictSet) {
            if (it.length()==fromWord.length())
                tempDict.insert(it);
        }
        wordLadder.push(findNeighbour(fromWord,toWord,tempDict,flag));
        while (flag == -1){
            multimap <string,string> tempLayerMap;
            for (auto it = wordLadder.top().begin();it != wordLadder.top().end();it++){
                multimap <string,string> tempWordMap;
                tempWordMap=findNeighbour(it->second,toWord,tempDict,flag);
                tempLayerMap.insert(tempWordMap.begin(),tempWordMap.end());
            }
            if (((flag !=0) && (tempLayerMap.size()==0)) || (tempDict.size() ==0)) flag = 1;
            wordLadder.push(tempLayerMap);
        }
        return wordLadder;
}

void printLadder(stack <multimap <string,string>> &ladder,const string toWord){
    string curWord;
    curWord = toWord;
    cout<<  curWord <<" ";
    while(!ladder.empty()){
        for (auto it=ladder.top().begin();it!= ladder.top().end();it++){
            if(it->second == curWord) {
                cout << it->first << " ";
                curWord = it->first;
                ladder.pop();
                break;
            }
        }
    } 
}

int main(int argc, char ** argv){
    ifstream ifs;
    string dictName;
    string fromWord,toWord;
    unordered_set<string> dictSet;
    stack <multimap <string,string>> wordLadder;
    int flag=-1;
    while(true){
        cout<<"Dictionary file name? ";
        cin >> dictName;
        if (dictName.length()!=0){
            ifs.open(dictName,ifstream::in);
            if (!ifs.is_open()) {
                cout<<"Unable to open that file. Try again.\n";
                continue;
            }
            getDict(ifs,dictSet);
        }
        else continue;
        
        while(true){
            cout<<"Word #1 (or Enter to quit):";
            char quit=cin.get();    //eat \n  === 10
            quit=cin.get();
            if(quit!=10) cin.putback(quit);
            else {
                cout<<"Have a nice day!\n";
                return 0;
            }
            cin>>fromWord;
            cout<<"Word #2 (or Enter to quit):";
            quit=cin.get(); //eat \n === 10
            quit=cin.get();
            if(quit!=10) cin.putback(quit);
            else {
                cout<<"Have a nice day!\n";
                return 0;
            }
            cin>>toWord;
            toLowerString(fromWord);
            toLowerString(toWord);
            int status;
            if((status = checkWords(fromWord,toWord,dictSet))!=0){
                switch(status){
                    case 1: 
                        cout<<"The words must be found in the dictionary.\n";
                        continue;    
                    case 2:
                        cout<<"The two words must be the same length.\n";
                        continue;
                    case 3:
                        cout<<"The two words must be different.\n";
                        continue;
                    default:
                        cout<<"Unknown error!";
                        continue;
                }
            }
            wordLadder=getLadder(fromWord,toWord,dictSet,flag);
            if(flag!=0) {
                cout<<"No word ladder found from "<<toWord<<" back to "<<fromWord<<endl;
                flag = -1;
                continue;
            }
            cout<<"A ladder from " << toWord <<" to " << fromWord <<": \n";
            printLadder(wordLadder,toWord);
            cout<<endl;
            flag = -1;
        }
    }
    return 0;
}