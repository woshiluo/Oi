#include <cstdio>
#include <cstring>

typedef long long ll;
typedef const long long cll;
typedef unsigned long long ull;
typedef const int cint;

bool is_number( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T>
T read() {
	T res = 0, k = 1; char x = getchar();
	for( ; !is_number(x); x = getchar() ) 
		if( x == '-' )
			k = -1;
	for( ; is_number(x); x = getchar() ) 
		res = res * 10 + ( x - '0' );
	return res * k;
}
template <class T>
T Min( T a, T b ) { return a < b? a: b; }
template <class T>
T Max( T a, T b ) { return a > b? a: b; }
template <class T>
void chk_Min( T &a, T b ) { if( a > b ) a = b;  }
template <class T>
void chk_Max( T &a, T b ) { if( a < b ) a = b;  }
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while(p) {
		if( p & 1 ) 
			res *= a;
		a *= a;
		p >>= 1;
	}
	return res;
}/*}}}*/

int get_sqrt( cint cur ) {
	int res = 1;
	for( ; 1LL * res * res <= cur; res ++ );
	return res;
}

void prime( cint n ) {
	int sqrt_n = get_sqrt(n);
}

int main() {
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
	}
}
