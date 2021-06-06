#include <cstdlib>
#include <cstdio>

#include <queue>

struct Node {
	int a, b;
	Node operator+ ( Node c ) {
		return (Node) { this -> a + c.a, this -> b + c.b };
	}
	Node operator- ( Node c ) {
		return (Node) { this -> a - c.a, this -> b - c.b };
	}
	bool operator== ( Node c ) {
		return a == c.a && b == c.b;
	}
};

bool dfs( Node a, Node b, int step ) {
	if( step > 10 ) 
		return false;

	if( a == (Node){ -1, 0 } && b == (Node){ 0, -1 } ) {
		printf( "Ok!" );
		printf( "%d %d | %d %d\n", a.a, a.b, b.a, b.b );
		return true;
	}

	if( dfs( a + b, b, step + 1 ) ) {
		printf( "%d %d | %d %d\n", a.a, a.b, b.a, b.b );
		return true;
	}
	if( dfs( a, b - a, step + 1 ) ) {
		printf( "%d %d | %d %d\n", a.a, a.b, b.a, b.b );
		return true;
	}

	return false;
}

int main() {
	dfs( { 1, 0 }, { 0, 1 }, 0 );
}
