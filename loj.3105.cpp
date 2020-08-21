#include <cstdio>
#include <cstring>

const int N = 1e6 + 1e5;

struct node {/*{{{*/
	int scr, time;
	node() {
		scr = time = 0;
	}
	bool operator< ( const node &b ) const {
		if( scr == b.scr ) 
			return time > b.time;
		return scr < b.scr;
	}
	bool operator== ( const node &b ) const {
		return scr == b.scr && time == b.time;
	}
} a[N]; 

struct splay_node {
	int cnt, sum;
	node val;
	splay_node *fa, *son[2];

	splay_node() {
		fa = son[0] = son[1] = 0;
		cnt = sum = 0;
	}

	inline bool get_son() {
		return fa -> son[1] == (this);
	}
	inline void push_up() {
		this -> sum = ( son[0]? son[0] -> sum: 0 ) 
			+ ( son[1]? son[1] -> sum: 0 )
			+ this -> cnt;
	}
} *rt;

void rotate( splay_node *cur ) {
	if( cur == rt ) 
		return ;
	splay_node *tmp_fa = cur -> fa; bool kind = cur -> get_son();
	if( tmp_fa == rt ) 
		rt = cur;

	cur -> fa = tmp_fa -> fa;
	if( tmp_fa -> fa ) 
		tmp_fa -> fa -> son[ tmp_fa -> get_son() ] = cur;

	tmp_fa -> son[kind] = cur -> son[ kind ^ 1 ];
	if( cur -> son[ kind ^ 1 ] ) 
		tmp_fa -> son[kind] -> fa = tmp_fa;

	cur -> son[kind^1] = tmp_fa;
	tmp_fa -> fa = cur;

	tmp_fa -> push_up(); cur -> push_up();
}

void splay( splay_node *from, splay_node *to = 0 ) {
	while( from -> fa != to ) {
		splay_node *tmp_fa = from -> fa;
		if( tmp_fa -> fa != to ) 
			rotate( tmp_fa -> get_son() == from -> get_son()? tmp_fa: from );
		rotate( from );
	}
}

splay_node* insert( node val, splay_node *cur ) { 
	splay_node *res = cur;
	if( val == cur -> val ) 
		cur -> cnt ++;
	else if( val < cur -> val ) {
		if( cur -> son[0] ) 
			res = insert( val, cur -> son[0] );
		else {
			cur -> son[0] = new splay_node;
			cur -> son[0] -> fa = cur;
			cur -> son[0] -> val = val;
			cur -> son[0] -> cnt = 1;
			cur -> son[0] -> push_up();
			res = cur -> son[0];
		}
	}
	else {
		if( cur -> son[1] ) 
			res = insert( val, cur -> son[1] );
		else {
			cur -> son[1] = new splay_node;
			cur -> son[1] -> fa = cur;
			cur -> son[1] -> val = val;
			cur -> son[1] -> cnt = 1;
			cur -> son[1] -> push_up();
			res = cur -> son[1];
		}
	}
	cur -> push_up();
	return res;
}

splay_node* del( node val, splay_node *cur ) {
	splay_node *res = cur;

	if( cur -> val == val ) 
		cur -> cnt --;
	else if( val < cur -> val ) 
		res = del( val, cur -> son[0] );
	else 
		res = del( val, cur -> son[1] );

	cur -> push_up();
	return res;
}

int get_rk( node val ) {
	splay_node *cur = rt;
	int cnt = 0;
	while( cur ) {
		if( cur -> val == val ) {
			if( cur -> son[1] ) 
				cnt += cur -> son[1] -> sum;
			break;
		}
		if( val < cur -> val ) {
			cnt += cur -> sum - cur -> son[0] -> sum;
			cur = cur -> son[0];
		}
		else {
			cur = cur -> son[1];
		}
	}
	splay(cur);
	return cnt;
}/*}}}*/

struct rand_gen {
	unsigned int last = 7, seed, m;
	unsigned int get(){ 
		seed = seed * 17 + last ; return seed % m + 1; 
	}
} Gen;

void remove( splay_node *rt ) {
	if( rt != 0 ) {
		remove( rt -> son[0] );
		remove( rt -> son[1] );
		delete(rt);
	}
}

int T;
int main() {
#ifdef woshiluo
	freopen( "loj.3105.in", "r", stdin );
	freopen( "loj.3105.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		remove(rt);
		unsigned int n, m, seed;
		scanf( "%u%u%u", &m, &n, &seed );
		Gen.seed = seed, Gen.m = m;
		for( unsigned int i = 1; i <= m; i ++ ) {
			a[i].scr = a[i].time = 0;
		}
		rt = new splay_node;
		for( unsigned int i = 1; i <= m; i ++ ) {
			splay( insert( a[i], rt ) );
		}
		for( unsigned int i = 1; i <= n; i ++ ) {
			unsigned int ta = Gen.get();
			unsigned int tb = Gen.get();
			splay( del( a[ta], rt ) );
			a[ta].time += tb, a[ta].scr ++;
			splay( insert( a[ta], rt ) );
			printf( "%d\n", Gen.last = get_rk( a[ta] ) );
		}
	}
}
