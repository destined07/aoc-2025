#include<bits/stdc++.h>
using namespace std;
#define ll long long

    // Greedy solution exits.. will code that later..  
// ps for later reference- given number find the largest 12 digit number from any subsequence of given number

vector<vector<ll>> dp;

int main(){
    fstream obj("input1.txt");
    ll Ans = 0;
    string s;

    while(getline(obj,s)){
        int n = s.length();
        dp.assign(n, vector<ll>(13, -1));    
        for (int i = 0; i < n; i++) dp[i][0] = 0;
        dp[n-1][1] = (int(s[n-1]) - int('0'));  
        dp[n-1][1] = s[n-1] - '0';
        for(int idx = n-2; idx>=0; idx--){
            for(int rem = 0; rem<13; rem++){
                ll ans = -1;
                if(idx+1<n) ans = dp[idx+1][rem];
                if(rem-1 >= 0 && dp[idx+1][rem-1] >= 0){
                    if(dp[idx+1][rem-1]!=0){
                        string temp = to_string(dp[idx+1][rem-1]);
                        temp = s[idx] + temp;
                        ans = max(ans, stoll(temp));
                    }
                    else ans = max(ans, (ll)(s[idx] - '0'));
                }
                dp[idx][rem] = ans;
            }
        }
        Ans += dp[0][12];
    }

    cout << Ans << '\n';
}
