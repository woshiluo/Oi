#include <cstdio>
#include <cstring>

#include <queue>

const int N = 1e4 + 1e3;
const int T_L = 1e6 + 1e5;

int n;

class AC_AM {
	private:
		struct node { 
			int nxt[26], end, fail; 
			node() { 
				memset( nxt, 0, sizeof(nxt) );
				end = 0; fail = 1; 
			}
		};

		int node_cnt = 1, dict_cnt = 0;
		node tree[N];
	public:
		void insert( char str[] ) {
			int cur = 1;
			for( int i = 0; str[i]; i ++ ) {
				int cur_char = str[i] - 'a';
				if( tree[cur].nxt[ cur_char ] == 0 ) 
					tree[cur].nxt[ cur_char ] = ++ node_cnt;
				cur = tree[cur].nxt[ cur_char ];
			}
			tree[cur].end = ++ dict_cnt;
		}
		void build() {
			std::queue<int> q;
			for( int i = 0; i < 26; i ++ ) {
				if( tree[1].nxt[i] == 0 ) 
					tree[1].nxt[i] = 1;
				else 
					q.push( tree[1].nxt[i] );
					
			}
			while( !q.empty() ) {
				int cur = q.front(); q.pop();
				for( int i = 0; i < 26; i ++ ) {
					int &nxt = tree[cur].nxt[i];
					if( nxt ) {
						tree[nxt].fail = tree[ tree[cur].fail ].nxt[i];
						q.push( nxt );
					}
					else 
						nxt = tree[ tree[cur].fail ].nxt[i];
				}
			}
		}
		std::vector<int> query( char str[] ) {
			int sum[N];
			memset( sum, 0, sizeof(int) * ( dict_cnt + 1 ) );
			int cur = 1;
			for( int i = 0; str[i]; i ++ ) {
				cur = tree[cur].nxt[ str[i] - 'a' ];
				for( int tmp = cur; tmp != 1; tmp = tree[tmp].fail ) {
					if( tree[tmp].end ) 
						sum[ tree[tmp].end ] ++;
				}
			}
			
			int min = 0;
			for( int i = 1; i <= dict_cnt; i ++ ) {
				if( sum[i] > min ) 
					min = sum[i];
			}
			std::vector<int> res;
			res.push_back(min);
			for( int i = 1; i <= dict_cnt; i ++ ) {
				if( sum[i] == min ) 
					res.push_back(i);
			}
			return res;
		}
};

int main() {
#ifdef woshiluo
	freopen( "luogu.3796.in", "r", stdin );
	freopen( "luogu.3796.out", "w", stdout );
#endif
	while( scanf( "%d", &n ) != EOF ) {
		if( n == 0 ) 
			break;
		AC_AM *ac_am = new AC_AM;
		char rd_str[200][100], que_str[T_L];
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%s", rd_str[i] );
			ac_am -> insert(rd_str[i]);
		}
		ac_am -> build();
		scanf( "%s", que_str );
		std::vector<int> ans = ac_am -> query(que_str);
		int size = ans.size();
		printf( "%d\n", ans[0] );
		for( int i = 1; i < size; i ++ ) {
			printf( "%s\n", rd_str[ ans[i] ] );
		}
		delete(ac_am);
	}
}
