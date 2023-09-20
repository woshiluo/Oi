#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <bitset>
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

namespace sub1 {/*{{{*/
	const int N = 305;
	void calc( const int n ) {
		std::vector<std::bitset<N>> a;
		std::bitset<N> one(1);
		a.resize( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			const int k = read<int>();
			for( int j = 1; j <= k; j ++ ) {
				a[i] |= ( one << read<int>() );
			}
		}
		for( int i = 1; i <= n; i ++ ) {
			for( int j = i + 1; j <= n; j ++ ) {
				const auto merge = a[i] & a[j];
				if( merge == a[i] || merge == a[j] ) 
					continue;
				if( merge.count() == 0 ) 
					continue;
				printf( "YES\n%d %d\n", i, j );
				return ;
			}
		}
		printf( "NO\n" );
	}
}/*}}}*/

namespace sub2 {/*{{{*/
	const int N = 1005;
	void calc( const int n ) {
		std::vector<std::bitset<N>> a;
		std::bitset<N> one(1);
		a.resize( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			const int k = read<int>();
			for( int j = 1; j <= k; j ++ ) {
				a[i] |= ( one << read<int>() );
			}
		}
		for( int i = 1; i <= n; i ++ ) {
			for( int j = i + 1; j <= n; j ++ ) {
				const auto merge = a[i] & a[j];
				if( merge == a[i] || merge == a[j] ) 
					continue;
				if( merge.count() == 0 ) 
					continue;
				printf( "YES\n%d %d\n", i, j );
				return ;
			}
		}
		printf( "NO\n" );
	}
}/*}}}*/

namespace sub3 {/*{{{*/
	const int K = 12;

	std::vector<int> a[ 1 << K ];

	int full_pow( const int k ) { return 1 << k; }

	void calc( const int n ) {
		for( int i = 1; i <= n; i ++ ) {
			const int k = read<int>();
			int tmp = 0;
			for( int j = 1; j <= k; j ++ ) {
				tmp |= ( 1 << read<int>() );
			}
			a[tmp].push_back(i);
		}

		for( int i = 0; i < full_pow(K); i ++ ) {
			if( a[i].size() == 0 )
				continue;
			for( int j = i; j < full_pow(K); j ++ ) {
				if( a[j].size() == 0 )
					continue;
				const int merge = ( i & j );
				if( merge == 0 || i == merge || j == merge ) 
					continue;
				printf( "YES\n%d %d\n", a[i].back(), a[j].back() );
				return ;
			}
		}
		printf( "NO\n" );
	}
}/*}}}*/

int main() {
//	freopen( "discuss.in", "r", stdin );
//	freopen( "discuss.out", "w", stdout );

	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		if( n <= 300 ) 
			sub1::calc(n);
		else if( n <= 1000 ) 
			sub2::calc(n);
		else
			sub3::calc(n);
	}


	fclose( stdin );
	fclose( stdout );
	return 0;
}
