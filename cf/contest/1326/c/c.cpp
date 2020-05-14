// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/19 22:35:48 
#include <cstdio>
#include <cstring>

//#include <vector>
#include <algorithm>

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }

const int N = 2e5 + 1e4;
const int mod = 998244353;

inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }

struct node { int id, val; };
bool cmp( node _a, node _b) { return _a.val > _b.val; }

int n, k;
int p[N];
node pos[N];
std::vector<int> a;

int main() {
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &p[i] );
		pos[i] = (node){ i, p[i] };
	}
	std::sort( pos + 1, pos + n + 1, cmp );

	long long sum = 0;
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( pos[i].id );
		sum += pos[i].val;
	}
	std::sort( a.begin(), a.end() );

	int ans = 1;
	for( int i = 0; i < k - 1; i ++ ) {
		ans = mul( ans, a[ i + 1 ] - a[i] );
	}

	printf( "%lld %d\n", sum, ans );
}
