const ll MAX = 1e9;
const int LOG_MAX = 64 - __builtin_clzll((ll)MAX);

struct gauss {
    array<ll, LOG_MAX> vet;
    gauss(){}
    gauss(ll val) {
        add(val);
    }
    bool add(ll val) {
        int sig = LOG_MAX;
        for(int i = 0; i < LOG_MAX; i++) if(val & (1LL << i)) {
            if(!vet[i]) {
                vet[i] = val;
                return true;
            }
            val ^= vet[i];
        }
        return false;
    }
};
