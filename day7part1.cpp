#include<bits/stdc++.h>
using namespace std;
#define ll long long

vector<string> v;
int r,c;

int solve(int r1, vector<bool> prevb){
    if(r1==r) return 0;
    
    int ans = 0;
    vector<bool> nextb(c,false);
    for(int i=0;i<c;i++){
        if(prevb[i]){
            if(v[r1][i]=='^'){
                ans++;
                if(i-1>=0) nextb[i-1]=true;
                if(i+1<c) nextb[i+1]=true;
            }
            else nextb[i]=true;
        }
    }

    return ans + solve(r1+1,nextb);
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

    vector<bool> beam(c,false);
    beam[st]=true;


    for(auto i:beam) cout<<i<<" "; cout<<'\n';

    cout << solve(1,beam) <<'\n';

}