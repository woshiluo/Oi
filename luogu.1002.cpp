#include <cstdio>
using namespace std;

long long a[30][30];

void mmp(int x,int y){
	a[x][y]=-1;
	a[x-1][y-2]=-1;
	a[x-2][y-1]=-1;
	a[x-2][y+1]=-1;
	a[x-1][y+2]=-1;
	a[x+1][y-2]=-1;
	a[x+2][y-1]=-1;
	a[x+2][y+1]=-1;
	a[x+1][y+2]=-1;
}


int main(){
	long long xa,ya,xb,yb;
	scanf("%lld%lld%lld%lld",&xa,&ya,&xb,&yb);
	mmp(xb,yb);
	a[0][0]=1;
	for(int i=0;i<=xa;i++){
		for(int j=0;j<=ya;j++){
			if(i==0&&j==0)continue;
			long long temp=0;
			if(a[i-1][j]>=0&&i!=0) temp+=a[i-1][j];
			if(a[i][j-1]>=0&&j!=0) temp+=a[i][j-1];
			if(a[i][j]>=0)a[i][j]=temp;
		}
	}
	printf("%lld",a[xa][ya]);
}	
