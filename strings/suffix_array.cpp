// Suffix array
//
// Given a string s of length N, function suffix_array(s, N) computes an array
// of sorted suffixes: the i-th sorted suffix starts from index srt[i].second.
// Time complexity: O(N log^2 N)
//
// Function lcp(a, b) computes the length of longest common prefix of suffixes
// s[a..] and s[b..].
// Time complexity: O(log N)
//
// Constants to configure:
// - MAX is the maximum value of N
// - LG is ceil(log2(MAX)) + 1

const int MAX = 100100;
const int LG = 17 + 1;

int L;
pair<llint, int> srt[MAX];
llint buc[LG][MAX];

int lcp(int a, int b) {
	int ret = 0;
	for(int i = L-1; i >= 0; --i){
		int s = 1 << i;
		if (a+s <= N && b+s <= N && buc[i][a] == buc[i][b])
	  		a += s, b += s, ret += s;
	}
	return ret;
}

void suffix_array(char *s, int N){
	REP(i, N) buc[0][i] = s[i] + 1;

	for(L = 0; (1<<L) < 2*N; ++L){
		for(x = 0; x < N; x++) srt[x] = {buc[L][x] << 30, x};
		for (int x = (1<<L); x < N; x++) srt[x-(1<<L)].first += buc[L][x];
		sort(srt, srt+N);

		int pos = 1;
		for(x = 0; x < N; x++){
			pos += i && srt[i-1].first < srt[i].first;
			buc[L+1][srt[i].second] = pos;
		}
	}
}