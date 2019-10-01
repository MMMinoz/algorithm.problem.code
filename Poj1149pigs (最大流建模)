#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+5;
int n,m,s,t;
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
        for(int i=0;i<=n+m+6;i++)
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
            for(int i=0;i<=n+m+6;i++)
                cur[i]=head[i];

            ans+=dfs(s,INF);
        }
        return ans;
    }
}_din;

int vis[maxn];
int pig[maxn];
void Init()
{
    mem(head,-1);
    cnt=-1;
    mem(vis,0);
}

int main()
{
    Init();
    scanf("%d%d",&m,&n);
    s=0,t=m+n+5;
    int w;
    for(int i=1;i<=m;i++)
        scanf("%d",pig+i);

    ///猪窝编号 1->m
    ///人编号 m+1->m+n
    for(int i=1;i<=n;i++)
    {
        int k;
        scanf("%d",&k);
        while(k--)
        {
            int index;
            scanf("%d",&index);
            ///如果被打开了 加一条上一个人到这一个人 INF 的边
            if(vis[index])
            {
                addEdge(vis[index],i+m,INF);
                addEdge(i+m,vis[index],0);
            }
            ///如果没有打开 加一条源点到这个人 猪数量 的边
            else
            {
                vis[index]=i+m;
                addEdge(s,i+m,pig[index]);
                addEdge(i+m,s,0);
            }
        }

        int buy;
        scanf("%d",&buy);
        ///加每个人到汇点 购买力 的边
        addEdge(i+m,t,buy);
        addEdge(t,i+m,0);
    }
    printf("%d\n",_din.din());
}
