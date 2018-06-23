/* bit normal -> cumulative frequency */
class ft_normal {
public:

    vector<int> ft;
    int n;
    
    ft_normal (int size) : n(size), ft(n, 0){}
    int query_cf(int a) const{ int resp = 0;
        for (int i = a; i; i -= (i & -i)) resp += ft[i];
        return resp; }
    int update_cf (int a, int v) {
        for (int i = a; i < n; i += (i & -i)) ft[i] += v;
        return 0; }

};


class ft_invert {
public:

    vector<int> ft_inv;
    int n;
    
    ft_invert (int size) : n(size), ft_inv(n, 0){}
    int query_cf_inv(int a) const{ int resp = 0;
        for (int i = a; i < n; i += (i & -i)) resp += ft_inv[i];
        return resp; }
    int update_cf_inv (int a, int v) {
        for (int i = a; i; i -= (i & -i)) ft_inv[i] += v;
        return 0; }
};

/* bit diferente -> range minimum query*/

class ft_diff {
public:
    int n;
    vector<int> ft;
    vector<int> ft_inv;
    vector<int> vet;
    
    ft_diff(int size) : n(size), ft(n, 0), ft_inv(n, 0), vet(n, 0){
        for (int i = 1; i < n; i++) ft[i] = ft_inv[i] = i; }
    int query_rmq (int a, int b) const{
        int i, mini = a;
        //bit normal
        for (i = a; i <= b; i += (i & -i))
            if (i + (i & -i) <= b)
                mini = vet[mini] < vet[ft_inv[i]] ? mini : ft_inv[i];
            else mini = vet[mini] < vet[i] ? mini : i;
        //bit invertida
        for (i = b; i >= a; i -= (i & -i))
            if (i - (i & -i) >= a)
                mini = vet[mini] < vet[ft[i]] ? mini : ft[i];
        return mini;
    }
    
    int upd (int a, int v) {
        put_value(a, v);
        update_rmq(a, v);
        return 0;
    }
    
    int put_value (int a, int v) {
        vet[a] = v;
        return 0;
    }
    int update_rmq (int a, int v) const{
        int mini_l = a, mini_r = a;
        for (int i = a; i < n; i += (i & -i)) {
            if (ft[i] != a) ft[i] = v < vet[ft[i]] ? a : ft[i];
            else {
                ft[i] = vet[mini_l] < vet[mini_r] ?
                    (vet[mini_l] < v ? mini_l : a) : (vet[mini_r] < v ? mini_r : a);
                if (i >= a + 1)
                    mini_r = vet[mini_r] < vet[ft_inv[i]] ? mini_r : i;
                if (i - (i & -i) + 1 <= a - 1)
                    mini_l = vet[mini_l] < vet[ft[i - (i & -i) + 1]] ?
                        mini_l : i - (i & -i) + 1;
            }
        }
        mini_l = a, mini_r = a;
        //bit invertida
        for (int i = a; i; i -= (i & -i)) {
            if (ft_inv[i] != a) ft_inv[i] = v < vet[ft_inv[i]] ? a : ft_inv[i];
            else {
                ft_inv[i] = vet[mini_l] < vet[mini_r] ?
                    (vet[mini_l] < v ? mini_l : a) : (vet[mini_r] < v ? mini_r : a);
                if (i + (i & -i) - 1 >= a + 1)
                    mini_r = vet[mini_r] < vet[ft_inv[i + (i & -i) - 1]] ?
                        mini_r : (i + (i & -i) - 1);
                if (i <= a - 1)
                    mini_l = vet[mini_l] < vet[ft[i]] ? mini_l : i;
            }
        }
        return 0;
    }

};

