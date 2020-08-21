#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

inline int aabs( int a ) { return ( a < 0 )? -a: a; }

const int N = 2e5 + 1e4;
const int INF = N + N;

int n;
char str[N];

struct node {
	int val;
	bool is_a;
	node *lst, *nxt;
	node( node *_lst = 0, node *_nxt = 0, int _val = 0, bool _is_a = false ) {
		lst = _lst, nxt = _nxt;
		val = _val; is_a = _is_a;
	}
	node( const node &b ) {
		this -> val = b.val;
		this -> is_a = b.is_a;
		this -> lst = b.lst;
		this -> nxt = b.nxt;
	}
};

struct edge {
	int size;
	node *head, *tail;
	edge() {
		size = 1;
		head = tail = new node();
	}
	edge( const edge &b ) {
		this -> copy(b);
	}
	void copy ( const edge &b ) {
		head = tail = new node(b.head);
		head -> lst = 0;
		size = b.size;
		node *cur = b.head;
		while( cur -> nxt ) {
			cur = cur -> nxt;
			tail -> nxt = new node(*cur);
			if( tail -> nxt ) 
				tail -> nxt -> lst = tail;
			tail = tail -> nxt;
		}
		tail -> nxt = 0;
	}
	void merge( int dep = INF ) {
		int cnt = 0;
		node *cur = head -> nxt;
		while( cur && cur -> nxt && cnt <= dep ) {
			node *cur_nxt = cur -> nxt;
			if( cur_nxt -> is_a == cur -> is_a ) {
				if( cur -> nxt == tail ) 
					tail = cur;
				cur -> val += cur_nxt -> val;
				cur -> nxt = cur_nxt -> nxt;
				if( cur -> nxt )
					cur -> nxt -> lst = cur;
				delete( cur_nxt );
				size --;
			}
			else 
				cur = cur -> nxt;
			
			cnt ++;
		}
	}
	void add( bool _is_a, int _val = 1 ) {
		size ++;
		tail -> nxt = new node( tail, 0, _val, _is_a );
		tail = tail -> nxt;
	}
} a, b;

void swap_edge( edge &_a, edge &_b, int a_dep, int b_dep, std::vector<int> &res ) {
	int a_val = 0, b_val = 0;
	node *a_cur = _a.head, *b_cur = _b.head;
	_b.size = _b.size - b_dep + a_dep;
	_a.size = _a.size + b_dep - a_dep;
	for( int i = 1; i <= a_dep; i ++ ) {
		a_cur = a_cur -> nxt;
		a_val += a_cur -> val;
	}
	for( int i = 1; i <= b_dep; i ++ ) {
		b_cur = b_cur -> nxt;
		b_val += b_cur -> val;
	}

	std::swap( a_cur -> nxt, b_cur -> nxt );
	std::swap( _a.head, _b.head );

	if( a_cur -> nxt )
		a_cur -> nxt -> lst = a_cur;
	else 
		_a.tail = a_cur;

	if( b_cur -> nxt )
		b_cur -> nxt -> lst = b_cur;
	else 
		_b.tail = b_cur;

	_a.merge( b_dep + 2 );
	_b.merge( a_dep + 2 );

	res[0] ++;
	res.push_back( a_val ); res.push_back( b_val );
}

std::vector<int> chk_a( edge gol_a, edge gol_b ) {
	std::vector<int> res;
	res.push_back(0);
	if( gol_a.head -> nxt -> is_a == gol_b.head -> nxt -> is_a ) {
		if( gol_a.size > gol_b.size ) {
			int cnt = aabs( gol_a.size - gol_b.size ) / 2;
			if( ( cnt & 1 ) == 0 ) 
				cnt ++;
			swap_edge( gol_a, gol_b, cnt, 0, res );
		}
		else
			swap_edge( gol_a, gol_b, 1, 0, res );
	}
	while( gol_a.size > 2 || gol_b.size > 2 ) {
		int a_size = gol_a.size, b_size = gol_b.size;
		if( aabs( a_size - b_size ) < 2 || ( a_size <= 4 && b_size <= 4 ) ) 
			swap_edge( gol_a, gol_b, 1, 1, res );
		else if( a_size < b_size ) 
			swap_edge( gol_a, gol_b, 1, 3, res );
		else 
			swap_edge( gol_a, gol_b, 3, 1, res );
	}
	return res;
}

#ifdef woshiluo
std::vector<char> debug_edge( edge e ) {
	std::vector<char> res;
	node *cur = e.head;
	res.push_back( cur -> is_a? 'a': 'b' );
	while( cur -> nxt ) {
		cur = cur -> nxt;
		res.push_back( cur -> is_a? 'a': 'b' );
	}
	return res;
}
#endif

int main() {
#ifdef woshiluo
	freopen( "loj.2815.in", "r", stdin );
	freopen( "loj.2815.out", "w", stdout );
#endif
	scanf( "%d", &n );
	scanf( "%s", str );
	int len = strlen(str);
	for( int i = 0; i < len; i ++ ) {
		a.add( str[i] == 'a' );
	}
	scanf( "%s", str );
	len = strlen(str);
	for( int i = 0; i < len; i ++ ) {
		b.add( str[i] == 'a' );
	}
	a.merge();
	b.merge();

	std::vector<int> ta, tb;
	ta.push_back(10000000); tb.push_back(10000000);
	if( a.size > 2 ) 
		ta = chk_a( a, b );
	if( b.size > 2 ) 
		tb = chk_a( b, a );
	if( ta[0] == tb[0] && ta[0] == 10000000 ) 
		printf( "%d\n", 0 );
	else if( ta[0] < tb[0] ) {
		int size = ta[0];
		printf( "%d\n", size );
		size = ta.size();
		for( int i = 1; i < size; i += 2 ) {
			printf( "%d %d\n", ta[i], ta[i + 1] );
		}
	}
	else {
		int size = tb[0];
		printf( "%d\n", size );
		size = tb.size();
		for( int i = 1; i < size; i += 2 ) {
			printf( "%d %d\n", tb[i + 1], tb[i] );
		}
	}
}
