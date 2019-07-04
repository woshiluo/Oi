#include <cstdio>
#include <cstring>
using namespace std;

long long n,k,tcnt;
long long p[16];
long long a[20],b[20];
bool x[20];

long long zys(){
	long long ans=0;
	memset(x,false,sizeof(x));
	for(long long i=1;i<=n-1;i++){
		long long tcnt=0;
		for(long long j=1;j<a[i];j++) if(x[j]==false) tcnt++;
		ans=ans+tcnt*p[n-i];
		x[a[i]]=true;
	}
	ans++;
	return ans;
}

void nys(long long cnt){
	cnt--;
	memset(x,true,sizeof(x));
	for(long long i=1;i<=n;i++){
		long long tcnt=cnt/p[n-i];
		cnt-=tcnt*p[n-i];
		long long j;
		for(j=1;j<=n;j++){
			if(x[j]==true){
				if(tcnt==0) break;
				tcnt--;
			}	
		}
		x[j]=false;
		a[i]=j;
	}
	for(long long i=1;i<n;i++) printf("%lld ",a[i]);
	printf("%lld\n",a[n]);
}

int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	p[0]=1;for(int i=1;i<=15;i++){p[i]=i*p[i-1];}
	printf("%lld\n",zys());
	scanf("%lld",&k);
	nys(k);
}
