#include<bits/stdc++.h>
using namespace std;
#define ll long long

/*
    poorly framed question... debugged the whole time only to find out that the question meant to say-
                Make the ten shortest connections "including skipped ones".
*/

struct dsu{
    int n;
    vector<int> parent, size;
    
    dsu(int n){
        this->n=n;
        parent.assign(n+1,1), size.assign(n+1,1);
        for(int i=1;i<=n;i++) parent[i]=i;
    }

    int find(int node){
        if(parent[node] == node) return node;
        return parent[node] = find(parent[node]);
    }

    void Union(int a,int b){
        a=find(a), b=find(b);
        if(a!=b){
            if(size[a] > size[b]) swap(a,b);
            parent[a] = b;
            size[b] += size[a];
        }
    }
};

inline ll get(vector<ll> &p1, vector<ll> &p2){
    ll a=abs(p1[0]-p2[0]), b=abs(p1[1]-p2[1]), c=abs(p1[2]-p2[2]);
    a*=a; b*=b; c*=c;
    return a+b+c; 
}

int main(){
    fstream obj("input.txt");
    string s; 

    vector<vector<ll>> points;
    while(getline(obj,s)){
        int n = s.length();
        string temp = "";
        vector<ll> curr;
        for(int i=0;i<n;i++){
            if(s[i]==','){
                curr.push_back(stoll(temp));
                temp.clear();
            }
            else temp.push_back(s[i]);
        }
        curr.push_back(stoll(temp));
        points.push_back(curr);
    }
    int n = points.size();

    vector<vector<ll>> dist; // d, p1, p2 (1-based)
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            ll d = get(points[i],points[j]);
            dist.push_back({d, i+1, j+1});
        }
    }
    sort(dist.begin(), dist.end());
    
    dsu Dsu(n);

    for(int i=0; i<1000; i++){
        int p1 = dist[i][1], p2 = dist[i][2];
        if(Dsu.find(p1) != Dsu.find(p2)){
            Dsu.Union(p1,p2);
        }
    }

    map<ll,ll> mp;
    for(int i=1;i<=n;i++){
        mp[Dsu.find(i)]++;
    }
    
    // Top 3 sizes
    vector<ll> temp;
    for(auto &i:mp) temp.push_back(i.second);
    sort(temp.rbegin(), temp.rend());

    ll ans = temp[0] * temp[1] * temp[2];
    cout << ans << '\n';
}
