#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3f
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+5;
int n,m,s,t;
int head[maxn],cnt;
struct Edge
{
    int v;
    ll w;
    int next;
}e[maxn<<1];
void addEdge(int u,int v,ll w)
{
    e[++cnt]={v,w,head[u]};
    head[u]=cnt;
}
struct Dinic
{
    int cur[maxn],d[maxn];
    bool bfs()
    {
        queue<int> q;
        for(int i=0;i<=2*n;i++)
            d[i]=-1;
        d[s]=0;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=head[u];i!=-1;i=e[i].next)
            {
                int v=e[i].v;
                if(d[v]==-1&&e[i].w>0)
                {
                    d[v]=d[u]+1;
                    q.push(v);
                }
            }
        }
        return d[t]!=-1;
    }

    ll dfs(int u,ll flow)
    {
        ll nowflow=0;
        if(u==t) return flow;
        for(int i=cur[u];i!=-1;i=e[i].next)
        {
            cur[u]=i;
            int v=e[i].v;
            if(d[v]==d[u]+1&&e[i].w>0)
            {
                if(ll k=dfs(v,min(flow-nowflow,e[i].w)))
                {
                    e[i].w-=k;
                    e[i^1].w+=k;
                    nowflow+=k;
                    if(nowflow==flow)
                        break;
                }
            }
        }
        if(!nowflow) d[u]=-2;
        return nowflow;
    }
    ll din()
    {
        ll ans=0;
        while(bfs())
        {
            for(int i=0;i<=2*n;i++)
                cur[i]=head[i];

            ans+=dfs(s,INF);
        }
        return ans;
    }
}_din;

void Init()
{
    mem(head,-1);
    cnt=-1;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        Init();
        scanf("%d%d",&n,&m);
        s=2+n,t=0;

        ///0       汇点
        ///1 ~ n   入点
        ///n+1 2n  出点

        ///出点与入点连边(i,i',1)
        for(int i=1;i<=n;++i)
            addEdge(i,i+n,1);
        for(int i=1;i<=m;++i)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            if(u<1||u>n||v<1||v>n)
                continue;
            ///无向边拆成两个有向边
            ///(u',v,1),(v',u,1)
            addEdge(u+n,v,1);
            addEdge(v+n,u,1);
        }
        ///1'、3'连接到汇点
        addEdge(1+n,t,1);
        addEdge(3+n,t,1);

        if(_din.din()==2)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
