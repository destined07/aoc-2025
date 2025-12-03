#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool invalid(ll i){
    string s1 = to_string(i);
    ll n = s1.length(),i2=n/2;
    if(n%2!=0) return false;
    
    while(i2<n){
        if(s1[i2]!=s1[i2-n/2]) return false;
        i2++;
    }

    return true;
}

int main(){
    fstream obj("input1.txt");
    string s;
    ll idx = 0,prev,curr,ans=0,ns;
    getline(obj,s);
    ns = s.length();
    while(idx<ns){
        string n1 = "";
        while(idx<ns && (s[idx]>='0' && s[idx]<='9')){
            n1.push_back(s[idx]);
            idx++;
        }
        curr = stoll(n1);
        
        if(idx==ns || s[idx]==','){
            for(ll i=prev;i<=curr;i++){
                if(invalid(i)){
                    ans+=i;
                }
            }
        }

        idx++;
        prev=curr;
    }
    cout<<ans<<'\n';
}