#include <random>
#include <chrono>
cout << RAND_MAX << endl;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<int> permutation(N);
iota(permutation.begin(), permutation.end(), 0);
shuffle(permutation.begin(), permutation.end(), rng);
iota(permutation.begin(), permutation.end(), 0);
for(int i = 1; i < N; i++){
    swap(permutation[i], permutation[uniform_int_distribution<int>(0, i)(rng)]);
}
