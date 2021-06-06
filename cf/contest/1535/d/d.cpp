// Woshiluo<woshiluo@woshiluo.site>
// 2021/06/04 22:36:09 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
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

const int K = 20;
const int N = ( 1 << 20 );

int k, q;
int a[N];
struct Node {
	int pos, cnt;
	Node *son[2], *fa;

	Node( int _pos, int _cnt ) {
		pos = _pos; cnt = _cnt;
		fa = son[0] = son[1] = 0;
	}

	inline void push_up() {
		if( a[pos] == 0 ) 
			cnt = son[0] -> cnt;
		else if( a[pos] == 1 ) 
			cnt = son[1] -> cnt;
		else
			cnt = son[0] -> cnt + 
				son[1] -> cnt;
	}
};

std::vector<Node*> dep[K];
Node* pos[N];

Node* build( int depth, int base ) {
	Node *cur = new Node( base, depth == 0 );
	dep[depth].push_back(cur);
	if( depth == 0 ) 
		return cur;

	base = base - ( ( k - depth + 1 ) << 1 );
	cur -> son[0] = build( depth - 1, base );
	cur -> son[1] = build( depth - 1, base + 1 );
	cur -> son[0] -> fa = cur -> son[1] -> fa = cur;

	return cur;
}

void full_upgrade( Node *cur ) {
	if( cur -> son[0] == 0 ) 
		return ;
	full_upgrade( cur -> son[0] );
	full_upgrade( cur -> son[1] );
	cur -> push_up();
}

inline int trans( char _a ) {
	if( _a == '?' ) 
		return -1;
	else
		return _a - '0';
}

void pull_up( Node *cur ) {
	if( cur == 0 ) 
		return ;
	cur -> push_up();
	pull_up( cur -> fa );
}

void dfs_free( Node *cur ) {
	if( cur == 0 ) 
		return ;
	dfs_free( cur -> son[0] );
	dfs_free( cur -> son[1] );
	delete(cur);
	return ;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d", &k );
	char str[N];
	scanf( "%s", str + 1 );
	for( int i = 1; i <= ( 1 << k ) - 1; i ++ ) {
		a[i] = trans( str[i] );
	}

	Node *rt = build( k, ( 1 << k ) - 1 );

	{
		int base = 0;
		for( int i = 1; i <= k; i ++ ) {
			int cnt = 0;
			for( auto node: dep[i] ) {
				cnt ++;
				node -> pos = base + cnt;
				pos[ node -> pos ] = node;
			}
			base += cnt;
		}

		full_upgrade(rt);
	}

	scanf( "%d", &q );
	while( q -- ) {
		int x; 
		char op[3];
		scanf( "%d%s", &x, op );
		a[x] = trans(op[0]);
		pull_up(pos[x]);
		printf( "%d\n", rt -> cnt );
	}

	dfs_free(rt);
}
