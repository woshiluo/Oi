#include<iostream>
#include<cstdio>
#include<vector>
#include "tree.h"
#define N 2000
#define M 20
using namespace std;
int lowbit(int x)
{
    return x&(-x);
}
int Base,num[1<<M],length,sz[1<<M],cl[N+1],A[N+1][N+1];
bool used[M+1][N+1];
std::vector<std::pair<int, int>> solve(int n)
{
    vector<pair<int,int>>E;
    vector<int>v;
    vector<vector<int>>d;
    if (n<=2000) Base=14;
    else Base=20;
    for (int i=1;i<(1<<Base);++i) sz[i]=sz[i-lowbit(i)]+1;
    for (int i=0;i<(1<<Base);++i)
	if (sz[i]==(Base>>1)&&length+1<=n-1)
	{
	    num[i]=++length;
	    for (int j=1;j<=Base;++j)
		if (i&(1<<(j-1)))
		    used[j][length]=1;
	}
    for (int i=1;i<=Base;++i)
    {
	v.clear();
	for (int j=1;j<=n-1;++j) v.push_back(used[i][j]);
	for( auto &x: v ) 
		printf( "%d", x );
	printf( "\n" );
	d=query(v);
	for (int j=0;j<d.size();++j)
	    for (int k=0;k<d[j].size();++k)
		cl[d[j][k]]=j;
	for (int j=0;j<n;++j)
	    for (int k=j+1;k<n;++k)
		if (cl[j]==cl[k])
		    A[j][k]|=(1<<(i-1));
    }
    for (int i=0;i<n;++i)
	for (int j=i+1;j<n;++j)
	    if (sz[A[i][j]]==((Base+1)>>1))
		E.push_back(make_pair(i,j));
    return E;
}
