#include <cstdio>
using namespace std;

long long n,k,temp1,temp2;
long long c[20];
bool vis[20];
int main(){
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	scanf("%lld%lld",&n,&k);
	c[0]=1;
	for(long long i=1;i<=n;i++) c[i]=c[i-1]*i;
	for(long long i=n-1;i>=0;i--){
		if(c[i]!=0) temp1=k/c[i];
		temp1++;
		if(c[i]!=0) k%=c[i];
		if(k==0){
			k=c[i];
			temp1--;
		} 
		for(long long j=1;j<=n;j++){
			if(!vis[j]){
				temp1--;
				if(temp1==0){
					vis[j]=true;
					printf("%lld ",j);
				}
			}
		}
	}
	fclose(stdin);
	fclose(stdout);
}
