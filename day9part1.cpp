#include<bits/stdc++.h>
using namespace std;
#define ll long long
//i/p  c,r   0-based

int main(){
    fstream obj("input.txt");
    string s; 
    vector<pair<ll,ll>> v;
    
    while(getline(obj,s)){
        int n = s.length();
        string curr="";
        pair<ll,ll> temp;
        for(int i=0;i<n;i++){
            if(s[i]==','){
                temp.first = stoll(curr);
                curr="";
            }
            else curr.push_back(s[i]);
        }
        temp.second = stoll(curr);
        v.push_back(temp);
    }
    // for(auto i:v) cout<<i.first<<" "<<i.second<<'\n';
    int n = v.size();
    ll ans = 0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            ll x1=v[i].first, y1=v[i].second, x2=v[j].first, y2=v[j].second;
            // cout<<x1<<","<<y1<<" & "<<x2<<","<<y2<<" "<<(abs(x1-x2)+1)*(abs(y1-y2)+1)<<'\n';
            ans = max((abs(x1-x2)+1)*(abs(y1-y2)+1), ans);
        }
    }
    cout<<ans<<'\n';
}