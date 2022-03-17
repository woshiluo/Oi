/*
 * e.cpp
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

const int N = 2e5 + 1e4;

int a[N];
std::vector<ll> sum;
std::map<int, int> mp;

int main() {
	int n; ll k;
	n = read<int>(); k = read<ll>();
	for( int i = 0; i < n; i ++ ) {
		a[i] = read<int>();
	}

	int cur = 0; ll ans = 0; bool flag = false;
	mp[0] = 0; sum.push_back(0);
	for( ll i = 1; i <= k; i ++ ) {
		ans += 1LL * a[cur];
		cur = ( cur + a[cur] ) % n;
		if( !flag && mp.count(cur) ) {
			ll t = i - mp[cur];
			ll p = ( k - i ) / t;
			ans += ( ans - sum[ mp[cur] ] ) * p;
			i += t * p;
			flag = true;
		}
		mp[cur] = sum.size();
		sum.push_back(ans);
	}

	printf( "%lld\n", ans );
}
