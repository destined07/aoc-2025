#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define ll long long

bool invalid(ll i){
    string s1 = to_string(i);
    ll n = s1.length();

    for(int i=1;i<n;i++){
        if(n%i==0){
            string t1 = "";
            bool ck=true;
            for(int j=0;j<i;j++){
                t1.push_back(s1[j]);
            }
            for(int j=i;j<n;j++){
                if(s1[j%i]!=s1[j]) ck=false;
            }
            if(ck) return true;
        }
    }
    return false;

}

int main(){
    fstream obj("input.txt");
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
                if(invalid(i)) ans+=i;
            }
        }

        idx++;
        prev=curr;
    }
    cout<<ans<<'\n';
}