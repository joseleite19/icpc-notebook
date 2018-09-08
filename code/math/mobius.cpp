memset(mu, 0, sizeof mu);
mu[1] = 1;
for(int i = 1; i < N; i++)
    for(int j = i + i; j < N; j += i)
        mu[j] -= mu[i];
// g(n) = sum{f(d)} => f(n) = sum{mu(d)*g(n/d)}
