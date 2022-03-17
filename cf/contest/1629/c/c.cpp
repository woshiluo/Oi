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
const int MAXA = N;

int a[N], cnt[N];

inline int lowbit( int cur ) { return cur & ( - cur ); }
struct BIT {
	int n;
	int bit[N];
	BIT( int _size = 0 ) {
		init(_size);
	}
	void init( int _size ) {
		n = _size;
		memset( bit, 0, sizeof(bit) );
	}
	void add( int cur, int val ) {
		cur ++;
		for( ; cur < n; cur += lowbit(cur) ) 
			bit[cur] += val;
	}
	int sum( int cur ) {
		cur ++;
		int res = 0;
		for( ; cur; cur -= lowbit(cur) ) 
			res += bit[cur];
		return res;
	}
} bit;

int get_mex() {
	int left = 0, rig = MAXA, res = -1;
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		if( bit.sum(mid) == mid + 1 ) {
			res = mid;
			left = mid + 1;
		}
		else 
			rig = mid - 1;
	}
	return res + 1;
}

int main() {
#ifdef woshiluo 
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		memset( cnt, 0, sizeof(cnt) );

		bit.init( n + 10 );

		for( int i = 1; i <= n; i ++ ) 
			a[i] = read<int>();

		for( int i = 1; i <= n; i ++ ) {
			if( cnt[ a[i] ] == 0 ) 
				bit.add( a[i], 1 );
			cnt[ a[i] ] ++;
		}

		int p = 1;
		std::vector<int> res;
		while( p <= n ) {
			int g = get_mex();
			res.push_back(g);
			int tmp = g;
			std::map<int, bool> mp;
			int cur = p;
			for( ; cur <= n; cur ++ ) {
				if( mp.count( a[cur] ) == 0 ) {
					mp[ a[cur] ] = 1;
					if( a[cur] <= g )
						tmp --;
				}
				if( tmp == 0 )
					break;
			}
			for( int i = p; i <= cur; i ++ ) {
				if( cnt[ a[i] ] == 1 ) 
					bit.add( a[i], -1 );
				cnt[ a[i] ] --;
			}
			p = cur + 1;
		}
		printf( "%lu\n", res.size() );
		for( auto &cur: res ) {
			printf( "%d ", cur );
		}
		printf( "\n" );
	}
}
