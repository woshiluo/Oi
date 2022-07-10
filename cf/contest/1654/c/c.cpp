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

#include <map>
#include <queue>
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

const int N = 2e5 + 1e4;

int a[N];

bool work() {
	int n = read<int>();
	ll sum = 0;
	std::map<ll, int> mp;
	std::queue<ll> q[2];
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		mp[ a[i] ] ++;
		sum += a[i];
	}
	if( n == 1 ) 
		return true;

	int cur = 1, nxt = 0;
	q[cur].push(sum);
	while( !q[cur].empty() ) {
		while( !q[cur].empty() ) {
			const ll t = q[cur].front(); q[cur].pop();
			if( t < 2 ) 
				return false;
			ll p1 = t / 2LL;
			ll p2 = t - p1;
			if( mp[p1] > 0 ) 
				mp[p1] --;
			else {
				q[nxt].push(p1);
			}
			if( mp[p2] > 0 ) 
				mp[p2] --;
			else {
				q[nxt].push(p2);
			}
		}
		if( (int)q[nxt].size() > n ) 
			return false;
		cur ^= 1; nxt ^= 1;
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		printf( "%s\n", work()? "YES": "NO" );
	}
}
