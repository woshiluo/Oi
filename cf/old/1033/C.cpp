#include <cstdio>

inline int Min(int a,int b){return a<b?a:b;}

const int N=110000;

bool flag;
int n,tmp,cnt;
int a[N],ra[N];
// ra[i] 
// - 2 unknow
// - 0 A
// - 1 B

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		flag=false;
		ra[i]=2;
		tmp=i;
		while(1){
			tmp-=a[i];
			if(tmp<=0) break;
			if(a[tmp]>a[i]) flag=true; 
		}
		tmp=i;
		while(1){
			tmp+=a[i];
			if(tmp>n) break;
			if(a[tmp]>a[i]) flag=true; 
		}
		if(!flag) ra[i]=1;
	}
	for(int i=1;i<=n;i++){
		tmp=i;
		while(1){
			tmp-=a[i];
			if(tmp<=0) break;
			if(a[tmp]>a[i]&&ra[tmp]!=2) ra[i]=Min(ra[i],(ra[tmp]+1)%2); 
		}
		tmp=i;
		while(1){
			tmp+=a[i];
			if(tmp>n) break;
			if(a[tmp]>a[i]&&ra[tmp]!=2) ra[i]=Min(ra[i],(ra[tmp]+1)%2); 
		}
	}
	for(int i=1;i<=n;i++){
		tmp=i;
		while(1){
			tmp-=a[i];
			if(tmp<=0) break;
			if(a[tmp]>a[i]&&ra[tmp]!=2) ra[i]=Min(ra[i],(ra[tmp]+1)%2); 
		}
		tmp=i;
		while(1){
			tmp+=a[i];
			if(tmp>n) break;
			if(a[tmp]>a[i]&&ra[tmp]!=2) ra[i]=Min(ra[i],(ra[tmp]+1)%2); 
		}
	}
	for(int i=1;i<=n;i++){
		tmp=i;
		while(1){
			tmp-=a[i];
			if(tmp<=0) break;
			if(a[tmp]>a[i]&&ra[tmp]!=2) ra[i]=Min(ra[i],(ra[tmp]+1)%2); 
		}
		tmp=i;
		while(1){
			tmp+=a[i];
			if(tmp>n) break;
			if(a[tmp]>a[i]&&ra[tmp]!=2) ra[i]=Min(ra[i],(ra[tmp]+1)%2); 
		}
	}
	for(int i=1;i<=n;i++){
		if(ra[i]==1) printf("B");
		else printf("A");
//		printf("%d ",ra[i]);
	}
}
