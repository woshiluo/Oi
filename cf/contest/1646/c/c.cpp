/*
 * c.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

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

std::vector<ll> fac;

int full_pow( int k ) { return 1 << k; }
bool chk_pos( int s, int k ) { return ( s >> k ) & 1; }

ll lowbit( ll cur ) { return cur & (-cur); }
int bitcount( ll cur ) {
	int cnt = 0;
	while( cur ) {
		cnt ++;
		cur -= lowbit(cur);
	}
	return cnt;
}

int main() {
	{
		ll cur = 1, p = 1;
		while( cur <= (ll)(1e12) ) {
			fac.push_back(cur);
			p ++;
			cur *= p;
		}
	}
	int T = read<int>(), fsize = fac.size();
	while( T -- ) {
		ll n = read<ll>();
		int res = bitcount(n);
		for( int s = 0; s < full_pow(fsize); s ++ ) {
			ll tmp = n;
			int cnt = 0;
			for( int i = 0; i < fsize; i ++ ) {
				if( chk_pos( s, i ) ) {
					cnt ++;
					tmp -= fac[i];
				}
			}
			chk_Min( res, cnt + bitcount(tmp) );
		}
		printf( "%d\n", res );
	}
}
