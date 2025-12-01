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
        
        // int times = 0;
        // if(ch == 'L'){
        //     times = (prev + n) / 100;            
        //     pos = (pos - (n%100) + 100)%100;
        // }
        // else{
        //     times = (n + prev)/100;
        //     pos = (pos + n%100 )%100;
        // }
        // times=max(0,times);
        
        // ans += times;
        // if(!pos) ans++;                              // will fix this..
        
        for(int i=1;i<=n;i++){                          //bruteforce
            if(ch=='L') pos = (pos-1+100)%100;
            else pos = (pos+1+100)%100;
            ans += (!pos);
        }
    }
    cout<<ans<<'\n';
}
