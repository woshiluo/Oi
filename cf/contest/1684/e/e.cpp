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

const int N = 1e5 + 1e4;

int lowbit( cint cur ) { return cur & ( -cur ); }
struct BIT {/*{{{*/
	ll tree[N];
	void add( int cur, cint val ) { 
		for( ; cur < N; cur += lowbit(cur) ) 
			tree[cur] += val;
	}
	ll sum( int cur ) {
		ll res = 0;
		for( ; cur; cur -= lowbit(cur) ) 
			res += tree[cur];
		return res;
	}
} bit;/*}}}*/

int main() {
	int T = read<int>();
	while( T -- ) {
		std::map<int, int> pool, mp;
		std::vector<std::pair<int, int>> list;
		int n = read<int>(); 
		int k = read<int>();


		for( int i = 1; i <= n; i ++ ) {
			mp[ read<int>() ] ++;
		}

		for( auto &pair: mp ) {
			list.push_back( std::make_pair( pair.second, pair.first ) );
		}

		std::sort( list.begin(), list.end() );

		cint tot = list.size();
		for( int i = 0; i < tot; i ++ ) {
			bit.add( i + 1, list[i].second );
			mp[ list[i].first ] = i + 1;
		}

		int min = 0;
		int p = 1;
		for( int mex = 1; mex <= n; mex ++ ) {
			while( bit.sum(p) == 0 ) 
				p ++;
			if( !mp.count( mex - 1 ) ) {
				min ++;
				bit.add( p, -1 );
			}
			int left = p, rig = tot, res = 0; 
			while( left <= rig ) {
				cint mid = ( left + rig ) >> 1;
				if( min + bit.sum(mid) <= k ) {
					res = mid;
					left = mid + 1;
				}
				else 
					rig = mid - 1;
			}
			if( min >=
		}
	}
}
