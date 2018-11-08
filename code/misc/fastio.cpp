#define pc(x) putchar_unlocked(x)
#define gc(x) getchar_unlocked(x)

inline void scan_int(int &x){
    register int c = gc();
    x = 0;
    int neg = 0;
    for(; ((c < '0' || c > '9') && c != '-'); c = gc());
    if(c == '-'){
        neg = 1;
        c = gc();
    }
    for(; c >= '0' && c <= '9'; c = gc())
        x = (x << 1) + (x << 3) + c - '0';
    if(neg) x = -x;
}

inline void print_int(int n){
    int rev = 0, count = 0, neg;
    if(n == 0){
        pc('0');
        return;
    }
    if(n < 0) n = -n, neg = 1;
    while(n % 10 == 0) count++, n /= 10;
    for(rev = 0; n != 0; n /= 10)
        rev = (rev << 3) + (rev << 1) + n % 10;
    if(neg) pc('-');
    while(rev != 0) pc(rev % 10 + '0'), rev /= 10;
    while(count--) pc('0');
    pc('\n');
}

inline void print_string(char *str){
    while(*str) pc(*str++);
    pc('\n');
}

