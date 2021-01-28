#include <cstdio>

#include <stack>

std::stack<int> a;

int cnt = 0;
void dfs( int less, int cur ) {
	cnt ++;
	if( less == 0 ) 
		return ;
	while( cur > 0 ) {
		if( cur > less ) {
			cur --;
			continue;
		}
		a.push(cur);
		dfs( less - cur, cur - 1 );
		a.pop();
		cur --;
	}
}

int main() {
	int n, k;
	n = 2000; k = 2000;
	dfs( k, n );

	printf( "%d", cnt );
}
