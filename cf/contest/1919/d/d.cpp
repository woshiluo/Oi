/*
 * d.cpp 2024-01-07
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 n And that has made all the difference.」 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <set>
#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

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
T pow( T a, i32 p ) {
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
std::set<int> set[N];

bool dfs( int left, int rig, int base ) {
	if( rig < left ) 
		return true;
	int la = left;
	int cnt = 0;
	auto p = set[base].lower_bound(left);
	for( ; p != set[base].end() && *p <= rig; p ++ ) {
		const int i = *p;
		if( a[i] == base ) {
			cnt ++;
			if( !dfs( la, i - 1, base + 1 ) ) 
				return false;
			la = i + 1;
		}
	}
	if( cnt == 0 ) 
		return false;
	if( la != rig + 1 )
		if( !dfs( la, rig, base + 1 ) )
			return false;
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		for( int i = 0; i < n; i ++ )
			set[i].clear();
		int cnt_0 = 0;
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<i32>();
			cnt_0 += ( a[i] == 0 );
			set[ a[i] ].insert(i);
		}
		if( cnt_0 != 1 ) {
			printf( "NO\n" );
			continue;
		}
		for( int i = 1; i <= n; i ++ ) {
			if( a[i] == 0 ) {
				bool flag = (dfs( 1, i - 1, 1 ) && dfs( i + 1, n, 1 ) );
				printf( "%s\n", flag? "YES": "NO" );
				break;
			}
		}
	}
	
}
