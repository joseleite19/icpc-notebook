const ll MAX = 1e9;
const ll LOG_MAX = 64 - __builtin_clzll((ll)MAX);

struct gauss{
    vector<ll> vet;
    gauss(){}
    gauss(ll val){
        if(val) vet.push_back(val);
    }
    void add(ll val){
        int sig = LOG_MAX;
        for(int i = 0; i < (int)vet.size(); i++){
            while(!(vet[i] & (1LL << sig))) sig--;
            if(val & (1LL << sig)) val ^= vet[i];
        }
        if(!val) return;
        sig = LOG_MAX;
        while(!(val & (1 << sig))) sig--;
        for(auto &x : vet) if(x & (1LL << sig)) x ^= val;
        vet.push_back(val);
        for(int i = (int)vet.size() - 2; i >= 0 && vet[i] < vet[i + 1]; i--){
            swap(vet[i], vet[i + 1]);
        }
    }
};
