#include <cstdio>

#include <cstring>

inline long long Max( long long a, long long b ) { return a > b? a: b; }

const int N = 1e5 + 1e4;

long long ans;
long long f[30][30], add[30];
char s[N];

int main() {
#ifdef woshiluo
	freopen( "C.in", "r", stdin );
	freopen( "C.out", "w", stdout );
#endif
	scanf( "%s", s + 1 );
	int len = strlen( s + 1 );
	for( int i = 1; i <= len; i ++ ) {
		int mp = s[i] - 'a';
		for( int j = 0; j < 26; j ++ ) {
			f[j][mp] += add[j];
			ans = Max( ans, f[j][mp] );
		}
		add[mp] ++;
		ans = Max( ans, add[mp] );
	}
	printf( "%lld\n", ans );
}
