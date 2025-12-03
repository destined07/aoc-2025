#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    fstream obj("input1.txt");
    ll ans = 0;
    string s;
    while(getline(obj,s)){
        int n = s.length();
        string temp = s.substr(0,2);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                string t = "";
                t+=s[i], t+=s[j];
                if(t>temp) temp=t;         
            }
        }
        ans += stoi(temp);
    }
    cout<<ans<<'\n';
}