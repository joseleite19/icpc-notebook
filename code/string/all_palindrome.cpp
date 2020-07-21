// rad[2 * i] = largest palindrome cetered at char i
// rad[2 * i + 1] = largest palindrome cetered between chars i and i+i
void manacher(char *s, int n, int *rad) {
	static char t[2*MAX];
	int m = 2 * n - 1;

	for(int i = 0; i < m; i++) t[i] = -1;
	for(int i = 0; i < n; i++) t[2 * i] = s[i];

	int x = 0;
	rad[0] = 0; // <
	for(int i = 1; i < m; i++) {
		int &r = rad[i] = 0;
		if(i <= x+rad[x]) r = min(rad[x+x-i],x+rad[x]-i);
		while(i - r - 1 >= 0 and i + r + 1 < m and
			  t[i - r - 1] == t[i + r + 1]) ++r;
		if(i + r >= x + rad[x]) x = i;
	}

	for(int i = 0; i < m; i++) {
		if(i-rad[i] == 0 || i+rad[i] == m-1) ++rad[i];
	}
	// for(int i = 0; i < m; i++) rad[i] /= 2;
}
