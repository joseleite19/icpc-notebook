
/* bit diferente -> range minimum query*/

struct ft_diff {
    int n;
    vector<int> ft, ft_inv;
    vector<int> vet;
    
    ft_diff(int size) : n(size), ft(n, 0), ft_inv(n, 0), vet(n, 0){
        for (int i = 1; i < n; i++) ft[i] = ft_inv[i] = i;
    }
    int min_id(int a, int b) const {
        return vet[a] < vet[b] ? a : b;
    }
    int min_id_ft(int a, int b) const {
        return vet[a] < vet[ft[b]] ? a : b;
    }
    int min_id_inv(int a, int b) const {
        return vet[a] < vet[ft_inv[b]] ? a : b;
    }
    int query_rmq (int a, int b) const{
        int i, mini = a;
        //bit invertida
        for (i = a; i <= b; i += (i & -i))
            if (i + (i & -i) <= b)
                mini = min_id(mini, ft_inv[i]);
            else mini = min_id(min, i);
        //bit normal
        for (i = b; i >= a; i -= (i & -i))
            if (i - (i & -i) >= a)
                mini = min_id(mini, ft[i]);
        return mini;
    }
    
    void upd (int a, int v) {
        put_value(a, v);
        update_rmq(a, v);
    }
    
    void put_value (int a, int v) {
        vet[a] = v;
    }
    void update_rmq (int a, int v) {
        int mini_l = a, mini_r = a;
        for (int i = a; i < n; i += (i & -i)) {
            if (ft[i] != a) ft[i] = min_id(a, ft[i]);
            else {
                ft[i] = vet[mini_l] < vet[mini_r] ?
                    min_id(mini_l, a) : mini(mini_r, a);
                if (i >= a + 1)
                    mini_r = min_id_inv(mini_r, i);
                if (i - (i & -i) + 1 <= a - 1)
                    mini_l = min_id_ft(mini_l, i - (i & -i) + 1);
            }
        }
        mini_l = a, mini_r = a;
        //bit invertida
        for (int i = a; i; i -= (i & -i)) {
            if (ft_inv[i] != a) ft_inv[i] = min_id(a, ft_inv[i]);
            else {
                ft_inv[i] = vet[mini_l] < vet[mini_r] ?
                    min_id(mini_l, a) : min_id(mini_r, a);
                if (i + (i & -i) - 1 >= a + 1)
                    mini_r = min_id_inv(mini_r, i + (i & -i) - 1);
                if (i <= a - 1)
                    mini_l = min_id_ft(mini_l, i);
            }
        }
    }

};

