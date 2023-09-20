#include <cstdio> 

const int N = 2e5 + 1e3;

int n = 2e5;

struct node {
	bool val;
	bool lazy_zero, lazy_one, lazy_xor;
	node() {
		lazy_zero = lazy_one = lazy_xor 
			= val = false;
	}

	void clear_lazy() {
		lazy_zero = lazy_one = lazy_xor = false;
	}
	void calc() {
		if( lazy_xor ) 
			val = !val;
		if( lazy_one )
			val = true;
		if( lazy_zero ) 
			val = false;
	}
} tree[ N << 2 ];

// Segment Tree Start 
inline void push_down( int cur );

void seg_zero( int from, int to, int cur = 1, int left = 1, int rig = n );
void seg_one( int from, int to, int cur = 1, int left = 1, int rig = n );
void seg_xor( int from, int to, int cur = 1, int left = 1, int rig = n );
int query( int pos, int cur = 1, int left = 1, int rig = n );
// Segment Tree End

inline void to_seg( int left, int rig ) {
//	printf( "%d %d\n", left, rig );
	printf( "%c%d,%d%c ", ( left & 1 )? '[': '(', ( ( left - 1 ) >> 1 ), ( rig >> 1 ), ( rig & 1 )? ']': ')' );
}

int main() {
#ifdef woshiluo
	freopen( "poj.3225.in", "r", stdin );
	freopen( "poj.3225.out", "w", stdout );
#endif
	int x, y;
	char op[5], x_op, y_op;
	while( scanf( "%s ", op ) != EOF ) {
		scanf( "%c%d,%d%c", &x_op, &x, &y, &y_op );
//		printf( "%c %c%d,%d%c\n", op[0], x_op, x, y, y_op );
		x ++, y ++;
		x <<= 1; y <<= 1;
		y -= 2;
		x -= ( x_op == '[' );
		y += ( y_op == ']' );
//		printf( "%d %d\n", x, y );
		if( op[0] == 'U' )
			seg_one( x, y );
		else if( op[0] == 'I' ) 
			seg_zero( 1, x - 1 ), seg_zero( y + 1, n );
		else if( op[0] == 'D' ) 
			seg_zero( x, y );
		else if( op[0] == 'C' ) 
			seg_zero( 1, x - 1 ), seg_zero( y + 1, n ), seg_xor( x, y );
		else 
			seg_xor( x, y );
	}
//	for( int i = 1; i <= 12; i ++ ) {
//		printf( "%d ", query(i) );
//	}
//	printf( "\n\n" );

	int la = 0; bool flag = false;
	for( int i = 1; i <= 131071; i ++ ) {
		if( query(i) ) {
			if( la == 0 )
				la = i;
		}
		else if( la != 0 ){
			flag = true;
			to_seg( la, i - 1 );
			la = 0;
		}
	}
	if( la != 0 ) {
		flag = true;
		to_seg( la, 131071 );
		la = 0;
	}

	if( !flag ) {
		printf( "empty set\n" );
	}
}

void rev( int cur ) {
	if( tree[cur].lazy_one ) 
		tree[cur].lazy_one = false, tree[cur].lazy_zero = true;
	else if( tree[cur].lazy_zero ) 
		tree[cur].lazy_zero = false, tree[cur].lazy_one = true;
	else 
		tree[cur].lazy_xor ^= 1;
}

void push_down( int cur ) {
	int left = ( cur << 1 ), rig = ( cur << 1 | 1 );
	if( tree[cur].lazy_zero ) {
		tree[left].clear_lazy(); tree[rig].clear_lazy();
		tree[left].lazy_zero = tree[rig].lazy_zero = true;
	}
	if( tree[cur].lazy_one ) {
		tree[left].clear_lazy(); tree[rig].clear_lazy();
		tree[left].lazy_one = tree[rig].lazy_one = true;
	}
	if( tree[cur].lazy_xor ) {
		rev(left), rev(rig);
	}
	tree[cur].clear_lazy();
}

void seg_zero( int from, int to, int cur, int left, int rig ) {
	if( from > to ) 
		return ;
	if( from <= left && rig <= to ) {
		tree[cur].clear_lazy();
		tree[cur].lazy_zero = true;
		return ;
	}

	int mid = ( left + rig ) >> 1;
	push_down( cur );
	if( from <= mid )
		seg_zero( from, to, cur << 1, left, mid );
	if( to > mid ) 
		seg_zero( from, to, cur << 1 | 1, mid + 1, rig );
}


void seg_one( int from, int to, int cur, int left, int rig ) {
	if( from > to ) 
		return ;
	if( from <= left && rig <= to ) {
		tree[cur].clear_lazy();
		tree[cur].lazy_one = true;
		return ;
	}

	int mid = ( left + rig ) >> 1;
	push_down( cur );
	if( from <= mid )
		seg_one( from, to, cur << 1, left, mid );
	if( to > mid ) 
		seg_one( from, to, cur << 1 | 1, mid + 1, rig );
}

void seg_xor( int from, int to, int cur, int left, int rig ) {
	if( from > to ) 
		return ;
	if( from <= left && rig <= to ) {
		rev(cur);
		return ;
	}

	int mid = ( left + rig ) >> 1;
	push_down( cur );
	if( from <= mid )
		seg_xor( from, to, cur << 1, left, mid );
	if( to > mid ) 
		seg_xor( from, to, cur << 1 | 1, mid + 1, rig );
}

int query( int pos, int cur, int left, int rig ) {
	if( left == rig && left == pos ) {
		tree[cur].calc();
		return tree[cur].val;
	}

	int mid = ( left + rig ) >> 1;
	push_down(cur);
	if( pos <= mid ) 
		return query( pos, cur << 1, left, mid );
	if( pos > mid )
		return query( pos, cur << 1 | 1, mid + 1, rig );
	return 0;
}
