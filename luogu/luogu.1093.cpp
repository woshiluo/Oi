#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/* 垃圾语文
 * 垃圾英语
 * 垃圾数学
 * 垃圾考试
 * 垃圾奖学金*/

int y,s,w,n;

struct WSL{
	int cnt,yw,k;
};

bool cmp(WSL a,WSL b){
	if(a.cnt>b.cnt) return true;
	else if(a.cnt==b.cnt){
		if(a.yw>b.yw) return true;
		else if(a.yw==b.yw){ if(a.k<b.k) return true;}
		else return false;
	}
	else return false;
}

int main(){
	scanf("%d",&n);
	WSL a[n];
	memset(a,0,sizeof(a));
	for(int i=0;i<n;i++){
		scanf("%d%d%d",&y,&s,&w);
		a[i].cnt=y+s+w;
		a[i].yw=y;
		a[i].k=i+1;
	}
	sort(a,a+n,cmp);
	for(int i=0;i<5;i++){
		printf("%d %d\n",a[i].k,a[i].cnt);
	}
}
