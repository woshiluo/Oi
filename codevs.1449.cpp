#include <cstdio>
using namespace std;

int main(){
	int n,cnt=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cnt*=i;
	}
	printf("%d",cnt);
}
