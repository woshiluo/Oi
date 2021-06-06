// Woshiluo<woshiluo@woshiluo.site>
// 2021/04/03 22:59:31 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <iostream>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

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

const int N = 1e5 + 1e4;
const int INF = 0x3f3f3f3f;

struct City {
	int id, a, c;
}cities[N];
bool cmp( City _a, City _b ) {
	return _a.a < _b.a;
}

struct QNode {
	int id, dis;
	bool operator< ( const QNode &b ) const {
		return this -> dis > b.dis;
	}
};

int n;
int f[N];
bool vis[N];
std::vector<int> wait[N];

int fd_nxt( int cur ) {
	int cur_a = cities[cur].c + cities[cur].a;
	int left = cur + 1, rig = n, res = n + 1;
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		if( cities[mid].a >= cur_a ) {
			res = mid;
			rig = mid - 1;
		}
		else 
			left = mid + 1;
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d", &cities[i].a, &cities[i].c );
		cities[i].id = i;
	}
	
	std::sort( cities + 1, cities + n + 1, cmp );

}
