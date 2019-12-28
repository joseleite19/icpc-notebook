#define private public
#include <bitset>
#undef private
#include <bits/stdc++.h>

using namespace std;

#define tab _M_w
using biti = typename remove_reference<decltype(bitset<404>().tab[0])>::type;
const int SIZE = 8 * sizeof(biti);
const int LOG = __builtin_ctz(SIZE);

template<size_t Nw>
int find_prev(const bitset<Nw> &x, int v) {
	int start = v >> LOG;
	int first_bits = v & (SIZE - 1);
	if(first_bits) {
		biti curr = x.tab[start];
		curr = curr << (SIZE - first_bits) >> (SIZE - first_bits);
		if(curr)
			return start << LOG | (SIZE - __builtin_clzl(curr) - 1);
	}
	for(int i = start - 1; i >= 0; i--) {
		biti curr = x.tab[i];
		if(curr) {
			return (i << LOG) | (SIZE - __builtin_clzl(curr) - 1);
		}
	}
	return -1;
}

// s._Find_first(); s._Find_next(k); find_prev(s, k+1);
// _Unchecked_set/_Unchecked_reset/_Unchecked_flip
