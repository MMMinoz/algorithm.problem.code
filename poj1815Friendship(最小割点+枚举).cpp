#include<iostream>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
#define INF 0x3f3f3f3f
const int maxn=5000+5;
int n,s,t;
int ans[maxn];
bool vis[maxn];
int Map[205][205];
struct Edge
{
    int v,w;
    int next;
}e[maxn<<1];

int head[maxn],cnt;
void addEdge(int u,int v,int w)
{
    e[++cnt]={v,w,head[u]};
    head[u]=cnt;
    e[++cnt]={u,0,head[v]};
    head[v]=cnt;
}

struct Din
{
    int cur[maxn],d[maxn];
    bool bfs()
    {
        for(int i=0;i<=2*n;i++)
            d[i]=-1;
        d[s]=0;
        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=head[u];~i;i=e[i].next)
            {
                int v=e[i].v;
                if(d[v]==-1&&e[i].w)
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
        if(u==t)
            return flow;
        int nowflow=0;
        for(int i=cur[u];~i;i=e[i].next)
        {
            cur[u]=i;
            int v=e[i].v;
            if(d[v]==d[u]+1&&e[i].w)
            {
                int k=dfs(v,min(flow-nowflow,e[i].w));
                if(k)
                {
                    nowflow+=k;
                    e[i].w-=k;
                    e[i^1].w+=k;
                    if(nowflow==flow)
                        break;
                }
            }
        }
        if(!nowflow)
            d[u]=-2;
        return nowflow;
    }

    int din()
    {
        int ans=0;
        while(bfs())
        {
            for(int i=0;i<=2*n;i++)
                cur[i]=head[i];
            ans+=dfs(s,INF);
        }
        return ans;
    }
}_din;

void build()
{
    cnt=-1;
    mem(head,-1);

    for(int i=1;i<=n;i++)
        if(!vis[i])
            addEdge(i,i+n,1);
    for(int i=1;i<=n;i++)
    {
        if(vis[i])
            continue;
        for(int j=1;j<=n;j++)
        {
            if(vis[j]||i==j)
                continue;
            if(Map[i][j])
                addEdge(i+n,j,INF);
        }
    }
}

int main()
{
    scanf("%d%d%d",&n,&s,&t);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&Map[i][j]);
    if(Map[s][t])
    {
        puts("NO ANSWER!");
        return 0;
    }

    s+=n;
    build();
    int result=_din.din();
    printf("%d\n",result);
    if(!result)
        return 0;

    int num=0;
    for(int i=1;i<=n;i++)
    {
        if(i==s-n||i==t)
            continue;
        vis[i]=1;
        build();
        int m=_din.din();
        if(m<result)
        {
            result--;
            ans[num++]=i;
            if(result==0)
                break;
        }
        else
            vis[i]=0;
    }
    for(int i=0;i<num-1;i++)
        printf("%d ",ans[i]);
    printf("%d\n",ans[num-1]);
}
