#include <cstdio>

struct LinkCutTree {
	struct SplayNode {
		int val;
		SplayNode *son[2], *fa;
		void push_up() {
			val = ( son[0]? son[0] -> val: 0 ) ^ 
				( son[1]? son[1] -> val: 0 );
		}
		bool is_root() {
			if( fa ) {
				return !( fa -> son[0] == (this) || fa -> son[1] == (this) );
			}
			return true;
		}
		bool get_son() {
			if( fa == 0 ) 
				return false;
			return fa -> son[1] == this;
		}
	};
	void rotate( SplayNode *cur ) {
		bool kind = son -> get_son();
		SplayNode *tmp_fa = cur -> fa;
		if( tmp_fa -> fa != 0 ) 
			tmp_fa -> fa -> son[ tmp_fa -> get_son() ] = cur;
		cur -> fa = tmp_fa -> fa;

		tmp_fa -> son[kind] = cur -> son[ kind ^ 1 ];
		if( tmp_fa -> son[kind] ) 
			tmp_fa -> son[kind] -> fa = tmp_fa;
		
		cur -> son[ kind ^ 1 ] = tmp_fa;
		tmp_fa -> fa = cur;

		tmp_fa -> push_up(); cur -> push_up();
	}
	void splay( SplayNode *cur ) {
		while( cur -> is_root() == false ) {
			SplayNode *fa = cur -> fa;
			if( fa -> is_root() == false ) 
				rotate( fa -> get_son() == cur -> get_son()? cur: fa );
			rotate(cur);
		}
	}
	void access( SplayNode *cur ) {
	}
};
