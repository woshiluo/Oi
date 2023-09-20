#include <cstdio>

struct Set {
	int fa[N];
	Set(n) {
		for( int i = 0; i <= n; i ++ ) {
			fa[i] = i;
		}
	}
	int& get_fa( int cur ) {
		if( this -> fa[cur] == cur ) 
			return fa[cur];
		fa[cur] = get_fa( fa[cur] );
		return get_fa( fa[cur] );

	}
	int& operator[] ( int cur ) {
		return this -> get_fa(cur);
	}
};

struct edge { int to, next; };

int n, m;

edge e[ N << 1 ];
int ecnt, ehead[N];
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int main() {
	scanf( "%d%d", &n, &m );
	Set set(n);
	std::vector<std::pair<int, int>> tmp_e;
	for( int i = 1; i <= n; i ++ ) {
		int x, y;
		char s[10];
		scanf( "%d%s%d", &x, s, &y );
		if( s[0] == '<' ) {
			tmp_e.push( std::make_pair( x, y ) );
		}
		else {
			set[x] = set[y];
		}
	}
	for( auto x: tmp_e ) {
		add_edge( set[x.first], set[x.second] );
	}
}
