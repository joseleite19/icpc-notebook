#include <bits/stdc++.h>

#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
#define mp make_pair

using namespace std;

const int N = 100005;

const double EPS = 1e-9;

int n;
int h[N], ht[N], c[N], ct[N], erased[N], id[N];

pair<double, double> H[N], C[N];

double getx(int *h, int *hc, int i, int j){
    return 1.0*(h[i] - h[j])/(hc[j] - hc[i]);
}

void cht(int *h, int *hc, pair<double, double> *H){
    for(int i = 0; i < n; i++) id[i] = i;

    sort(id, id+n, [=](int a, int b){
        if(hc[a] == hc[b]) return h[a] < h[b];
            return hc[a] < hc[b];
    });
    
    vector<int> v;

    for(int i = 0; i < n; i++){
        while(v.size() >= 1){
            
            bool taken = 0;
            double x3 = getx(h, hc, v[ v.size()-1], id[i]);
            if(x3 < EPS) taken = 1, v.pop_back();
            
            if(v.size() >= 2){
                double x1 = getx(h, hc, v[ v.size()-1], v[v.size()-2]);
                double x2 = getx(h, hc, v[ v.size()-2], id[i]);
                if(x2-EPS <= x1) v.pop_back();
                else break;
            }
            else if(!taken) break;
        }
        v.push_back(id[i]);
    }
    double last = 0;
    for(int i = 0; i < v.size(); i++){
        H[ v[i] ].ff = last;
        if(i+1 < v.size()) last = H[ v[i] ].ss = getx(h, hc, v[i], v[i+1]);
        else H[ v[i] ].ss = 1e50;
    }
}

int main(){

    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d %d %d %d", h+i, ht+i, c+i, ct+i), c[i] *= -1, ct[i] *= -1;

    {
        multiset<pair<int, int> > hh, cc;
        for(int i = 0; i < n; i++)
            hh.insert(mp(h[i], ht[i])),
            cc.count(mp(c[i], ct[i]));
        for(int i = 0; i < n; i++)
            if(hh.count(mp(h[i], ht[i])) > 1 || cc.count(mp(c[i], ct[i])) > 1)
                erased[i] = 1;
    }

    for(int i = 0; i < n; i++)
        H[i].ff = H[i].ss = C[i].ff = C[i].ss = -1;
    cht(h, ht, H);
    cht(c, ct, C);

    int ans = 0;

    for(int i = 0; i < n; i++) if(!erased[i]){
        if(H[i].ff == -1 || C[i].ff == -1) continue;
        double a = max(H[i].ff, C[i].ff);
        double b = min(H[i].ss, C[i].ss);
        if(a+EPS <= b){
            ans++;
        }
    }

    printf("%d\n", ans);

    return 0;
}
