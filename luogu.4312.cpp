#include <cstdio>

#include <stack>

unsigned int read() {
	unsigned int res = 0; char c = getchar();
	while( c < '0' || c > '9' ) 
		c = getchar();
	while( c >= '0' && c <= '9' ) { res = res * 10 + ( c - '0' ); c = getchar(); }
	return res;
}

const unsigned int N = 3e4 + 1e2;

struct node {
	unsigned int son[2], fa;
	unsigned int val, sum;
	bool rev;
};

unsigned int n, q;
node tree[N];

inline bool get_son( unsigned int cur );
inline void push_up( unsigned int cur );
inline void push_r( unsigned int cur );
inline void push_down( unsigned int cur );

void access( unsigned int cut );
inline bool chk_rt( unsigned int cur );

void rotate( unsigned int cur );
void splay( unsigned int cur );

void split( unsigned int from, unsigned int to );
void link( unsigned int from, unsigned int to );
unsigned int findroot( unsigned int cur );
void makeroot( unsigned int cur );

unsigned int query( unsigned int from, unsigned int to );
void update( unsigned int cur, unsigned int val );

int main() {
#ifdef woshiluo
	freopen( "luogu.4312.in", "r", stdin );
	freopen( "luogu.4312.out", "w", stdout );
#endif
	n = read();
	for( unsigned int i = 1; i <= n; i ++ ) {
		tree[i].val = read();
	}
	q = read();
	unsigned int u, v;
	char op[20];
	while( q -- ) {
		scanf( "%s", op );
		u = read(); v = read();
		if( op[0] == 'b' ) {
			if( findroot(u) == findroot(v) ) 
				printf( "no\n" );
			else {
				printf( "yes\n" );
				link( u, v );
			}
		}
		else if( op[0] == 'p' ) {
			update( u, v );
		}
		else {
			if( findroot(u) == findroot(v) ) {
				printf( "%u\n", query( u, v ) );
			}
			else 
				printf( "impossible\n" );
		}
	}
}

inline bool get_son( unsigned int cur ) { return ( tree[ tree[cur].fa ].son[1] == cur ); }
inline void push_up( unsigned int cur ) { tree[cur].sum = tree[ tree[cur].son[0] ].sum + tree[ tree[cur].son[1] ].sum + tree[cur].val; }
inline void push_r( unsigned int cur ) {/*{{{*/
	std::swap( tree[cur].son[0], tree[cur].son[1] );
	tree[cur].rev ^= 1;
}/*}}}*/
inline void push_down( unsigned int cur ) {/*{{{*/
	if( tree[cur].rev == 0 ) 
		return ;
	if( tree[cur].son[0] ) 
		push_r( tree[cur].son[0] );
	if( tree[cur].son[1] ) 
		push_r( tree[cur].son[1] );
	tree[cur].rev ^= 1;
}/*}}}*/

void access( unsigned int cur ) {/*{{{*/
	for( unsigned int la = 0; cur; cur = tree[cur].fa ) {
		splay(cur);
		tree[cur].son[1] = la;
		push_up( cur );
		la = cur;
	}
}/*}}}*/
inline bool chk_rt( unsigned int cur ) { return ( tree[ tree[cur].fa ].son[0] != cur && tree[ tree[cur].fa ].son[1] != cur ); }

void rotate( unsigned int cur ) {/*{{{*/
	unsigned int tmp_fa = tree[cur].fa;
	push_down( tmp_fa ); push_down( cur );
	bool kind = get_son(cur); 
	if( chk_rt( tmp_fa ) == false ) 
		tree[ tree[ tmp_fa ].fa ].son[ get_son(tmp_fa) ] = cur;
	tree[cur].fa = tree[tmp_fa].fa;
	tree[tmp_fa].son[kind] = tree[cur].son[ kind ^ 1 ];
	if( tree[tmp_fa].son[kind] ) 
		tree[ tree[tmp_fa].son[kind] ].fa = tmp_fa;
	tree[cur].son[ kind ^ 1 ] = tmp_fa;
	tree[tmp_fa].fa = cur;
	push_up(tmp_fa); push_up(cur);
}/*}}}*/
void splay( unsigned int cur ) {/*{{{*/
	std::stack<int> st;
	unsigned int tmp = cur;
	st.push(tmp);
	while( tree[tmp].son[0] ){/*{{{*/
		tmp = tree[tmp].son[0];
		st.push(tmp);
	}/*}}}*/
	while( !st.empty() ) {/*{{{*/
		push_down( st.top() );
		st.pop();
	}/*}}}*/
	while( chk_rt(cur) == false ) {
		unsigned int tmp_fa = tree[cur].fa;
		if( chk_rt( tmp_fa ) == false ) 
			rotate( get_son( tmp_fa ) == get_son( cur )? tmp_fa: cur );
		rotate(cur);
	}
	push_up(cur);
}/*}}}*/

void split( unsigned int from, unsigned int to ) { makeroot(from); access(to); splay(to); }
void link( unsigned int from, unsigned int to ) { split( from, to ); tree[from].fa = to; }
unsigned int findroot( unsigned int cur ) {/*{{{*/
	unsigned int res = cur;
	access( cur ); splay(cur);
	while( tree[res].son[0] ) 
		res = tree[res].son[0];
	return res;
}/*}}}*/
void makeroot( unsigned int cur ) { access(cur); splay(cur); push_r(cur); }

unsigned int query( unsigned int from, unsigned int to ) {
	split( from, to );
	return tree[to].sum;
}
void update( unsigned int cur, unsigned int val ) {
	access(cur), splay(cur);
	tree[cur].val = val;
	push_up( cur );
}
