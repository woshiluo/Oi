/*
 * d.cpp
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

#include <map>
#include <queue>
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

int get_len( ll cur ) {
	ll res = 0;
	while( cur ) {
		cur /= 10LL;
		res ++;
	}
	return res;
}

std::map<ll, bool> mp;

int main() {
	int n = read<int>();
	ll x = read<ll>();

	std::priority_queue<ll> q[2];
	int cur = 1, la = 0;
	q[la].push(x); 
	mp[x] = true;

	for( int i = 0; ; i ++, cur ^= 1, la ^= 1 ) {
		if( q[la].empty() ) 
			break;
		while( !q[la].empty() ) {
			const ll top = q[la].top(); q[la].pop();
			if( get_len(top) == n ) {
				printf( "%d\n", i );
				return 0;
			}
			if( get_len(top) > n ) 
				continue;
			ll tmp = top;
			while( tmp ) {
				ll res = top * ( tmp % 10LL );
				tmp /= 10LL;
				if( !mp[res] ) {
					mp[res] = true;
					q[cur].push(res);
				}
			}
		}
	}

	printf( "-1\n" );
}
