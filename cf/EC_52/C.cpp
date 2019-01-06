#include <cstdio>
using namespace std;

const int N=210000;

inline int Max(int a,int b){return a>b?a:b;}

int n,k,tmp,ans,Mahei=0,Mihei=0x7fffffff;
int f[N][20];

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&tmp);
		Mahei=Mahei>tmp?Mahei:tmp;
		Mihei=Mihei<tmp?Mihei:tmp;
		f[tmp][0]++;
	}
	for(int j=Mahei;j>=1;j--){
		f[j][0]+=f[j+1][0];
	}
	for(int j=1;j<=20;j++){
		for(int i=1;i<=Mahei;i++){
			if(i+(1<<(j-1))<=Mahei) f[i][j]=f[i][j-1]+f[i+(1<<(j-1))][0];	
		}
	}
	Mihei++;
	while(Mihei<Mahei){
		for(int j=20;j>=0;j--){
			if(f[Mihei][j]<=k&&Mihei+Max(1<<(j-1),0)+1<=Mahei){
				ans++;
				Mihei+=Max(1<<(j-1),0);
				Mihei++;
				break;
			}
		}
	}
	printf("%d",ans);
}
