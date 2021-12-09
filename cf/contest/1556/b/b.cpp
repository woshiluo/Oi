/*
 * b.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T aabs ( T cur ) { return cur < 0? -cur: cur; }
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

inline int lowbit( int cur ) { return cur & ( - cur ); }
struct BIT {
	int n;
	std::vector<int> bit;
	BIT( int _size ) {
		n = _size + 10;
		bit.resize(n);
	}
	void add( int cur, int val ) {
		for( ; cur < n; cur += lowbit(cur) ) 
			bit[cur] += val;
	}
	int sum( int cur ) {
		int res = 0;
		for( ; cur; cur -= lowbit(cur) ) 
			res += bit[cur];
		return res;
	}
};
ll calc( std::vector<int> a ) {
	int n = a.size() - 1; ll cnt = 0;
	BIT bit(n);
	for( int i = 1; i <= n; i ++ ) {
		cnt += i - bit.sum( a[i] ) - 1;
		bit.add( a[i], 1 );
	}
	return cnt;
}

ll work() {
	int n = read<int>();
	std::vector<int> a, b[2];
	a.push_back(0);
	for( int i = 1; i <= n; i ++ ) {
		int tmp = read<int>();
		a.push_back(tmp);
		b[ tmp & 1 ].push_back(i);
	}
	if( n & 1 ) {
		if( aabs( (int)( b[1].size() ) - (int)( b[0].size() ) ) != 1 ) 
			return -1;
		int p = ( b[1].size() > b[0].size() ) ;
		{
			int size = b[p].size();
			for( int i = 0; i < size; i ++ ) {
				a[ b[p][i] ] = 2 * i + 1;
			}
		}
		p ^= 1;
		{
			int size = b[p].size();
			for( int i = 0; i < size; i ++ ) {
				a[ b[p][i] ] = 2 * i + 2;
			}
		}
		return calc(a);
	}
	else {
		ll res = n * n;
		if( b[0].size() != b[1].size() ) 
			return -1;
		{
			int size = b[0].size();
			for( int i = 0; i < size; i ++ ) {
				a[ b[0][i] ] = 2 * i + 1;
			}
		}
		{
			int size = b[1].size();
			for( int i = 0; i < size; i ++ ) {
				a[ b[1][i] ] = 2 * i + 2;
			}
		}
		chk_Min( res, calc(a) );
		{
			int size = b[0].size();
			for( int i = 0; i < size; i ++ ) {
				a[ b[0][i] ] = 2 * i + 2;
			}
		}
		{
			int size = b[1].size();
			for( int i = 0; i < size; i ++ ) {
				a[ b[1][i] ] = 2 * i + 1;
			}
		}
		chk_Min( res, calc(a) );
		return res;
	}
	return calc( a );
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		printf( "%lld\n", work() );
	}
}
