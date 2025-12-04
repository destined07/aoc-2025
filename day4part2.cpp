#include<bits/stdc++.h>
using namespace std;
#define ll long long

int r,c;
vector<string> v;

inline bool isValid(int r1,int c1){return (r1<r && 0<=r1 && c1<c && 0<=c1);}

int main(){
    fstream obj("input.txt");
    string s;
    int cnt=0;
    while(getline(obj,s)) v.push_back(s);
    r = v.size(),c = v[0].size();

    vector<vector<int>> dirn = {{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}}; 

    int ans = 0;
    bool removed = false;
    do{
        removed = false;
        for(int r1=0;r1<r;r1++){
            for(int c1=0;c1<c;c1++){
                if(v[r1][c1]!='@') continue;
                int cnt = 0;
                for(auto &i:dirn){
                    int x = i[0]+r1,y=i[1]+c1;
                    if(isValid(x,y) && v[x][y]=='@') cnt++;
                }
                if(cnt<4){
                    v[r1][c1]='x';
                    ans ++;
                    removed = true;
                }
            }
        }
    }while(removed);
    cout<<ans<<'\n';
}
