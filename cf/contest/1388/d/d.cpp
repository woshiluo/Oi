// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/30 23:54:21 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const long long N = 4e5 + 1e4;

struct edge {
	long long to, next;
} e[N];
long long ehead[N], ecnt;
inline void add_edge( long long now, long long to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}

long long n;
long long a[N], b[N], in[N], out[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%lld", &n );
	for( long long i = 1; i <= n; i ++ ) {
		scanf( "%lld", &a[i] );
	}
	for( long long i = 1; i <= n; i ++ ) {
		scanf( "%lld", &b[i] );
		if( b[i] != -1 ) {
			out[i] ++, in[ b[i] ] ++;
			add_edge( i, b[i] );
		}
	}

	long long res = 0;
	std::queue<long long> q;
	std::vector<long long> ans;
	for( long long i = 1; i <= n; i ++ ) {
		if( in[i] == 0 ) 
			q.push(i);
	}

	while( !q.empty() ) {
		long long top = q.front(); q.pop();
		if( a[top] >= 0 ) {
			ans.push_back(top);
			res += a[top];
		}

		for( long long i = ehead[top]; i; i = e[i].next ) {
			if( a[top] >= 0 ) {
				a[ e[i].to ] += a[top];
			}
			in[ e[i].to ] --;
			if( in[ e[i].to ] == 0 ) 
				q.push( e[i].to );
		}
	}

	ecnt = 0;
	memset( ehead, 0, sizeof(ehead) );
	memset( in, 0, sizeof(in) );
	memset( out, 0, sizeof(out) );
	for( long long i = 1; i <= n; i ++ ) { 
		if( a[i] < 0 && b[i] != -1 ) {
			if( a[ b[i] ] < 0 ) {
				out[ b[i] ] ++; in[i] ++;
				add_edge( b[i], i );
			}
		}
	}
	for( long long i = 1; i <= n; i ++ ) {
		if( a[i] < 0 && in[i] == 0 ) {
			q.push(i);
		}
	} 

	while( !q.empty() ) {
		long long top = q.front(); q.pop();

		ans.push_back(top);
		res += a[top];

		for( long long i = ehead[top]; i; i = e[i].next ) {
			in[ e[i].to ] --;
			if( in[ e[i].to ] == 0 ) 
				q.push(e[i].to);
		}
	}

	printf( "%lld\n", res );
	long long size = ans.size();
	for( long long i = 0; i < size; i ++ ) {
		printf( "%lld ", ans[i] );
	}
}
