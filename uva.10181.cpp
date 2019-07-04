#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;

// FUCK 储存棋牌的结构体
// 忽略这个名字
struct FUCK{
	int a[5][5],x,y,deep,mhd,k,dlen;
	char d[100];
}st,ed;


// cmp2 控制优先队列排序规则
struct cmp2{
    bool operator ()(FUCK a,FUCK b){
        return a.mhd>b.mhd;
    }
};

//优先队列大法
priority_queue<FUCK,vector<FUCK>,cmp2> q;

int z,n;
int dx[4]={0,-1,0,1};// dx[] x轴增量
int dy[4]={-1,0,1,0};// dy[] y轴增量
int p[16],jwxy[16][2];// p[] 储存阶乘 jwxy[][]  结(j)尾(w)x轴(x)y轴(y)记录
char mmp[4]={'D','R','U','L'};
// 计算曼(m)哈(h)顿(d)距(j)离(l)
int mhdjl(FUCK b){
	int ans=0;
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			ans+=abs(jwxy[ b.a[i][j] ][1]-i)+abs(jwxy[ b.a[i][j] ][2]-j);	
		}
	}
	return ans;
}

int main(){
	scanf("%d",&n);
	int temp=0;
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			ed.a[i][j]=++temp;
			jwxy[ ed.a[i][j] ][1]=i;
			jwxy[ ed.a[i][j] ][2]=j;
		}
	}
	ed.a[4][4]=0;
	ed.x=ed.y=4;
	while(n!=0){
		for(int i=1;i<=4;i++){
			for(int j=1;j<=4;j++){
				scanf("%d",&st.a[i][j]);
				if(st.a[i][j]==0){
					st.x=i;st.y=j;	
				}
			}
		}
		st.dlen=0;
		st.mhd=mhdjl(st);
		q.push(st);
		while(!q.empty()){
			for(int i=0;i<4;i++){
				FUCK temp=q.top();
				FUCK f=q.top();
				temp.x=f.x+dx[i];
				temp.y=f.y+dy[i];

				if(temp.x>=1&&temp.x<=4&&temp.y>=1&&temp.y<=4){
					int temp_xy=temp.a[temp.x][temp.y];
					temp.a[temp.x][temp.y]=temp.a[f.x][f.y];
					temp.a[f.x][f.y]=temp_xy;
					temp.deep=f.deep+1;
					temp.mhd=mhdjl(temp);
					temp.d[temp.dlen++]=mmp[i];
					q.push(temp);
				
                    printf("%d\n%d\n%d\n",temp.deep,temp.x,temp.y);
                    bool mdzz=true;
					for(int j=1;j<=4;j++){
						for(int k=1;k<=4;k++){
							if(temp.a[j][k]!=ed.a[j][k]) mdzz=false;
						}
					}
					if(mdzz){
						for(int j=1;j<=4;j++){
							for(int k=1;k<=4;k++){
								printf("%d  ",temp.a[j][k]);
							}
							printf("\n");
						}
						for(int j=0;j<temp.dlen;j++){
							printf("%c",temp.d[j]);
						}
                        break;
					}
				}
			}
			q.pop();
		}
		n--;
	}
}
