/*
 * sort.cpp
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

#include <set>
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

int lowbit( const int cur ) { return cur & ( - cur ); }
struct BIT {
	int bit[N];

	void add( int cur, int val ) {
		for( ; cur; cur -= lowbit(cur) ) 
			bit[cur] += val;
	}

	int sum( int cur ) {
		int res = 0;
		for( ; cur < N; cur += lowbit(cur) ) 
			res += bit[cur];
		return res;
	}

	int query( int cur ) {
		return sum(cur) - sum(cur + 1);
	}
} bit;

int main() {
	freopen( "sort.in", "r", stdin );
	freopen( "sort.out", "w", stdout );

	int n = read<int>();
	std::vector<int> nums;
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		nums.push_back( a[i] );
	}
	std::sort( nums.begin(), nums.end() );
	nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );
	for( int i = 1; i <= n; i ++ ) {
		a[i] = std::lower_bound( nums.begin(), nums.end(), a[i] ) - nums.begin() + 1;
	}
	const int CMAX = nums.size();

	ll ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( a[i] > a[1] ) {
			std::swap( a[1], a[i] );
			ans ++;
		}
	}

	bit.add( CMAX, 1 );
	for( int i = 2; i <= n; i ++ ) {
		const int cnt = bit.sum( a[i] + 1 );
		ans += cnt;
		if( bit.query( a[i] ) == 0 ) 
			bit.add( a[i], 1 );
	}
	printf( "%lld\n", ans );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
