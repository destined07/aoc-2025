#include<bits/stdc++.h>
using namespace std;
#define ll long long

vector<string> v;
int r,c;

vector<vector<ll>> dp;
/*
    for a particle we need to find the number of different ways it can split up ahead..
    it can either go left or right after hitting... 
    we need to find the distinct number of ways for a beam to complete it's journey...
    dp.. state- r, idx... each state will store the number of ways to split particle from this state ahead...
*/
ll solve(int r1, int idx){
    if(r1>=r || idx<0 || idx>=c) return 1;  //journey completed so add 1...

    if(dp[r1][idx]!=-1) return dp[r1][idx];

    ll ans = 0;

    if(r1+1 < r && v[r1+1][idx]=='^'){
        ans = solve(r1+1,idx-1) + solve(r1+1,idx+1);
    }
    else  ans = solve(r1+1,idx);

    return dp[r1][idx] = ans;
}

int main(){
    fstream obj("input.txt");
    string s; 

    while (getline(obj, s)) v.push_back(s);
    
    int st = 0;
    c=v[0].length(), r=v.size();
    
    for(int i=0; i<c; i++){
        if(v[0][i]=='S') {st=i; break;}
    }

    dp.resize(r,vector<ll>(c,-1));

    cout << solve(1,st) <<'\n';
}