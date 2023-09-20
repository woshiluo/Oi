#include <cstdio>
using namespace std;

const int N=70;

int n,temp;
int sti[N],scnt,Mmin=0x7fffffff,Mmax;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&temp);
		if(temp<=50){
			sti[++scnt]=temp;
			Mmin=temp<Mmin?temp:Mmin;
			Mmax=temp>Mmax?temp:Mmax;
		}
	}
	dfs(0,0);
}
