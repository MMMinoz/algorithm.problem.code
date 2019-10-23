#include<bits/stdc++.h>
#define maxn 1010
#define maxm 200010
#define ll long long
#define INF 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
int n,m,s,t,C,P;
int head[maxn],cnt;

struct Edge
{
    int v,flow,dis;//flow流量 dis花费
    int next;
}e[maxn];
void addEdge(int u,int v,int flow,int dis)
{
    e[++cnt]={v,flow,dis,head[u]};
    head[u]=cnt;
    e[++cnt]={u,0,-dis,head[v]};
    head[v]=cnt;
}

int dis[maxn],pre[maxn],last[maxn];
bool vis[maxn];
bool spfa(int s,int t)
{
    mem(pre,-1);
    mem(vis,0);
    mem(dis,INF);
    queue<int> q;
    q.push(s);
    pre[s]=s;
    dis[s]=0;
    vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=e[i].next)
        {
            int v=e[i].v;
            if(e[i].flow>0&&dis[u]+e[i].dis<dis[v])
            {
                dis[v]=dis[u]+e[i].dis;
                pre[v]=u;
                last[v]=i;
                if(!vis[v])
                {
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
    }
    return pre[t] != -1;
}

int maxflow;ll mincost;
int minCostFlow(int s,int t)
{
    mincost=0,maxflow=0;
    while(spfa(s,t))
    {
        ll flow=INF;
        for(int i=t;i!=s;i=pre[i])
            if(e[last[i]].flow<flow)
                flow=e[last[i]].flow;
        mincost+=dis[t]*flow;
        maxflow+=flow;
        if(mincost>C)
        {
            maxflow-=ceil((mincost-C)*1.0/dis[t]);
            break;
        }
        for(int i=t;i!=s;i=pre[i])
        {
            e[last[i]].flow-=flow;
            e[last[i]^1].flow+=flow;
        }
    }
    return mincost;
}


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
        scanf("%d%d%d%d",&n,&m,&C,&P);
        Init();
        int s=n,t=1;
        addEdge(s,0,INF,P);
        for(int i=1;i<=m;i++)
        {
            int u,v,c1,c2;
            scanf("%d%d%d%d",&u,&v,&c1,&c2);
            addEdge(u,v,c1,0);
            addEdge(v,u,c1,0);
            addEdge(u,v,INF,c2);
            addEdge(v,u,INF,c2);
        }
        minCostFlow(s,t);
        printf("%d\n",maxflow);
    }
    return 0;
}
