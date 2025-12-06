#include<bits/stdc++.h>
using namespace std;
#define ll long long

                //Need to improve this code.. later...

int main(){
    fstream obj("input.txt");
    string s; 

    ll ans = 0;
    vector<vector<ll>> v;
    vector<char> op;
    vector<string> t;
    while (getline(obj, s)) {t.push_back(s);}
    for(char ch:t.back()){
        if(ch!=' ') op.push_back(ch);
    }

    int cnt = 0;
    vector<int> maxLen;
    for(char ch:t.back()){
        if(ch!=' '){
            if(cnt > 0) maxLen.push_back(cnt);
            cnt=0;
        }
        else cnt++;
    }
    cnt=0;
    int mm = 0;
    for(int r=0;r<t.size();r++){
        int n = t[r].size(),idx;
        for(idx=n-1;idx>=0;idx--){
            if(t[r][idx]==' ') break;
        }
        mm=max(mm,n-idx-1);
    }
    maxLen.push_back(mm);
    
    vector<pair<int,int>> prefSum;
    int prev = 0, curr=0;
    for(int i=0;i<maxLen.size();i++){
        curr += maxLen[i]-1;
        prefSum.push_back({curr,prev});
        curr+=2;
        prev=curr;
    }

    int r1=t.size()-1;
    int n = prefSum.size();
    for(int i=0;i<n;i++){
        int end=prefSum[i].first, st=prefSum[i].second;
        string temp = "";

        ll curr = 0;
        for(int idx=st;idx<=end;idx++){
            for(int r=0;r<r1;r++){
                if(t[r][idx]!=' ') temp.push_back(t[r][idx]);
            }

            if(op[i]=='*') curr= (!curr ? stoll(temp) : curr*stoll(temp));
            else curr += stoll(temp);

            temp.clear();
        }
        ans+=curr;

    }
    cout<<ans;
}