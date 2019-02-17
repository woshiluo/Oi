#include <cstdio>
#include <cstring>
#include <deque>

const int N = 510;

int T, r, c;
bool flag;
int dis[N][N];
bool vis[N][N];
char map[N][N];

inline void init(){
    flag = true;
    memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
}

inline void readin(){
    scanf("%d%d", &r, &c);
    for(int i = 1; i <= r; i++) scanf("%s", map[i] + 1);
    if((r + c) % 2 == 1) flag = false, printf("NO SOLUTION\n");
}

struct que{
    int x, y, dis;
}ne;
int q_head, q_tail, p_tail, tx, ty;
// q 0
// p 1
int dx[4] = {+1, +1, -1, -1};
int dy[4] = {-1, +1, +1, -1};
int ddx[4] = {+1, +1, 0, 0};
int ddy[4] = {0, +1, +1, 0};
char dd[4] = {'/','\\','/','\\'};

inline char get_dir(int from_x, int from_y, int to_x, int to_y){
    if(from_x - to_x == from_y - to_y) return '\\';
    else return '/';
}

inline void bfs(){
	std::deque<que> q;
	ne.x = ne.y = ne.dis = 0;
	q.push_back(ne);
    while(!q.empty()){
        que top = q.front(); q.pop_front();
		vis[top.x][top.y] = true;
        for(int i = 0; i < 4; i++){
            ne = top; 
            ne.x += dx[i]; 
            ne.y += dy[i];
            tx = top.x + ddx[i];
            ty = top.y + ddy[i];

            if(ne.x >= 0 && ne.y >= 0 && ne.x <= r && ne.y <= c && !vis[ne.x][ne.y]){
                if(map[tx][ty] != get_dir(top.x, top.y, ne.x, ne.y)) ne.dis++;
                if(dis[ne.x][ne.y] > ne.dis&&!vis[ne.x][ne.y]){
                    dis[ne.x][ne.y] = ne.dis;
                    if(map[tx][ty] != get_dir(top.x, top.y, ne.x, ne.y)) q.push_back(ne);
                    else q.push_front(ne);
                }
            }
        }
    }
}

int main(){
    scanf("%d", &T);
    while(T--){
        init();
        readin();
        bfs();
        flag && printf("%d\n", dis[r][c]);
    }
}
