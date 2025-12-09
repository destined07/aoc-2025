#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
                Converted my friends Python code to c++ by LLM
                This is not my code will try later after exams... 
                My naive approach made the computer crash...
    Need to have knowledge about coordinate compression and other techniques to solve this one
                Also do the remaining days after the exams....

*/



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream in("input1.txt");
    if(!in.is_open()){
        cerr << "input.txt not found\n";
        return 1;
    }

    // Read original points as (x,y) pairs (x = column, y = row)
    vector<pair<ll,ll>> pts;
    string line;
    while (getline(in, line)) {
        if(line.empty()) continue;
        size_t p = line.find(',');
        if(p==string::npos) continue;
        ll x = stoll(line.substr(0,p));
        ll y = stoll(line.substr(p+1));
        pts.emplace_back(x,y);
    }
    in.close();

    ll n = pts.size();
    if(n < 2){
        cout << 0 << '\n';
        return 0;
    }

    // ----------------------------------------------------------------
    // Build coordinate compression arrays WITH boundaries:
    // include x, x+1 for each point and add one layer outside so floodfill outside works
    // ----------------------------------------------------------------
    vector<ll> xs, ys;
    xs.reserve(2*n + 4);
    ys.reserve(2*n + 4);

    ll minx = pts[0].first, maxx = pts[0].first;
    ll miny = pts[0].second, maxy = pts[0].second;
    for(auto &p: pts){
        minx = min(minx, p.first);
        maxx = max(maxx, p.first);
        miny = min(miny, p.second);
        maxy = max(maxy, p.second);
        xs.push_back(p.first);
        xs.push_back(p.first + 1);
        ys.push_back(p.second);
        ys.push_back(p.second + 1);
    }
    // Add outside padding so floodfill from outside is possible
    xs.push_back(minx - 1);
    xs.push_back(maxx + 2);
    xs.push_back(minx);      // ensure minx boundary exists
    ys.push_back(miny - 1);
    ys.push_back(maxy + 2);
    ys.push_back(miny);

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    // compressed grid size = intervals count = xs.size()-1 by ys.size()-1
    int C = (int)xs.size() - 1;
    int R = (int)ys.size() - 1;
    if(R <= 0 || C <= 0){
        cout << 0 << '\n';
        return 0;
    }

    // helper: map original integer coord to compressed interval index i such that
    // xs[i] <= coord < xs[i+1]
    auto idx_x = [&](ll x)->int {
        int i = int(lower_bound(xs.begin(), xs.end(), x+1) - xs.begin()) - 1;
        if(i < 0) i = 0;
        if(i >= C) i = C-1;
        return i;
    };
    auto idx_y = [&](ll y)->int {
        int j = int(lower_bound(ys.begin(), ys.end(), y+1) - ys.begin()) - 1;
        if(j < 0) j = 0;
        if(j >= R) j = R-1;
        return j;
    };

    // grid cells: grid[r][c] corresponds to original tiles with
    // x in [xs[c], xs[c+1]-1], y in [ys[r], ys[r+1]-1]
    // 0 = dot, 1 = boundary (edge or red), we'll also keep a set of compressed cells that contain red tile(s)
    vector<vector<char>> grid(R, vector<char>(C, 0)); // 0 = dot, 1 = boundary/edge
    vector<vector<char>> isRed(R, vector<char>(C, 0)); // 1 if this compressed cell contains an original red tile

    // Mark red tile positions in compressed coordinates (may share a compressed block with others)
    vector<pair<int,int>> cpts; cpts.reserve(n);
    for(auto &p: pts){
        int cx = idx_x(p.first);
        int cy = idx_y(p.second);
        cpts.emplace_back(cy, cx); // (row, col)
        isRed[cy][cx] = 1;
        grid[cy][cx] = 1; // boundary at least where red exists
    }

    // Mark segments between consecutive red tiles (including wrap). They are guaranteed axis aligned.
    for(int i=0;i<(int)n;i++){
        auto p = pts[i];
        auto q = pts[(i+1)%n];
        ll x1 = p.first, y1 = p.second;
        ll x2 = q.first, y2 = q.second;

        if(y1 == y2){
            // horizontal segment on row y1, from a..b inclusive
            ll a = min(x1,x2), b = max(x1,x2);
            int row = idx_y(y1);
            // columns whose interval [xs[c], xs[c+1]-1] intersects [a,b]
            int cL = int(lower_bound(xs.begin(), xs.end(), a+1) - xs.begin()) - 1;
            int cR = int(lower_bound(xs.begin(), xs.end(), b+1) - xs.begin()) - 1;
            cL = max(0, cL); cR = min(C-1, cR);
            for(int c=cL;c<=cR;c++){
                grid[row][c] = 1;
            }
        } else if(x1 == x2){
            // vertical
            ll a = min(y1,y2), b = max(y1,y2);
            int col = idx_x(x1);
            int rL = int(lower_bound(ys.begin(), ys.end(), a+1) - ys.begin()) - 1;
            int rR = int(lower_bound(ys.begin(), ys.end(), b+1) - ys.begin()) - 1;
            rL = max(0, rL); rR = min(R-1, rR);
            for(int r=rL;r<=rR;r++){
                grid[r][col] = 1;
            }
        } else {
            // problem statement guarantees axis-aligned consecutive tiles
            cerr << "Non axis-aligned segment encountered\n";
            return 2;
        }
    }

    // Flood-fill from outside to find exterior compressed cells.
    // pick outside coordinate = (minx-1, miny-1) which we added earlier.
    int sx = idx_x(minx - 1);
    int sy = idx_y(miny - 1);
    vector<vector<char>> vis(R, vector<char>(C, 0));
    deque<pair<int,int>> dq;
    dq.emplace_back(sy, sx);
    vis[sy][sx] = 1;
    int dr[4] = {1,-1,0,0}, dc[4] = {0,0,1,-1};
    while(!dq.empty()){
        auto [r0,c0] = dq.front(); dq.pop_front();
        for(int k=0;k<4;k++){
            int nr=r0+dr[k], nc=c0+dc[k];
            if(nr<0||nr>=R||nc<0||nc>=C) continue;
            if(vis[nr][nc]) continue;
            if(grid[nr][nc]) continue; // boundary blocks outside flow
            vis[nr][nc] = 1;
            dq.emplace_back(nr,nc);
        }
    }

    // Any cell not visited and not already boundary is interior => fill it (mark as green/boundary)
    for(int r=0;r<R;r++){
        for(int c=0;c<C;c++){
            if(!vis[r][c]) grid[r][c] = 1; // interior or already boundary -> treat as non-dot
        }
    }

    // Build weighted prefix sum of DOT tiles in ORIGINAL units.
    // For each compressed cell (r,c) its original tile count = width * height
    vector<vector<long long>> pref(R+1, vector<long long>(C+1, 0));
    for(int r=0;r<R;r++){
        long long rowsum = 0;
        for(int c=0;c<C;c++){
            ll w = xs[c+1] - xs[c];   // number of original columns represented by this compressed column
            ll h = ys[r+1] - ys[r];   // number of original rows represented by this compressed row
            ll cellTiles = w * h;
            ll dotTiles = grid[r][c] ? 0 : cellTiles; // if grid[r][c]==1 then it's green/red => not dot
            rowsum += dotTiles;
            pref[r+1][c+1] = pref[r][c+1] + rowsum;
        }
    }

    auto rectDots = [&](int r1,int c1,int r2,int c2)->long long{
        if(r1>r2) swap(r1,r2);
        if(c1>c2) swap(c1,c2);
        return pref[r2+1][c2+1] - pref[r1][c2+1] - pref[r2+1][c1] + pref[r1][c1];
    };

    // Map original points to compressed coords again (safe mapping)
    vector<pair<int,int>> compPts; compPts.reserve(n);
    for(auto &p: pts){
        compPts.emplace_back(idx_y(p.second), idx_x(p.first));
    }

    // For every pair of original red tiles, check rectangle between them:
    long long ans = 0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            // only pairs that are opposite corners are allowed (they can be anywhere; requirement: opposite corners must be red)
            // compute original area
            ll x1 = pts[i].first, y1 = pts[i].second;
            ll x2 = pts[j].first, y2 = pts[j].second;
            ll area = (ll)llabs(x1 - x2) + 1;
            area *= ((ll)llabs(y1 - y2) + 1);
            if(area <= ans) continue;

            // compressed ranges covering original rectangle:
            int c1 = idx_x(min(x1,x2));
            int c2 = idx_x(max(x1,x2));
            int r1 = idx_y(min(y1,y2));
            int r2 = idx_y(max(y1,y2));

            // But idx_x/min mapping with min(...) ensures we start at correct compressed cells.
            // Check if any original tile inside rectangle is a dot by weighted prefix-sum
            long long dotsInside = rectDots(r1, c1, r2, c2);
            if(dotsInside == 0){
                ans = area;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
