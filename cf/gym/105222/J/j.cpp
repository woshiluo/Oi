#include<bits/stdc++.h>
using namespace std;
long long num;
int cost1[20],cost2[20],a[20];
const int b[10]={0,1,5,10,50,100,500,1000};
int f[20][210][2];
int main()
{
    ios::sync_with_stdio(false);
    int T;cin>>T;
    while(T --> 0){
        cin>>num;a[0]=0;
        while(num){
            a[++a[0]]=num%10;
            num/=10;
        }
        reverse(a+1,a+1+a[0]);
        for(int i=0;i<10;i++)
            cin>>cost1[i];
        for(int i=1;i<=7;i++)
            cin>>cost2[i];
        memset(f,0x3f,sizeof f);
        f[0][0][0]=0;
        for(int i=1;i<=a[0];i++){
            for(int j=0;j<=200;j++){
                if(j*10+a[i]<=200)
                    f[i][j*10+a[i]][0]=min(f[i][j*10+a[i]][0],f[i-1][j][0]);
                for(int k=0;k<10;k++)
                if(j*10+a[i]-k>=0&&j*10+a[i]-k<=200)
                    f[i][j*10+a[i]-k][1]=min(f[i][j*10+a[i]-k][1],min(f[i-1][j][0],f[i-1][j][1])+cost1[k]);
                for(int k=1;k<=7;k++)
                if(j*10+a[i]-b[k]>=0&&j*10+a[i]-b[k]<=200)
                    f[i][j*10+a[i]-b[k]][1]=min(f[i][j*10+a[i]-b[k]][1],min(f[i-1][j][0],f[i-1][j][1])+cost2[k]);
            }
        }
        cout<<f[a[0]][0][1]<<'\n';
    }
}
/*
1 102
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1
*/