#include<bits/stdc++.h>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
#define INF 0x3f3f3f3f
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
}
struct Dinic
{
    int cur[maxn],d[maxn];
    bool bfs()
    {
        queue<int> q;
        for(int i=0;i<=n+m+5;i++)
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
            for(int i=0;i<=n+m+5;i++)
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
double b[11];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        Init();
        scanf("%d%d",&n,&m);
        s=0,t=m+n+1;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                int A;
                scanf("%d",&A);
                if(A==2)
                {
                    addEdge(i,n+j,1);
                    addEdge(n+j,i,0);
                }
            }
        }
        int sum=0;
        for(int i=1;i<=m;i++)
        {
            scanf("%lf",b+i);
            sum+=b[i];
        }

        ///源点到糖果
        for(int i=1;i<=n;i++)
        {
            addEdge(s,i,1);
            addEdge(i,s,0);
        }

        ///孩子到汇点
        for(int i=1;i<=m;i++)
        {
            addEdge(n+i,t,b[i]/2.0);
            addEdge(t,n+i,0);
        }

        int x=_din.din();
//        printf("x=%d,x+N=%d,sum=%d\n",x,x+n,sum);
        if(x+n>=sum)
            puts("Yes");
        else
            puts("No");
    }
}
