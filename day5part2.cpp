#include<bits/stdc++.h>
using namespace std;
#define ll long long

// merge overlapping intervals

int main(){
    fstream obj("input.txt");
    string s; 

    ll ans = 0;
    bool rg = true;
    vector<vector<ll>> ranges;
    while(getline(obj,s)){
        if(s.size()==0) break;

        string a="",b="";
        bool bb = false;
        for(char ch:s){
            if(ch=='-') {bb=true; continue;}
            if(bb) b.push_back(ch);
            else a.push_back(ch);
        }
        
        ranges.push_back({stoll(a),stoll(b)});
    }

    sort(ranges.begin(),ranges.end());

    ll l=0, r=0, n=ranges.size(), prevSt,prevEnd;

    while(r<n){
        l=r;
        prevSt=ranges[r][0], prevEnd=ranges[r][1];

        while(r<n && ranges[r][0]<=prevEnd){
            prevEnd = max(prevEnd,ranges[r][1]);
            r++;
        }

        ans += (prevEnd - prevSt + 1);
    }

    cout<<ans<<'\n';
}