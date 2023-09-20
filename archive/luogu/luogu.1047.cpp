#include <cstdio>
using namespace std;

int l,m,s,t;
int a[110000];

int main(){
	scanf("%d%d",&l,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&s,&t);
		for(int j=s;j<=t;j++){
			a[j]=1;
		}
	}
	int cnt=0;
	for(int i=0;i<=l;i++){
		if(a[i]==0) cnt++;
	}
	printf("%d",cnt);
}
