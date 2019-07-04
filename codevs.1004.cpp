#include <cstdio>
using namespace std;

struct node{
    int a[4][4],deep; 
    int next;
}dl[440000];


int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
char qp[4][4];
//O->0 B->1 W->2
bool lx(node temp){
    for(int i=0;i<4;i++){
        if(temp.a[i][0]==temp.a[i][1]&&temp.a[i][0]==temp.a[i][2]&&temp.a[i][0]==temp.a[i][3]) return true;
        if(temp.a[0][i]==temp.a[1][i]&&temp.a[0][i]==temp.a[2][i]&&temp.a[0][i]==temp.a[3][i]) return true;
    }
    if(temp.a[0][0]==temp.a[1][1]&&temp.a[0][0]==temp.a[2][2]&&temp.a[0][0]==temp.a[3][3]) return true;
    if(temp.a[0][3]==temp.a[1][2]&&temp.a[0][3]==temp.a[2][1]&&temp.a[0][3]==temp.a[3][0]) return true;
    return false;
}


int main(){
    for(int i=0;i<4;i++){
        scanf("%s",qp[i]);
        for(int j=0;j<4;j++){
            if(qp[i][j]=='O') dl[1].a[i][j]=0;
            if(qp[i][j]=='B') dl[1].a[i][j]=1;
            if(qp[i][j]=='W') dl[1].a[i][j]=2;
        }
    }
    dl[1].deep=0;

    int l,r;
    l=r=1;

    while(l<=r){
        node fir=dl[l];
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(fir.a[i][j]==0) continue;
                for(int k=0;k<4;k++){
                    int tx=i+dx[k];
                    int ty=j+dy[k];
                    
                    if(fir.a[tx][ty]==0 && ( (fir.a[i][j]!=0 && fir.a[i][j]==fir.next) || fir.next==0 ) && tx>=0 && tx<4 && ty>=0 && ty<4){
                        node temp=dl[l];
                        if(temp.next==1) temp.next=2;
                        else if(temp.next==2) temp.next=1;
                        else if(temp.next==0){
                            if(temp.a[i][j]==1) temp.next=2;
                            else temp.next=1;
                        }
                        int tem=temp.a[i][j];
                        temp.a[i][j]=temp.a[tx][ty];
                        temp.a[tx][ty]=tem;
                        temp.deep++;

                        dl[++r]=temp;
/*                        for(int ii=0;ii<4;ii++){
                            for(int jj=0;jj<4;jj++){
                                printf("%d ",temp.a[ii][jj]);
                            }
                            printf("\n");
                        }
                        printf("\n");*/
                        if(lx(temp)){
                            printf("%d\n",temp.deep);
                            return 0;
                        }
                    }
                }
            }
        }
        l++;
    }
}
