//最大流
#include<cstring>
#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
#define INF 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+5;
int n,m,s,t;
int head[maxn],cnt;
struct Edge
{
    int v,w;
    int next;
}e[maxn<<1];
void addEdge(int u,int v,int w)
{
    e[++cnt]={v,w,head[u]};
    head[u]=cnt;
    e[++cnt]={u,0,head[v]};
    head[v]=cnt;
}

struct Dinic
{
    int cur[maxn],d[maxn];
    bool bfs()
    {
        queue<int> q;
        for(int i=0;i<=n+1;i++)
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

    int dfs(int u,int flow)
    {
        int nowflow=0;
        if(u==t) return flow;
        for(int i=cur[u];i!=-1;i=e[i].next)
        {
            cur[u]=i;
            int v=e[i].v;
            if(d[v]==d[u]+1&&e[i].w>0)
            {
                if(int k=dfs(v,min(flow-nowflow,e[i].w)))
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
    int din()
    {
        int ans=0;
        while(bfs())
        {
            for(int i=0;i<=n+1;i++)
                cur[i]=head[i];

            ans+=dfs(s,INF);
        }
        return ans;
    }
}_din;

int du[maxn];
void Init()
{
    cnt=-1;
    mem(head,-1);
    mem(du,0);
    s=0,t=n+1;

}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        Init();
        while(m--)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            du[u]++,du[v]--;
            if(w == 0)//双向
                addEdge(u,v,1);
        }
        int mf=0;
        for(int i=1;i<=n;i++)
        {
            if(du[i]>0)
                addEdge(s,i,du[i]/2),mf+=du[i]/2;
            else if(du[i]<0)
                addEdge(i,t,-du[i]/2);
            if(du[i]&1)
            {
                mf=-INF;
                break;
            }
        }
        int ans=_din.din();
        if(mf==ans)
            puts("possible");
        else
            puts("impossible");
    }
}



//费用流
#include<cstring>
#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
#define ll long long
#define INF 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+5;
int n,m,s,t;
int head[maxn],cnt;
struct Edge
{
    int v,flow,dis;
    int next;
}e[maxn];
void addEdge(int u,int v,int flow,int dis)
{
    e[++cnt]={v,flow,dis,head[u]};
    head[u]=cnt;
    e[++cnt]={u,0,-dis,head[v]};
    head[v]=cnt;
}

struct MCMF
{
    int dis[maxn],pre[maxn],last[maxn];
    bool vis[maxn];
    int flow[maxn];
    bool spfa()
    {
        mem(dis,INF);
        mem(flow,INF);
        mem(vis,0);
        queue<int> q;

        q.push(s);
        vis[s]=1;
        dis[s]=0;
        pre[t]=-1;

        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            vis[u]=0;
            for(int i=head[u];~i;i=e[i].next)
            {
                int v=e[i].v;
                if(e[i].flow&&dis[v]>dis[u]+e[i].dis)
                {
                    dis[v]=dis[u]+e[i].dis;
                    pre[v]=u;
                    last[v]=i;
                    flow[v]=min(flow[u],e[i].flow);
                    if(!vis[v])
                    {
                        vis[v]=1;
                        q.push(v);
                    }
                }
            }
        }
        return pre[t]!=-1;
    }

    int maxflow;ll mincost;
    int mcmf()
    {
        mincost=0,maxflow=0;
        while(spfa())
        {
            ll flow=INF;
            for(int i=t;i!=s;i=pre[i])
                flow=min(flow,(ll)e[last[i]].flow);
            mincost+=dis[t]*flow;
            maxflow+=flow;
            for(int i=t;i!=s;i=pre[i])
            {
                e[last[i]].flow-=flow;
                e[last[i]^1].flow+=flow;
            }
        }
        return mincost;
    }
}_mcmf;

int pre[maxn];
int Find(int x)
{
    while(x!=pre[x])
        x=pre[x];

    return x;
}
bool mix(int a,int b)
{
    int fa=Find(a);
    int fb=Find(b);
    if(fa!=fb)
    {
        pre[fb]=fa;
        return 0;
    }
    return 1;
}

int tot,ans,du[maxn];
void Init()
{
    s=0,t=n+1;
    cnt=-1;
    mem(head,-1);
    mem(du,0);
    for(int i=1;i<=n;i++)
        pre[i]=i;
    ans=0;
    tot=n;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        Init();
        while(m--)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            du[u]++,du[v]--;
            if(w == 0)//双向
                addEdge(u,v,1,0);
            if(!mix(u,v))
                tot--;
        }
        ///是否连通
        if(tot!=1)
        {
            puts("impossible");
            continue;
        }
        int mf=0;
        for(int i=1;i<=n;i++)
        {
            if(du[i]>0)
                addEdge(s,i,du[i]/2,0),mf+=du[i]/2;
            else if(du[i]<0)
                addEdge(i,t,-du[i]/2,0);
            if(du[i]&1)
            {
                mf=-INF;
                break;
            }
        }
        _mcmf.mcmf();
        int ans=_mcmf.maxflow;
        if(mf==ans)
            puts("possible");
        else
            puts("impossible");
    }
}
