#include<iostream> 
#include<string>
using namespace std;

string& trans(string& str) {
    char ch=str.at(0);
    if (ch >= 'a' && ch < 'z') {
       str.at(0)++;   
    }
    else if (ch == 'z') {
        str.at(0) = 'a';  
    }
    return str;
}

int main(void) {
    int i=0;
    string str[256];
    cin>>str[i++];
    while (str[i-1].at(0) != '*') {
        cout<<str<<endl;
        trans(str[i]);
        cout<<str<<endl;
        cin >> str[i++];
    }
}
