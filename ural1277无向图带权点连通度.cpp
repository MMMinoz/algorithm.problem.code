#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
const int maxn=1e4+5;
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
            for(int i=0;i<=2*n;i++)
                cur[i]=head[i];

            ans+=dfs(s,INF);
        }
        return ans;
    }
}_din;


void Init()
{
    cnt=-1;
    memset(head,-1,sizeof(head));
}
int main()
{
    int k;
    scanf("%d",&k);
    Init();
    scanf("%d%d%d%d",&n,&m,&s,&t);
    ///1~n  入点
    ///n~2n 出点
    ///权值为R
    for(int i=1;i<=n;i++)
    {
        int R;
        scanf("%d",&R);
        if(i==s||i==t)
        {
            addEdge(i,i+n,INF);
            continue;
        }
        addEdge(i,i+n,R);
    }
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u+n,v,INF);
        addEdge(v+n,u,INF);
    }
    
    ///特判源点汇点重合时 NO
    if(s==t)
    {
        puts("NO");
        return 0;
    }

    if(_din.din()<=k)
        puts("YES");
    else
        puts("NO");
}
