#include <cstdio>
#include <algorithm>

const int N = 1100;

struct kuai{
	int s,c;	
}colk[N * N];

bool cmp(kuai a, kuai b){
	if(a.s == b.s) return a.c<b.c;
	else return a.s>b.s;
}

int n, col_cnt;
char str[N];
int col[N][N];
bool map[N][N], vis[N][N];

struct point{
	int x,y;
}q[N*N];
int head, tail, tmp;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

inline void bfs(int x, int y){
	point tmp_p;
	col_cnt++;
	head = tail = 0;
	q[head] = (point){x, y};
	while(head <= tail){
		vis[ q[head].x ][ q[head].y ] = true;
		tmp = 4;
		colk[col_cnt].s++;
		for(int i = 0; i < 4; i++){
			tmp_p = q[head];
			tmp_p.x += dx[i]; tmp_p.y += dy[i];
			if(map[ q[head].x + dx[i] ][ q[head].y + dy[i] ]) tmp--;	
			colk[col_cnt].c+=tmp;
			if(tmp_p.x < 1 || tmp_p.x > n || tmp_p.y < 1 || tmp_p.y > n || map[tmp_p.x][tmp_p.y] == false || vis[tmp_p.x][tmp_p.y] ) continue;
			vis[ tmp_p.x ][ tmp_p.y ] = true;
			q[++tail]=tmp_p;
		}
		head++;
	}
}

int main(){
	freopen("perimeter.in", "r", stdin);
	freopen("perimeter.out", "w", stdout);
	scanf("%d", &n);	
	for(int i = 1; i <= n; i++){
		scanf("%s",str+1);
		for(int j = 1; j <= n; j++)
			if(str[j] == '#') map[i][j] = true; 
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(map[i][j]&&!vis[i][j]) bfs(i,j);
		}
	}
	std::sort(colk + 1, colk + col_cnt +1, cmp);
	printf("%d %d\n", colk[1].s, colk[1].c);
}
