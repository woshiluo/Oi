// Woshiluo<woshiluo@woshiluo.site>
// 2021/02/18 23:04:22 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <iostream>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

const int N = 2100;
const ll LLF = ( 1LL << 61LL );

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <class T> 
T aabs( T a ) { return ( a > 0 )? a: -a; }
template <typename T=int>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

struct node {
	int x, y;
	int operator+ ( const node &b ) const {
		return aabs( x - b.x ) + aabs( y - b.y );
	}
	int get_x( const node &b ) const {
		return aabs( x - b.x );
	}
	int get_y( const node &b ) const {
		return aabs( y - b.y );
	}
};

ll work() {
	int n = read();
	static node a[N];
	for( int i = 1; i <= n; i ++ ) {
		a[i].x = read(); a[i].y = read();
	}

	if( n == 2 ) {
		return 1LL * ( a[1].get_x(a[2]) + 1 ) * ( a[1].get_y(a[2]) + 1 );
	}

	std::vector<int> x, y;
	for( int i = 1; i <= n; i ++ ) {
		x.push_back(a[i].x);
		y.push_back(a[i].y);
	}

	std::sort( x.begin(), x.end() );
	x.erase( std::unique( x.begin(), x.end() ), x.end() );
	std::sort( y.begin(), y.end() );
	y.erase( std::unique( y.begin(), y.end() ), y.end() );

	int cnt[2];
	// 0 x 
	// 1 y

	{
		int size = x.size();
		int best_cnt = 0; ll best = LLF;
		for( int i = 0; i < size; i ++ ) {
			ll res = 0;
			for( int j = 1; j <= n; j ++ ) {
				res += 1LL * aabs( x[i] - a[j].x );
			}
			if( res < best ) {
				best = res;
				best_cnt = 1;
			}
			else if( res == best ) {
				best_cnt ++;
			}
		}
		cnt[0] = best_cnt;
	}
	{
		int size = y.size();
		int best_cnt = 0; ll best = LLF;
		for( int i = 0; i < size; i ++ ) {
			ll res = 0;
			for( int j = 1; j <= n; j ++ ) {
				res += 1LL * aabs( y[i] - a[j].y );
			}
			if( res < best ) {
				best = res;
				best_cnt = 1;
			}
			else if( res == best ) {
				best_cnt ++;
			}
		}
		cnt[1] = best_cnt;
	}

	return 1LL * cnt[0] * cnt[1];
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read();
	while( T -- ) {
		printf( "%lld\n", work() );
	}
}
