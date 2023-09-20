#include <cstdio>
#include <cstdlib>

#include <queue>
#include <vector>

using std::make_pair;

const int N = 2e6 + 1e5;

int n;
bool in[N], vis[N];
int belong[N], col[N], right[N], index[N];
// col
// 0 - unset
// 2 - A
// 3 - B

struct Set {
	int fa[N];
	Set(int n) {
		for( int i = 0; i <= n; i ++ ) {
			fa[i] = i;
		}
	}
	int& get_fa( int cur ) {
		if( fa[cur] == cur ) 
			return fa[cur];
		int &p = get_fa( fa[cur] );
		fa[cur] = p;
		return p;
	}
	inline int& operator[] ( int index ) {
		return this -> get_fa(index);
	}
};

inline void no_answer() {
	printf( "0\n" );
	exit(0);
}

int main() {
#ifdef woshiluo
	freopen( "loj.2391.in", "r", stdin );
	freopen( "loj.2391.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		int x, y;
		scanf( "%d%d", &x, &y );
		in[x] = true; in[y] = false;
		belong[x] = belong[y] = i;
		right[i] = y;
	}

	int ans = 1;
	n = n + n;
	Set set(n);

	for( int i = 1; i <= n; i ++ ) {
		nxt[i] = i;
	} 
	for( int i = 1; i <= n; i ++ ) {
		int cur = belong[i];
		if( in[i] ) {
			time_index ++;
			vis[cur] = time_index;
		}
		else {
			
		}
	}

	printf( "%d\n", ans );
}
