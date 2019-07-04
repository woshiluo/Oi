#include <cstdio>
#include <cstring>
using namespace std;

int main(){
	int n;
	scanf("%d",&n);
	char a[n][210];
	int b[n][210];
	int cnt=0;
	memset(b,0,sizeof(b));
	memset(a,0,sizeof(a));
	for(int i=0;i<n;i++){
		scanf("%s",a[i]);
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<=200;j++){
			if(a[i][j]=='*'||a[i][j]=='.') continue;
			if(a[i][j]==' '||a[i][j]==0) break;
			int max_cnt=0;
			if(b[i][j+1]!=0&&j+1<=200){
				int temp_cnt=b[i][j+1];
				if(temp_cnt>max_cnt)max_cnt=temp_cnt;
			}
			if(b[i][j-1]!=0&&j-1>=0){
				int temp_cnt=b[i][j-1];
				if(temp_cnt>max_cnt)max_cnt=temp_cnt;
			}
			if(b[i+1][j]!=0&&i+1<n){
				int temp_cnt=b[i+1][j];
				if(temp_cnt>max_cnt)max_cnt=temp_cnt;
			}
			if(b[i-1][j]!=0&&i-1>=0){
				int temp_cnt=b[i-1][j];
				if(temp_cnt>max_cnt)max_cnt=temp_cnt;
			}
			if(max_cnt==0){
				cnt++;
				b[i][j]=cnt;
			}
			else {
				b[i][j]=max_cnt;
			}
		}
	}
	printf("%d",cnt);
}
