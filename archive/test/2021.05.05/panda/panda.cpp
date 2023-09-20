#include <cstdio>

struct LinkCutTree {
	struct SplayNode {
		int id;
		bool tag;
		SplayNode *fa, *son[2];
		SplayNode( int cur ) {
			id = cur;
			tag = false;
			fa = son[0] = son[1] = 0;
		}

		inline void push_up() { }
		inline void push_down() {
			if( tag ) {
				std::swap( son[0], son[1] );
				if( son[0] ) son[0] -> tag ^= 1;
				if( son[1] ) son[1] -> tag ^= 1;
				tag = 0;
			}
		}
		bool is_root() {
			if( fa )
				return !( ( fa -> son[0] ) == cur || ( fa -> son[1] ) == cur );
			return false;
		}
		bool get_kind() {
			if( fa ) 
				return ( fa -> son[1] ) == cur; 
			return 0;
		}

		void rotate() {
			SplayNode *old_fa = this -> fa;

			bool kind = this -> get_kind();
			if( !is_root() )
				old_fa -> fa -> son[ old_fa -> get_kind() ] = this;
			fa = old_fa -> fa;
			
			old_fa -> son[kind] = son[ kind ^ 1 ];
			if( old_fa -> son[kind] )
				old_fa -> son[kind] -> old_fa = old_fa;

			son[ kind ^ 1 ] = old_fa;
			old_fa -> fa = this;

			old_fa -> push_up(); this -> push_up();
		}
	};
	SplayNode *node[N];

	void update( SplayNode* cur ) {
		if( !is_root(cur) ) 
			update( cur -> fa );
		cur -> push_down();
	}
	void splay( SplayNode *cur ) {
		update(cur);
		while( ! cur -> is_root() ) {
			SplayNode *fa = cur -> fa;
			if( cur -> fa ) 
				( fa -> get_son() == cur -> get_son()? fa: cur ) -> rotate();
			cur -> rotate();
		}
	}

	LinkCutTree( int n ) {
		for( int i = 0; i <= n; i ++ ) {
			node[i] = new SplayNode(i);
		}
	}

	SplayNode* access( SplayNode* cur ) {
		for( SplayNode* p = 0; cur; p = cur, cur = cur -> fa ) {
			splay(cur); cur -> son[1] = p; cur -> push_up();
		}
	}
	void makeroot( SplayNode *cur ) {
		cur = access(cur);
		std::swap( cur -> son[0], cur -> son[1] );
		cur -> tag ^= 1;
	}
	SplayNode* find( SplayNode* cur ) {
		while( cur -> son[0] ) 
			cur = cur -> son[0];
		splay(cur);
		return cur;
	}
	bool link( SplayNode* from, SplayNode *to ) {
		if( find(from) == find(to) )
			return false;
		makeroot(from);
		from -> fa = to;
	}
	bool cut( SplayNode* from, SplayNode *to ) {
		makeroot(from);
		if( find(from) != find(to) || to -> fa != from || from -> son[0] != 0)
			return false;
		from -> son[1] = 0; to -> fa = 0;
		cur -> push_up();
	}
};

struct Opt {
	int x, y;
};

struct HistoryList {
	struct SetNode {
		int cur, fa;
		int size, son[2];
	} fa[N];

	typedef std::pair<SetNode, SetNode> psn;
	std::stack<history> psn;
	HistoryList( int n ) {
		for( int i = 0; i <= n; i ++ ) {
			fa[i].fa = i; fa[i].cur = i;
			fa[i].size = fa[i].son[0] = fa[i].son[1] = 0;
		}
	}

	void add( Opt opt ) {
	}
};

struct SegmentTree {
	struct SegmentTreeNode {
		std::vector<Opt> opt;
		void add() {
		}
	} tree[ N << 2 ];
	void add( int cur ) {
		for( auto opt: tree[cur].opt ) {
			history.add(opt);
		}
	}
	void remove( int cur ) {
		for( auto opt: tree[cur].opt ) {
			history.pop();
		}
	}

	void query_add( int from, int to, Opt opt, int cur = 1, int left = 1, int rig = n ) { 
		if( from <= left && rig <= to ) {
			tree[cur].opt.push_back( opt );
			return ;
		}

		int mid = ( left + rig ) >> 1;
		if( from <= mid )
			query_add( from, to, opt, cur << 1, left, mid );
		if( to > mid ) 
			query_add( from, to, opt, cur << 1 | 1, mid + 1, rig );
	}
	void solve( int cur = 1, int left = 1, int rig = n ) {
		tree[cur].add();
		if( left == rig ) {
			ans[left] = history.ans;
			tree[cur].remove();
			return ;
		}

		int mid = ( left + rig ) >> 1;
		solve( cur << 1, left, mid );
		solve( cur << 1 | 1, mid + 1, rig );

		tree[cur].remove();
	}
};

int main() {
}
