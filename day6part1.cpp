#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    fstream obj("input.txt");
    string s; 

    ll ans = 0;
    vector<vector<ll>> v;
    vector<char> op;
    while (getline(obj, s)) {
        vector<ll> row;
        bool isOpLine = false;

        string token = "";
        for (char ch : s) {
            if (isdigit(ch)) {
                token += ch;
            }
            else {
                if (!token.empty()) {
                    row.push_back(stoll(token));
                    token.clear();
                }
                if (ch == '*' || ch == '+') {
                    op.push_back(ch);
                    isOpLine = true;
                }
            }
        }

        if (!token.empty()) {
            row.push_back(stoll(token));
        }

        if (!isOpLine) {
            v.push_back(row);
        }
    }

    int r = v.size(), c=v[0].size();
    
    for(int c1=0;c1<c;c1++){
        ll curr=v[0][c1];
        for(int r1=1;r1<r;r1++){
            if(op[c1]=='*') curr*=v[r1][c1];
            else curr+=v[r1][c1];
        }
        ans += curr;
    }
    cout<<ans<<'\n';
}