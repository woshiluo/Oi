#include <cstdio>
#include <cstring>
using namespace std;

struct FUCK{
	int a[4][4],x,y,deep;
}dl[400000],ed;

int z;
int dx[4]={0,-1,0,1};
int dy[4]={-1,0,1,0};
int p[16];

long long zys(FUCK md){

	int a[10],l=0,r=0;

	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			l++;
			a[l]=md.a[i][j]+1;
		}
	}

	long long ans=0;bool x[20];
	memset(x,false,sizeof(x));

	for(long long i=1;i<=8;i++){
		r=0;
		
		for(int j=1;j<a[i];j++) if(x[j]==false) r++;
	
		ans=ans+r*p[9-i];
		x[a[i]]=true;
	}

	ans++;
	return ans;
}

int main(){
	p[0]=1;
	for(int i=1;i<=15;i++) p[i]=p[i-1]*i;

	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			scanf("%d",&dl[1].a[i][j]);
			if(dl[1].a[i][j]==0){
				dl[1].x=i;
				dl[1].y=j;
			}
		}
	}
	dl[1].deep=1;

	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			scanf("%d",&ed.a[i][j]);
		}
	}	
	z=zys(ed);

	int l,r;
	l=r=1;
	
	bool xd[400000];
	memset(xd,false,sizeof(xd));
	
	while(l<=r){
		for(int i=0;i<4;i++){
			FUCK fir=dl[l];
			fir.x=dl[l].x+dx[i];
			fir.y=dl[l].y+dy[i];
			
			if(fir.x>=1&&fir.x<=3&&fir.y>=1&&fir.y<=3){
				int temp=fir.a[fir.x][fir.y];
				fir.a[fir.x][fir.y]=fir.a[dl[l].x][dl[l].y];
				fir.a[dl[l].x][dl[l].y]=temp;
				int temp_kt=zys(fir);
				fir.deep=dl[l].deep+1;
				
				if(!xd[temp_kt]){
					xd[temp_kt]=true;
					r++;
					dl[r]=fir;
					if(temp_kt==z){
						printf("%d\n",fir.deep);
						return 0;
					}
				}
			
			}
		}
		l++;
	}
}
