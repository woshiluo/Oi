/*
 * e.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

using std::make_pair;

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
const int K = 30;

struct Frac {
	int a, b;
	bool operator<( const Frac &_b ) const { return 1LL * a * _b.b < 1LL * _b.a * b; }
	bool operator>( const Frac &_b ) const { return 1LL * a * _b.b > 1LL * _b.a * b; }

	void operator+=( const Frac &_b ) { 
		assert( b == _b.b );
		a += _b.a;
	}
};

int a[N][K + 10];
int cnt[K + 10];

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n = read<int>(), m = 0, ans = 0;
	Frac max = {0, 1};
	for( int i = 1; i <= n; i ++ ) {
		int t, k;
		t = read<int>(); k = read<int>();
		a[t][k] ++;
		cnt[t] ++;
		chk_Max( m, t );
	}
	for( int i = 1; i <= m; i ++ ) {
		for( int j = 1; j <= K; j ++ )
			a[i][j] += a[i][ j - 1 ];
	}
	for( int k = 1; k <= K; k ++ ) {
		std::vector<Frac> res;
		for( int i = 1; i <= m; i ++ ) {
			res.push_back( (Frac){ ( cnt[i] - a[i][k] ) * k + a[i][k], k } );
		}
		std::sort( res.begin(), res.end(), []( const Frac &_a, const Frac &_b ) { return _a > _b; } );
		Frac cur = { 0, k };
		for( int i = 0; i < Min( k, (int)res.size() ); i ++ ) {
			cur += res[i];
		}
		if( cur > max ) {
			ans = k;
			max = cur;
		}
	}
	{
		std::vector<int> res;
		for( int i = 1; i <= m; i ++ ) 
			res.push_back(i);
		std::sort( res.begin(), res.end(), []( const int _a, const int _b ) { return cnt[_a] < cnt[_b]; } );
		int tot = 0;
		for( int i = 1; i <= m; i ++ ) {
			tot += cnt[ res[i - 1] ];
			Frac cur = (Frac){ tot, i };
			if( cur > max ) {
				ans = i;
				max = cur;
			}
		}
	}
	printf( "%d\n", ans );
	if( ans <= K ) {
		std::vector<std::pair<Frac, int>> res;
		for( int i = 1; i <= m; i ++ ) {
			res.push_back( make_pair( (Frac){ ( cnt[i] - a[i][ans] ) * ans + a[i][ans], ans }, i ) );
		}
		std::sort( res.begin(), res.end() );
		for( int i = 0; i < ans; i ++ ) {
			printf( "%d ", res[i].second );
		}
	}
	else {
		std::vector<int> res;
		for( int i = 1; i <= m; i ++ ) 
			res.push_back(i);
		std::sort( res.begin(), res.end(), []( const int _a, const int _b ) { return cnt[_a] < cnt[_b]; } );
		for( int i = 0; i < ans; i ++ ) {
			printf( "%d ", res[i] );
		}
	}
}
