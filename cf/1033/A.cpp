#include <cstdio>

int n;
bool vis[1100][1100];
int ax,ay,bx,by,cx,cy;

inline int zh(int x,int y){
	if(x>ax&&y>ay) return 1;
	if(x>ax&&y<ay) return 2;
	if(x<ax&&y>ay) return 3;
	if(x<ax&&y<ay) return 4;
	return 0;
}

int main(){
	scanf("%d",&n);
	scanf("%d%d",&ax,&ay);
	scanf("%d%d",&bx,&by);
	scanf("%d%d",&cx,&cy);
	
	if(zh(bx,by)==zh(cx,cy)) printf("YES");
	else printf("NO");
}
