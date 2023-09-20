#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
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

const int N = 5e5 + 1e4;
const int INF = 0x3f3f3f3f;
const ll LLF = 0x3f3f3f3f3f3f3f3f;

int a[N];
ll f[N][3];
std::priority_queue<int> q;


int main() {
#ifdef woshiluo
	freopen( "chen.in", "r", stdin );
	freopen( "chen.out", "w", stdout );
#endif
	ll ans = 0;
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		int tmp = read<int>();
		q.push(tmp);
		if( q.top() > tmp ) {
			ans += q.top() - tmp;
			q.push(tmp); q.pop();
		}
	}
	printf( "%lld\n", ans );
}
