
const ll MAX = 1e9;
const ll LOG_MAX = 64 - __builtin_clzll((ll)MAX);

struct gauss{
    vector<int> vet;
    gauss(){}
    gauss(int val){
        if(val) vet.push_back(val);
    }
    void add(int val){
        int sig = LOG_MAX;
        for(int i = 0; i < (int)vet.size(); i++){
            while(!(vet[i] & (1 << sig))) sig--;
            if(val & (1 << sig)) val ^= vet[i];
        }
        if(!val) return;
        sig = LOG_MAX;
        while(!(val & (1 << sig))) sig--;
        for(int &x : vet) if(x & (1 << sig)) x ^= val;
        vet.push_back(val);
        for(int i = (int)vet.size() - 2; i >= 0 && vet[i] < vet[i + 1]; i--){
            swap(vet[i], vet[i + 1]);
        }
    }
    gauss merge(const gauss &o) const{
        gauss a = *this;
        a.vet.insert(a.vet.end(), o.vet.begin(), o.vet.end());

        int sig = LOG_MAX;
        int i = 0;
        for(i = 0; i < (int)a.vet.size() && sig >= 0; sig--){
            int t = i;
            while(t < (int)a.vet.size() && !(a.vet[t] & (1 << sig)))
                t++;
            if(t == (int)a.vet.size()) continue;
            swap(a.vet[t], a.vet[i]);
            for(int j = 0; j < (int)a.vet.size(); j++) if(i != j){
                if(a.vet[j] & (1 << sig)){
                    a.vet[j] ^= a.vet[i];
                }
            }
            i++;
        }
        while((int)a.vet.size() > i) a.vet.pop_back();
        while(a.vet.size() and a.vet.back() == 0) a.vet.pop_back();

        return a;
    }
};
