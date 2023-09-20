#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
const int N=200005;
const int M = 1e6 + 1e5;
int n,m,q;
int c[N];
set<int>s;
set<int>pos[M];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>c[i];
	int premn=c[0],prei=0;
	s.insert(0);
	pos[c[0]].insert(0);
	long long ans=0;
	for(int i=1;i<n;i++)
	{
		if(c[i]<premn)
		{
			s.insert(i);
			ans+=(long long)(i-prei)*c[prei];
			prei=i;
		}
		premn=min(premn,c[i]);
		pos[c[i]].insert(i);
	}
	ans+=(long long)(n-prei)*c[prei];
	cout<<ans<<"\n";

	cin>>q;
	while(q--)
	{
		int p,v;
		cin>>p>>v;
		if(p==1)
		{
			bool del=false;
			auto it=s.find(v);
			if(it!=s.end())
			{
				if(it!=s.begin())
				{
					auto pre=prev(it);
					if(c[*pre]<=c[v]+1) del=true;
				}
				auto nxt=next(it);
				auto np=pos[c[v]].upper_bound(v);
				// cerr<<"nxt"<<*nxt<<"\n";
				// if(np!=pos[c[v]].end()) cerr<<"find"<<*np<<"\n";
				if(np!=pos[c[v]].end()&&(nxt==s.end()||*np<*nxt))
				{
					ans+=(*np-v);
					s.insert(*np);
					// cerr<<"insert"<<*np<<"\n";
					it=s.find(v);
				}
				else
				{
					if(nxt!=s.end()) ans+=(*nxt-v);
					else ans+=n-v;
				}
				if(del) s.erase(v);
			}
			pos[c[v]].erase(v);
			c[v]++;
			pos[c[v]].insert(v);
		}
		else if(p==2)
		{
			// exit(1);
			auto it=s.find(v);
			if(it!=s.end())
			{
				if(it!=s.begin())
				{
					auto pre=prev(it);
					auto np=pos[c[v]].upper_bound(*pre);
					if(np!=pos[c[v]].end()&&c[*pre]>c[v]&&(*np<v))
					{
						s.insert(*np);
						it=s.find(v);
					}
				}
				auto nxt=next(it);
				if(nxt!=s.end())
				{
					ans-=(*nxt-v);
					if(c[*nxt]>=c[v]-1) s.erase(nxt);
				}
				else ans-=(n-v);
			}
			else
			{
				if(s.empty()) exit(0);
				auto it=s.upper_bound(v);
				if(c[v]-1<c[*prev(it)])
				{
					if(it!=s.end())
					{
						ans-=*it-v;
						if(c[v]<=c[*it]) s.erase(it);
					}
					else ans-=n-v;
					s.insert(v);
				}
			}
			pos[c[v]].erase(v);
			c[v]--;
			pos[c[v]].insert(v);
		}
		// cerr<<"S:\n";
		// for(auto it:s)
			// cerr<<it<<" ";cerr<<"\n";
		cout<<ans<<"\n";
	}
	return 0;
}
