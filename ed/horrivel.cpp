#include <stdio.h>
#include <string.h>

long long st[800004];
long long troca[800004];

void update(int p, int ini, int fim, int b, int e, long long valor){
    st[p] += (troca[p] * (fim - ini + 1));
    troca[(p << 1)] += troca[p];
    troca[(p << 1) + 1] += troca[p];
    troca[p] = 0;

    if(b > fim || e < ini) return;

    st[p] += ((fim < e ? fim : e) - (ini > b ? ini : b) + 1) * valor;
    
    if(b <= ini && e >= fim){
        troca[(p << 1)] += valor;
        troca[(p << 1) + 1] += valor;
        return;
    }
    
    int meio = (ini + fim) >> 1;

    if(b <= meio) update((p << 1), ini, meio, b, e, valor);
    if(e > meio) update((p << 1) + 1, meio+1, fim, b, e, valor);
}

long long query(int p, int ini, int fim, int b, int e){
    st[p] += (troca[p] * (fim - ini + 1));
    troca[(p << 1)] += troca[p];
    troca[(p << 1) + 1] += troca[p];

    troca[p] = 0;

    if(b > fim || e < ini) return 0;
    if(b <= ini && e >= fim) return st[p];

    int meio = (ini + fim) >> 1;

    return query((p << 1), ini, meio, b, e) + query((p << 1) + 1, meio+1, fim, b, e);
}

int main(){
    int t, n, c, i, p, q, v;

    scanf("%d", &t);
    while(t--){
        scanf(" %d %d", &n, &c);

        memset(st, 0, sizeof(st));
        memset(troca, 0, sizeof(troca));
        while(c--){
            scanf(" %d %d %d", &i, &p, &q);
            if(!i){
                scanf(" %d", &v);
                update(1, 0, n-1, p-1, q-1, v);
            }
            else printf("%lld\n", query(1, 0, n-1, p-1, q-1));
        }
    }

    return 0;
}
