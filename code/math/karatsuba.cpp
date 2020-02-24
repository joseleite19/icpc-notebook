// source https://codeforces.com/blog/entry/74209

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma") 
namespace {
    template<int n, typename T>
    void mult(const T *__restrict a, const T *__restrict b, T *__restrict res) {
        if (n <= 64) { // if length is small then naive multiplication if faster
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    res[i + j] += a[i] * b[j];
                }
            }
        } else {
            const int mid = n / 2;
            alignas(64) T btmp[n], E[n] = {};
            auto atmp = btmp + mid;
            for (int i = 0; i < mid; i++) {
                atmp[i] = a[i] + a[i + mid]; // atmp(x) - sum of two halfs a(x)
                btmp[i] = b[i] + b[i + mid]; // btmp(x) - sum of two halfs b(x)
            }
            mult<mid>(atmp, btmp, E); // Calculate E(x) = (alow(x) + ahigh(x)) * (blow(x) + bhigh(x))
            mult<mid>(a + 0, b + 0, res); // Calculate rlow(x) = alow(x) * blow(x)
            mult<mid>(a + mid, b + mid, res + n); // Calculate rhigh(x) = ahigh(x) * bhigh(x)
            for (int i = 0; i < mid; i++) { // Then, calculate rmid(x) = E(x) - rlow(x) - rhigh(x) and write in memory
                const auto tmp = res[i + mid];
                res[i + mid] += E[i] - res[i] - res[i + 2 * mid];
                res[i + 2 * mid] += E[i + mid] - tmp - res[i + 3 * mid];
            }
        }
    }
}
