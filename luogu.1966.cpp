#include <cstdio>
#include <algorithm>
using namespace std;

const int N=110000;
const int mod=99999997;

int n,ans=0;;
int t[N],d[N];
struct node{
	int id,now;
}a[N],b[N];

bool cmp(node a,node b){return a.now<b.now;}

void margesort(int left,int rig){
	if(left==rig) return ;
	int mid=(left+rig)>>1;
	margesort(left,mid);
	margesort(mid+1,rig);
	int now=left,lcnt=left,rcnt=mid+1;
	for(;lcnt<=mid&&rcnt<=rig;now++){
		if(t[lcnt]>t[rcnt]){
			d[now]=t[lcnt++];
			ans=(ans+rig-rcnt+1)%mod;
		}	
		else d[now]=t[rcnt++];
	}
	for(;lcnt<=mid;lcnt++,now++) d[now]=t[lcnt];
	for(;rcnt<=rig;rcnt++,now++) d[now]=t[rcnt];
	for(int i=left;i<=rig;i++) t[i]=d[i];
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		a[i].id=i;
		scanf("%d",&a[i].now);
	}
	for(int i=1;i<=n;i++){
		b[i].id=i;
		scanf("%d",&b[i].now);
	}
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++) t[a[i].id]=b[i].id;
	margesort(1,n);
	printf("%d",ans);
}
