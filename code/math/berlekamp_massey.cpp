#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
    #define eprintf(...) {fprintf(stderr, __VA_ARGS__); fflush(stderr);}
#else
    #define eprintf(...) 42
#endif

using ll = long long;
using ld = long double;
using uint = unsigned int;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 998244353;

inline int sub(int a, int b)
{
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

inline int add(int a, int b)
{
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

inline int mult(int a, int b)
{
    return ((ll)a * b) % MOD;
}

inline int powmod(int a, int b)
{
    int ans = 1;
    while (b)
    {
        if (b & 1) ans = mult(ans, a);
        a = mult(a, a);
        b >>= 1;
    }
    return ans;
}

inline int inv(int a)
{
    return powmod(a, MOD - 2);
}

struct LinearRecurrence {
// given first 2 *m items init[0..2m-1], it will compute trans[0..m-1]
// trans[0..m] will satisfy init[m] = sum_{i=0}^{m-1} init[i] * trans[i]
    static vector<int> BerlekampMassey(vector<int> x) {
        vector<int> ls, cur;
        int lf, ld;
        for (int i = 0; i < (int)x.size(); i++) {
            ll t = 0;
            for (int j = 0; j < (int)cur.size(); j++)
                t = add(t, mult(cur[j], x[i - j - 1]));
            if (t == x[i]) continue;
            if (cur.empty()) {
                cur.resize(i + 1);
                lf = i;
                ld = sub(t, x[i]);
                continue;
            }
            int k = mult(sub(t, x[i]), inv(ld));
            vector<int> c(i - lf - 1);
            c.push_back(k);
            for (auto t : ls) {
                c.push_back(sub(0, mult(t, k)));
            }
            if (c.size() < cur.size()) c.resize(cur.size());
            for (int j = 0; j < (int)cur.size(); j++)
                c[j] = add(c[j], cur[j]);
            if (i - lf + (int)ls.size() >= (int)cur.size()) {
                ls = cur;
                lf = i;
                ld = sub(t, x[i]);
            }
            cur = c;
        }
        return cur;
    }

    LinearRecurrence(const vector<int> &s, const vector<int> &c):
        init(s), trans(c), m(s.size()) {}
    LinearRecurrence(const vector<int> &s) {
        trans = BerlekampMassey(s);
        m = trans.size();
        reverse(all(trans));
        init = {s.begin(), s.begin() + m};
    }
    int calc(ll n) {
        if (MOD == 1) return 0;
        if (n < m) return init[n];
        vector<int> v(m), u(m << 1);
        int msk = !!n;
        for (ll z = n; z > 1; z >>= 1) msk <<= 1;
        v[0] = 1;
        for (int x = 0; msk; msk >>= 1, x <<= 1) {
            fill_n(u.begin(), m * 2, 0);
            x |= !!(n & msk);
            if (x < m) u[x] = 1;
            else {// can be optimized by fft/ntt
                for (int i = 0; i < m; ++i) {
                    for (int j = 0, t = i + (x & 1); j < m; ++j, ++t) {
                        u[t] = add(u[t], mult(v[i], v[j]));
                    }
                }
                for (int i = m * 2 - 1; i >= m; --i) {
                    for (int j = 0, t = i - m; j < m; ++j, ++t) {
                        u[t] = add(u[t], mult(trans[j], u[i]));
                    }
                }
            }
            v = {u.begin(), u.begin() + m};
        }
        ll ret = 0;
        for (int i = 0; i < m; ++i) {
            ret = add(ret, mult(v[i], init[i]));
        }
        return ret;
    }

    vector<int> init, trans;
    int m;
};

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    auto res = LinearRecurrence::BerlekampMassey(a);
    printf("%d\n", (int)res.size());
    for (auto t : res) printf("%d ", t);
    printf("\n");
    return 0;
}

