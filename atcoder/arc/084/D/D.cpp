#include <cstdio>

#include <queue>

const int N = 1e5 + 1e4;

int k;
bool vis[N];

struct node { int cur, val; };

int main() {
	scanf( "%d", &k );
	std::deque<node> q;
	q.push_front( (node){ 1, 1 } );
	while( !q.empty() ) {
		node top = q.front(); q.pop_front();
		if( vis[ top.cur ] )
			continue;
		vis[ top.cur ] = true;
		if( top.cur == 0 ) {
			printf( "%d\n", top.val );
			return  0;
		}
		q.push_front((node){ ( top.cur * 10 ) % k, top.val });
		q.push_back((node){ ( top.cur + 1 ) % k, top.val + 1 });
	}
}
