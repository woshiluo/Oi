#include <cstdio>

#include <map>
#include <queue>

inline long long Max( long long a, long long b ) { return a > b? a: b; }
inline long long C( int a, int b ) { return 1LL * b * ( b - 1 ) / 2LL; }

const int N = 3e5 + 1e4;

int n, cur_id;
char S[N];
int a[N];
long long ans[N], gol[N];

struct node {
	int id, st, val;
	bool operator< ( const node &b ) const {
		bool flag = false;
		if( this -> id == b.id ) 
			flag = ( this -> val < b.val );
		else 
			flag = ( this -> id > b.id );
#ifdef woshiluo
//		printf( "{ %d, %d, %d } < { %d, %d, %d }: %d\n", id, st, val, b.id, b.st, b.val, flag );
#endif
		return flag;
	}
};

struct pool { int cnt, dep; };

std::map<node, int> mp;
std::map<int, pool> id_mp;
std::map<int, bool> vis;
std::priority_queue<node> q;

void print( std::priority_queue<node> q ) {
	std::priority_queue<node> tmp = q;
	while( !q.empty() ) {
		printf( "{ %d, %d, %d } ", q.top().id, q.top().st, q.top().val );
		q.pop();
	}
	printf( "\n" );
}

int main() {
#ifdef woshiluo
	freopen( "loj.2133.in", "r", stdin );
	freopen( "loj.2133.out", "w", stdout );
#endif
	scanf( "%d", &n );
	scanf( "%s", S + 1 );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		q.push( (node){ 0, i, a[i] } );
		ans[i] = -( 1LL << 62LL );
	}
	id_mp[0] = (pool){ n, 0 };
	while( !q.empty() ) {
		node top = q.top(); q.pop();
		if( id_mp[top.id].cnt < 2 ) {
			continue;
		}
		int cur_r = id_mp[top.id].dep;
		bool vis_1 = false, vis_2 = false;
		long long res = 1;
		gol[cur_r] += C( 2, id_mp[ top.id ].cnt );
		std::vector<long long> ta;
		while(1) {
#ifdef woshiluo
//			print(q);
#endif
			ta.push_back(top.val);

			if( top.st + cur_r > n ) {
				if( q.empty() ) 
					break;
				if( q.top().id != top.id ) 
					break;
				top = q.top();
				q.pop();
				continue;
			}

			node tmp = (node){ top.id, 0, S[ top.st + cur_r ] - 'a' };
			if( mp.count(tmp) == 0 ) {
				cur_id ++;
				mp[tmp] = cur_id;
				id_mp[cur_id] = (pool){ 1, cur_r + 1 };
				q.push( (node){ cur_id, top.st, top.val } );
			}
			else {
				int id = mp[tmp];
				id_mp[id].cnt ++;
				q.push( (node){ id, top.st, top.val } );
			}

			if( q.empty() ) 
				break;
			if( q.top().id != top.id ) 
				break;
			top = q.top();
			q.pop();
		}
		int size = ta.size();
		ans[cur_r] = Max( ans[cur_r], Max( ta[0] * ta[1], ta[ size - 1 ] * ta[ size - 2 ] ) );
	}
	for( int i = 1; i <= n; i ++ ) {
		if( gol[ i - 1 ] == 0 ) 
			printf( "0 0\n" );
		else
			printf( "%lld %lld\n", gol[ i - 1 ], ans[ i - 1 ] );
	}
}
