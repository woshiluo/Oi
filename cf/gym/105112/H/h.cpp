#include<bits/stdc++.h>
using namespace std;
int n,cnt1,cnt2;
priority_queue<pair<int,int>>q;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    while(cin>>n){
        cnt1=cnt2=0;
        while(!q.empty())q.pop();
        while(n --> 0){
            int x=read();
            if(x>2)q.push({-x,0});
            if(x==1)cnt1++;
            if(x==2)cnt2++;
        }
        int flag=0;
        while(cnt1&&cnt2){
            q.push({-3,1});
            cnt1--;cnt2--;
        }
        if(cnt1){
            while(cnt1>=3){
                q.push({-3,2});
                cnt1-=3;
            }
            if(cnt1==2)q.push({-2,1});
            else if(cnt1==1){
                if(q.size()>0&&q.top().first==-3&&q.top().second){
                    pair<int,int>temp=q.top();q.pop();
                    temp.first++;temp.second--;
                    q.push(temp);
                    q.push({-2,1});
                }else q.push({-1,0});
            }
        }
        while(cnt2--)q.push({-2,0});
        while(!q.empty()){
            if(q.top().first==-1&&q.size()==1)break;
            if(q.top().first!=-1)break;
            q.pop();
            pair<int,int>temp=q.top();q.pop();
            temp.first--;temp.second++;
            q.push(temp);
        }
        while(!q.empty()){
            pair<int,int>temp=q.top();q.pop();
            if(flag)printf("*");
            if(temp.second==0){
                printf("%d",-temp.first);
                flag=1;
                continue;
            }
            printf("(%d",-temp.first-temp.second);
            for(int i=1;i<=temp.second;i++)
                printf("+1");
            printf(")");
            flag=1;
        }
        printf("\n");
    }
}
/*
5
2 2 2 1 1

(2+1)*(2+1)*2


*/