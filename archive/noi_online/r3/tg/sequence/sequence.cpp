#include <cstdio>
#include <cstring>

#include <algorithm>

template<class T>
void aabs( T &a ) { return a < 0? -a: a; }
template<class T>
T Min( T a, T b ) { return a < b? a: b; }
template<class T>
T Max( T a, T b ) { return a < b? a: b; }
template<class T>
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T>
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

const int N = 1e6 + 1e5;
const int mod = 1e9 + 7;

inline int add( int a, int b ) { return ( a + b ) % mod; }
inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }

int n;
int a[N];

namespace sub4 {
	const int M = 1e7 + 5;
	int phi[M];
	void phi_table( int n = (int)(1e7) ) {
		for (int i = 2; i <= n; i++) phi[i] = 0;
		phi[1] = 1;
		for (int i = 2; i <= n; i++)
			if (!phi[i])
				for (int j = i; j <= n; j += i) {
					if (!phi[j]) phi[j] = j;
					phi[j] = phi[j] / i * (i - 1);
				}
	}

	int st[N], cnt, ans = 0;
	void dfs( int sum, int dep ) {
		if( dep == n + 1 ) {
			ans = add( ans, phi[sum + 1] );
			return ;
		}
		bool flag = true;
		for( int i = 1; i <= cnt; i ++ ) {
			if( ( st[i] & a[dep] ) != 0 ) 
				flag = false;
		}
		if( flag ) {
			st[ ++ cnt ] = a[dep];
			dfs( sum + a[dep], dep + 1 );
			cnt --;
		}
		dfs( sum, dep + 1 );
	}
	void calc() {
		phi_table();
		dfs( 0, 1 );
		printf( "%d\n", ans );
	}

}

namespace sub1 {
	int phi[5] = { 0, 1, 1, 2 };
	inline int pow( int a, int p ) {
		int res = 1;
		while( p ) {
			if( p & 1 ) 
				res = mul( a, res );
			a = mul( a, a );
			p >>= 1;
		}
		return res;
	}
	void calc() {
		int cnt_0 = 0, ans = 0;
		for( int i = 1; i <= n; i ++ ) {
			cnt_0 += ( a[i] == 0 );
		}
		ans = add( ans, pow( 2, cnt_0 ) );
		for( int i = 1; i <= n; i ++ ) {
			if( a[i] == 1 )
				ans = add( ans, mul( 1, pow( 2, cnt_0 ) ) );
		}
		printf( "%d\n", ans );
	}
}

int main() {
	freopen( "sequence.in", "r", stdin );
	freopen( "sequence.out", "w", stdout );

	scanf( "%d", &n );
	int max_ai = 0;
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		chk_Max( max_ai, a[i] );
	}
	if( max_ai <= 1 ) 
		sub1::calc();
	else 
		sub4::calc();

	fclose( stdin );
	fclose( stdout );
	return 0;
}
