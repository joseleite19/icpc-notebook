#include <random>
#include <chrono>
cout << RAND_MAX << endl;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
shuffle(p.begin(), p.end(), rng);
uniform_int_distribution<int>(a,b)(rng);
