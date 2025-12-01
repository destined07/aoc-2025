#include<iostream>
#include<fstream>
using namespace std;
int main(){
    fstream obj("input.txt");
    string s;
    int pos = 50,ans=0;
    while(getline(obj,s)){
        char ch = s[0];
        string n1 = "";
        int n=s.length(),prev=pos;
        bool ck = false;
        for(int i=1;i<n;i++) n1.push_back(s[i]);
        n = stoi(n1);

        if(ch == 'L') pos = (pos - n + 100)%100;
        else pos = (pos + n )%100;
        if(!pos) ans++;
    }
    cout<<ans<<'\n';
}