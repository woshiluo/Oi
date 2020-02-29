#include <cstdio>
#include <cstring>
using namespace std;

int main(){
	int n;
	scanf("%d",&n);
	char a[n][n];
	memset(a,0,sizeof(a));
	for(int i=0;i<n;i++){
		 char temp[1000];
		 scanf("%s",temp);
		 for(int j=0;j<n;j++){
			a[i][j]=temp[j];
		 }
	}
	int m;
	scanf("%d",&m);
	for(int k=2;k<=m;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(a[i][j]=='@'){
					if(a[i][j+1]=='.'&&j+1<n)  a[i][j+1]='o';
					if(a[i][j-1]=='.'&&j-1>=0) a[i][j-1]='o';
					if(a[i+1][j]=='.'&&i+1<n)  a[i+1][j]='o';
					if(a[i-1][j]=='.'&&i-1>=0) a[i-1][j]='o';
				}
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(a[i][j]=='o') a[i][j]='@';
			}
		}
	}

	int ans=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(a[i][j]=='@') ans+=1;
		}
	}
	printf("%d",ans);
}
