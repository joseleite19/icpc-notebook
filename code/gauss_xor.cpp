const ll MAX = 1e9;
const int LOG_MAX = 64 - __builtin_clzll((ll)MAX);

struct Gauss {
    array<ll, LOG_MAX> vet;
    int size;
    Gauss() size(0) {}
    Gauss(vector<ll> vals) size(0) {
        for(ll val : vals) add(val);
    }
    bool add(ll val) {
        for(int i = 0; i < LOG_MAX; i++) if(val & (1LL << i)) {
            if(vet[i] == 0) {
                vet[i] = val;
                size++;
                return true;
            }
            val ^= vet[i];
        }
        return false;
    }
};
