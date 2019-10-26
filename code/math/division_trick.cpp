for(int l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    // n / x yields the same value for l <= x <= r
}
for(int l, r = n; r > 0; r = l - 1) {
    int tmp = (n + r - 1) / r;
    l = (n + tmp - 1) / tmp;
    // (n + x - 1) / x yields the same value for l <= x <= r
}
