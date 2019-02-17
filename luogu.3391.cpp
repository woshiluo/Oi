#include <cstdio>

const int N = 110000;

int n, m, x, y;

class Splay{
	private:
		struct Splay_node{
			int size,val;
			bool lazy;
			Splay_node *son[2], *fa;
			// 0 left
			// 1 rig
		}tree[N], *root, *tmp1, *tmp2, *tmp3, *tmp4, *from_node, *to_node;
		
		int tcnt;
		int a[N];

		inline int get_size(Splay_node *now) {return now == 0? 0: now -> size;}

		inline bool get_son(Splay_node *now) {return now -> fa != 0? now -> fa -> son[1] == now : 0;}

		inline void pushup(Splay_node *now) {now -> size = get_size( now -> son[0] ) + get_size( now -> son[1] ) + 1;}

		inline void pushdown(Splay_node *now){
			if( now -> lazy ){
				now -> lazy = false;
				tmp4 = now -> son[0]; now -> son[0] = now -> son[1]; now -> son[1] = tmp4;
				if( now -> son[0] ) now -> son[0] -> lazy ^= 1;
				if( now -> son[1] ) now -> son[1] -> lazy ^= 1;
			}
		}

		void build(int left, int rig, Splay_node *now){
			int mid = (left + rig) >> 1;
			now -> val = mid;
			if( left != rig ){
				if(left < mid){
					now -> son[0] = &tree[++tcnt]; now -> son[0] -> fa = now;
					build(left, mid - 1, now -> son[0]);
				}
				if(rig > mid){
					now -> son[1] = &tree[++tcnt]; now -> son[1] -> fa = now;
					build(mid + 1, rig, now -> son[1]);
				}
			}
			pushup(now);
		}

		inline void rotate(Splay_node *now){
			pushdown(now);
			bool kind = get_son(now);
			tmp3 = now -> fa;
			if(tmp3 -> fa == 0) now -> fa = 0, root = now;
			else now -> fa -> fa -> son[ get_son(tmp3) ] = now, now -> fa = tmp3 -> fa;
			tmp3 -> son[kind] = now -> son[kind ^ 1]; if(tmp3 -> son[kind]) tmp3 -> son[kind] -> fa = tmp3;
			now -> son[kind ^ 1] = tmp3; tmp3 -> fa = now;
			pushup(tmp3);pushup(now);
		}
		
		inline void splay(Splay_node *from, Splay_node *to){
			while( from -> fa != to){
				tmp1 = from -> fa; tmp2 = tmp1 -> fa;
				if(tmp2 == to) rotate(from);
				else {
					if( get_son(from) != get_son(tmp1) ) rotate(tmp1), rotate(from);
					else rotate(from), rotate(from);
				}
			}
		}
		
		inline Splay_node* find(int val){
			Splay_node* now = root;
			while(now){
				pushdown(now);
				if( val > get_size(now -> son[0]) + 1 ) val -= get_size(now -> son[0]) + 1, now = now -> son[1];
				else if( val > get_size(now -> son[0]) ) return now;
				else now = now -> son[0];
			}
			return now;
		}
	public: 
		inline void init(int n){
			root = &tree[0];
			build(1, n+2, root);
		}
		
		inline void reserve(int from, int to){
			from_node = find(from); 
			to_node = find(to + 2);
			splay(from_node, 0);
			splay(to_node, from_node);
			root -> son[1] -> son[0] -> lazy ^= 1;
		}

		void zxbl(Splay_node *now){
			pushdown(now);
			if(now -> son[0]) zxbl(now -> son[0]);
			now -> val != 1 && now -> val != n + 2 && printf("%d ", now -> val - 1);
			if(now -> son[1]) zxbl(now -> son[1]);
		}	

		inline void print_zxbl() {zxbl(root);}
}T;

int main(){
	scanf("%d%d", &n, &m);
	T.init(n);
	while(m--){
		scanf("%d%d", &x, &y);
		T.reserve(x,y);
	}
	T.print_zxbl();
}
