#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    fstream obj("input1.txt");
    string s; 
    bool rg = true;
    vector<pair<ll,ll>> ranges;
    int ans = 0;
    while(getline(obj,s)){
        if(s.size()==0){
            cout<<"here\n";
            rg = false;
            continue;
        }
        if(rg){
            string a="",b="";
            bool bb = false;
            for(char ch:s){
                if(ch=='-') {bb=true; continue;}
                if(bb) b.push_back(ch);
                else a.push_back(ch);
            }
            ranges.push_back({stoll(a),stoll(b)});
        }
        else{
            ll t = stoll(s), n = ranges.size();
            for(int i=0; i<n; i++){
                if(t >= ranges[i].first && t <= ranges[i].second){
                    ans++;
                    break;
                }
            }
        }
    }
    cout<<ans<<'\n';
}