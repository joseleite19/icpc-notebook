// x = vet[i].first (mod vet[i].second)
ll crt(vector<pair<ll, ll>> vet){

    ll ans = vet[0].first, lcm = vet[0].second;
    ll a, b, g, x, y;

    for(int i = 1; i < (int)vet.size(); i++){
        tie(a, b) = vet[i];
        tie(g, x, y) = gcd(lcm, b);
        ans = ans + x * (a - ans) / g % (b / g) * lcm;
        lcm = lcm * b / g;
        ans = (ans % lcm + lcm) % lcm;
    }

    return ans;
}
