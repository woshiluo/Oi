#include<stdio.h>

int a[110][110];
int b[110][110];

int jdz(int x){
	if ( x<0 ) return 0-x;
	return x;
}

int main(){
	int n,k; scanf("%d %d",&n,&k);
	for ( int i=1;i<=n;i++ ) for ( int j=1;j<=k;j++ ) scanf("%d",&a[i][j]);
	int n1,k1; scanf("%d %d",&n1,&k1);
	for ( int i=1;i<=n1;i++ ) for ( int j=1;j<=k1;j++ ) scanf("%d",&b[i][j]);
	int n2=n-n1+1;
	int k2=k-k1+1;
	int minn=1000001,x,y;
	for ( int i=1;i<=n2;i++ ){
		for ( int j=1;j<=k2;j++ ){
			int s=0;
			for ( int i1=1;i1<=n1;i1++ ){
				for ( int j1=1;j1<=k1;j1++ ){
					s+=jdz(a[i+i1-1][j+j1-1]-b[i1][j1]);
				}
			}
			if ( s<minn ) { x=i; y=j; minn=s; }
		}
	}
	for ( int i=1;i<=n1;i++ )
	{
		for ( int j=1;j<=k1;j++ ) printf("%d ",a[x+i-1][y+j-1]);
		printf("\n");
	}
	return 0;
}
