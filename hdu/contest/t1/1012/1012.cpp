/*
 * 1012.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
    T sum = 0, fl = 1; 
    char ch = getchar();
    for (; isdigit(ch) == 0; ch = getchar())
        if (ch == '-') fl = -1;
    for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
    return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
    T res = 1;
    while( p ) {
        if( p & 1 ) 
            res = res * a;
        a = a * a;
        p >>= 1;
    }
    return res;
}/*}}}*/

const int N = 1e6 + 1e5;

int a[N];

int full_pow( cint cur ) { 
    if( cur > 30 ) 
        return ( 1 << 30 );
    if( cur < 0 ) 
        return 1;
    return 1 << cur;
}

int main() {
#ifdef woshiluo
    freopen( "1012.in", "r", stdin );
    freopen( "1012.out", "w", stdout );
#endif
    int T = read<int>();
    while( T -- ) {
        cint n = read<int>();
        int p = 0;
        bool alice = false;
        for( int i = 0; i <= n; i ++ ) {
            a[i] = read<int>();
        }
		for( int i = n - 1; i >= 0; i -- ) 
			a[i] += a[ i + 1 ] / 2;

        printf( "%s\n", a[0]? "Alice": "Bob" );
    }
}
