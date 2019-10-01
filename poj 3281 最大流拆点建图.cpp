#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e6+5;
int n,f,dd,s,t;
int head[maxn],cnt;
struct e
{
    int v;
    int w;
    int next;
}e[maxn<<1];
void addEdge(int u,int v,int w)
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
        for(int i=0;i<=2*n+f+dd+6;i++)
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
            for(int i=0;i<=2*n+f+dd+6;i++)
                cur[i]=head[i];

            ans+=dfs(s,INF);
        }
        return ans;
    }
}_din;

int vis[maxn];
void Init()
{
    mem(head,-1);
    cnt=-1;
    mem(vis,0);
}
int main()
{
    Init();
    scanf("%d%d%d",&n,&f,&dd);
    s=0,t=2*n+f+dd+5;
    ///牛拆点
    for(int i=1;i<=n;i++)
    {
        addEdge(i,i+n,1);
        addEdge(i+n,i,0);
    }
    ///源点向食物的边
    for(int i=1;i<=f;i++)
    {
        addEdge(s,i+2*n,1);
        addEdge(i+2*n,s,0);
    }
    ///饮料向汇点的边
    for(int i=1;i<=dd;i++)
    {
        addEdge(i+2*n+f,t,1);
        addEdge(t,i+2*n+f,0);
    }

    for(int i=1;i<=n;i++)
    {
        int k1,k2;
        scanf("%d%d",&k1,&k2);
        while(k1--)
        {
            ///食物向牛
            int food;
            scanf("%d",&food);
            addEdge(food+2*n,i,1);
            addEdge(i,food+2*n,0);
        }
        while(k2--)
        {
            ///牛向饮料
            int drink;
            scanf("%d",&drink);
            addEdge(i+n,drink+2*n+f,1);
            addEdge(drink+2*n+f,i+n,0);
        }
    }
    printf("%d\n",_din.din());
}
