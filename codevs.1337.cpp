#include <cstdio>
using namespace std;

char temp_zg[510][510];
int a[510][510],z[510][510],min_time[510][510];

int main(){
	int n,m,time;
	scanf("%d %d %d",&n,&m,&time); 
	for(int i=0;i<n;i++){
		scanf("%s",temp_zg[i]);
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(temp_zg[i][j]=='T'||temp_zg[i][j]=='t') {
				a[i][j]=2;
			}
			else if(temp_zg[i][j]=='A'||temp_zg[i][j]=='a'){
				a[i][j]=1;
				z[i][j]=0;
			}
			else if(temp_zg[i][j]=='W'||temp_zg[i][j]=='w'){
				a[i][j]=3;
				z[i][j]=-1;
			}
			else a[i][j]=1;
		}
	}
	if(a[0][0]!=1||a[n-1][m-1]!=1){ printf("Oh my god!");return 0;}
	z[0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(z[i][j]==-1)continue;
			int temp=0,temp2=0;
			bool bl=false;
			if(z[i-1][j]!=-1&&i-1>=0){
				temp=min_time[i-1][j]+a[i][j];
				bl=true;
				if(min_time[i-1][j]==0){ 
					if(i-1!=0)temp=0;
					if(j!=0)temp=0;
				}
			}
			if(z[i][j-1]!=-1&&j-1>=0){
				temp2=min_time[i][j-1]+a[i][j];
				bl=true;
				if(min_time[i][j-1]==0){ 
					if(i!=0)temp2=0;
					if(j-1!=0)temp2=0;
				}	
			}
			if(bl){
				if(temp==0) {min_time[i][j]=temp2;continue;}
				if(temp2==0) {min_time[i][j]=temp;continue;}
				if(temp<temp2) min_time[i][j]=temp;
				else min_time[i][j]=temp2;
			}
		}
	}
	if(min_time[n-1][m-1]!=0&&min_time[n-1][m-1]<time) printf("%d",min_time[n-1][m-1]);
	else printf("Oh my god!");
}
