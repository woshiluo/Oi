#include <cstdio>
#include <queue>
#include <algorithm>

const int N=110000;

inline int Min(int a,int b){return a<b?a:b;}
inline int Max(int a,int b){return a>b?a:b;}
inline int Aabs(int a){return a<0?(0-a):a;}

int n,ocnt,now,p,ans;

struct cow{
	int id,start,time;
	bool operator< (const cow &b)const{
		if(id==b.id) return this->start>b.start;
		else return this->id>b.id;
	}
}a[N],tmp;

bool cmp(cow a,cow b){return a.start<b.start;}

std::priority_queue<cow> pq;

int main(){
	freopen("convention2.in","r",stdin);
	freopen("convention2.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].start,&a[i].time);
		a[i].id=i;
	}
	std::sort(a+1,a+n+1,cmp);
	
	p=2;
	pq.push(a[1]);
	while(ocnt<n){
		ocnt++;
		if(pq.empty()) pq.push(a[p++]);
		tmp=pq.top();pq.pop();	
		ans=Max(ans,now-tmp.start);
		now=Max(tmp.time+tmp.start,now+tmp.time);
		while(1){
			if(a[p].start<=now&&p<=n) pq.push(a[p++]);
			else break;
		}
	}
	printf("%d",ans);
}
