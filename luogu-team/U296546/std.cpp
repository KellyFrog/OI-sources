#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

const int maxn=20;

int n,m,k;
vector<pair<int,int> > edg[maxn][maxn];

int val[maxn][maxn];

int dp[1<<maxn][maxn];
int fa[1<<maxn][maxn];


const int maxk=2005;
const int maxz=maxk*maxk/2;
struct node{
    int typ;
    int ei,ej;
}z[maxz];int zc;

struct fnode{
    int a,b;
    int es;
    bool typ;
}fv[maxk];

const int maxl=55;
int et[maxk*2][maxl];
int es[maxk*2],esz;

priority_queue<pair<double,int> > pq;
const int maxm=100005;
int eu[maxm],ev[maxm],ew[maxm];

mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
unsigned long long hv[maxm];

namespace ht{

const int maxh=maxz*2;
const int hl=22;
int ps;
unsigned long long ent[maxh];
int nxt[maxh];
int adj[1<<hl];

inline void add(unsigned long long x){
    int v=x&((1<<hl)-1);
    int id=++ps;
    ent[id]=x;nxt[id]=adj[v];
    adj[v]=id;
}
inline bool chk(unsigned long long x){
    int v=x&((1<<hl)-1);
    for(int i=adj[v];i;i=nxt[i]){
        if(ent[i]==x)return 1;
    }
    return 0;
}
}
unsigned long long hn[maxn];
int tarz[200];

double cm[maxn][maxn];
int cmt[maxn][maxn],tg;
int deg[maxn];
vector<int> adj[maxn];
int sq[200],qs,qe;
double calc(int a,int b,int sz){
    //cerr<<tg<<endl;
    ++tg;
    for(int i=0;i<n;i++)adj[i].clear(),deg[i]=0;
    for(int i=0;i<sz;i++){
        int id=tarz[i];
        int u=eu[id],v=ev[id],w=ew[id];
        if(cmt[u][v]!=tg){
            cmt[u][v]=tg;cm[u][v]=w;
            adj[u].push_back(v);adj[v].push_back(u);
            deg[u]++;deg[v]++;
        }else{
            cm[u][v]=w*cm[u][v]/(w+cm[u][v]);
        }
    }
    qs=qe=0;
    for(int i=0;i<n;i++)if(i!=a&&i!=b&&deg[i]==2){
        sq[++qe]=i;
    }
    while(qs!=qe){
        int u=sq[++qs];
        if(deg[u]!=2)continue;
        double sm=0;
        int iu=-1,iv=-1;
        for(int v:adj[u]){
            int cu=u,cv=v;if(u>v)swap(cu,cv);
            if(cmt[cu][cv]==tg){
                cmt[cu][cv]=-1;
                sm+=cm[cu][cv];
                if(iu==-1)iu=v;
                else iv=v;
            }
        }
        //cerr<<iu<<' '<<iv<<endl;
        deg[u]=0;
        if(iu>iv)swap(iu,iv);
        if(cmt[iu][iv]==tg){
            cm[iu][iv]=(sm*cm[iu][iv])/(sm+cm[iu][iv]);
            deg[iu]--;deg[iv]--;
            if(deg[iu]==2&&iu!=a&&iu!=b)sq[++qe]=iu;
            if(deg[iv]==2&&iv!=a&&iv!=b)sq[++qe]=iv;
        }else{
            cmt[iu][iv]=tg;
            cm[iu][iv]=sm;
            adj[iu].push_back(iv);adj[iv].push_back(iu);
        }
    }
    for(int i=0;i<n;i++){
        if(i==a||i==b){
            if(deg[i]!=1)return -1;
        }else{
            if(deg[i]!=0)return -1;
        }
    }
    return cm[a][b];
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>k;
    for(int i=0;i<n;i++)hn[i]=rng();
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;u--;v--;
        eu[i]=u;ev[i]=v;ew[i]=w;
        if(eu[i]>ev[i])swap(eu[i],ev[i]);
        hv[i]=rng();
        if(u!=v){
            edg[u][v].emplace_back(w,i);
            edg[v][u].emplace_back(w,i);
        }
    }
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        sort(edg[i][j].begin(),edg[i][j].end(),greater<pair<int,int> >());
        val[i][j]=edg[i][j].empty()?INT_MIN:edg[i][j].front().first;
    }
    for(int s=1;s<(1<<n);s++){
        for(int i=0;i<n;i++)if((s>>i)&1){
            dp[s][i]=0;
            fa[s][i]=-1;
            int s1=s-(1<<i);
            for(int j=0;j<n;j++)if((s1>>j)&1){
                int cur=dp[s1][j]+val[j][i];
                if(cur>dp[s][i]){
                    dp[s][i]=cur;
                    fa[s][i]=j;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        if(dp[(1<<n)-1][i]>0){
            int id=++zc;
            z[id].ei=-1;z[id].ej=i;
            z[id].typ=(1<<n)-1+(i<<n);
            pq.emplace((double)dp[(1<<n)-1][i],id);
        }
    }
    for(int i=1;i<=k;i++){
        if(pq.empty()){
            cout<<"-1\n";continue;
        }
        double val;int id;tie(val,id)=pq.top();pq.pop();
        int ep=++esz;
        unsigned long long hval=0;
        int tp,sp;
        int&zi=i;
        if(z[id].typ>=0){
            int i=z[id].typ>>n,s=z[id].typ-(i<<n);
            bool flg=1;
            int lss=s,lsi=i;
            if(z[id].ei!=-1&&z[id].ej<0){
                flg=0;
                tp=-z[id].ej-1;
            }else if(z[id].ei!=-1){
                int k1=z[id].ej>>20,ki=z[id].ej-(k1<<20);
                if(ki+1<edg[i][k1].size()){
                    int dlt=edg[i][k1][ki+1].first-edg[i][k1][ki].first;
                    int cid=++zc;
                    z[cid]=z[id];
                    z[cid].ej=(k1<<20)+(ki+1);
                    pq.emplace(val+dlt,cid);
                }
                //walk across
                s-=(1<<i);i=k1;
            }
            sp=z[id].ej;
            for(int cid=z[id].ei;cid!=-1;cid=z[cid].ei){
                int bi=(sp<0?-sp-1:lsi);
                if(sp>=0){
                    int k1=sp>>20,ki=sp-(k1<<20);
                    //cerr<<lsi<<' '<<ki<<' '<<k1<<endl;
                    et[ep][es[ep]++]=edg[lsi][k1][ki].second;
                    hval^=hv[edg[lsi][k1][ki].second];
                }
                sp=z[cid].ej;
                int ci=z[cid].typ>>n,cs=z[cid].typ-(ci<<n);
                lss=cs;lsi=ci;
                if(z[cid].ei!=-1){
                    cs-=(1<<ci);ci=z[cid].ej>>20;
                }
                while(ci!=bi){
                    int tmp=fa[cs][ci];
                    et[ep][es[ep]++]=edg[ci][tmp][0].second;
                    hval^=hv[edg[ci][tmp][0].second];
                    cs-=(1<<ci);
                    ci=tmp;
                }
                //find edges
            }
            if(flg){
                int ci=i,cs=s;
                while(1){
                    int v0=fa[cs][ci]==-1?0:dp[cs][ci]-dp[cs-(1<<ci)][fa[cs][ci]];
                    for(int j=0;j<n;j++){
                        if(((cs-(1<<ci))>>j)&1){
                            if(j!=fa[cs][ci]){
                                int x=dp[cs-(1<<ci)][j]+::val[ci][j];
                                if(x>0){
                                    int cid=++zc;
                                    //cerr<<"!"<<ci<<' '<<cs<<' '<<j<<endl;
                                    z[cid].ei=id;z[cid].ej=j<<20;
                                    z[cid].typ=(ci<<n)+cs;
                                    pq.emplace(val+(x-dp[cs][ci]),cid);
                                }
                            }else{
                                if(edg[ci][j].size()>1){
                                    int cid=++zc;
                                    z[cid].ei=id;z[cid].ej=(j<<20)+1;
                                    z[cid].typ=(ci<<n)+cs;
                                    pq.emplace(val+(edg[ci][j][1].first-v0),cid);
                                }
                            }
                        }
                    }
                    if(fa[cs][ci]==-1){
                        tp=ci;
                        break;
                    }else if(cs!=(1<<n)-1){
                        int cid=++zc;
                        z[cid].ei=id;z[cid].ej=-ci-1;
                        pq.emplace(val-dp[cs][ci],cid);
                    }
                    int tmp=fa[cs][ci];
                    et[ep][es[ep]++]=edg[ci][tmp][0].second;
                    hval^=hv[edg[ci][tmp][0].second];
                    cs-=(1<<ci);
                    ci=tmp;
                }
            }
            hval^=hn[sp]^hn[tp];
            if(ht::chk(hval)){
                zi--;
                continue;
            }
            ht::add(hval);
            if(sp>tp)swap(sp,tp);
            sort(et[ep],et[ep]+es[ep]);
            fv[zi].a=sp;fv[zi].b=tp;fv[zi].es=ep;fv[zi].typ=0;
        }else{
            fv[zi].a=fv[z[id].ei].a;
            fv[zi].b=fv[z[id].ej].b;
            fv[zi].typ=1;
            int ip=fv[z[id].ei].es,jp=fv[z[id].ej].es;
            int sz=merge(et[ip],et[ip]+es[ip],et[jp],et[jp]+es[jp],tarz)-tarz;
            sz=unique(tarz,tarz+sz)-tarz;
            memcpy(et[ep],tarz,sizeof(int)*sz);
            es[ep]=sz;
            fv[zi].es=ep;
        }
        cout<<fixed<<setprecision(10)<<val<<'\n';
        for(int j=1;j<i;j++){
            if(fv[i].typ&&fv[j].typ)continue;
            if(fv[i].a!=fv[j].a||fv[i].b!=fv[j].b)continue;
            int ip=fv[i].es,jp=fv[j].es;
            int sz=merge(et[ip],et[ip]+es[ip],et[jp],et[jp]+es[jp],tarz)-tarz;
            sz=unique(tarz,tarz+sz)-tarz;
            unsigned long long hsh=hn[fv[i].a]^hn[fv[i].b];
            for(int i=0;i<sz;i++)hsh^=hv[tarz[i]];
            if(ht::chk(hsh))continue;
            double u=calc(fv[i].a,fv[i].b,sz);
            //cerr<<u<<endl;
            if(u<0)continue;
            //for(int i=0;i<sz;i++)cerr<<tarz[i]<<' ';
            //for(int i=0;i<es[ip];i++)cerr<<et[ip][i]<<' ';
            //cerr<<u<<' '<<val<<endl;
            //assert(u<val);
            int id=++zc;
            z[id].ei=i;z[id].ej=j;
            z[id].typ=-1;
            pq.emplace(u,id);
            ht::add(hsh);
        }
    }
    return 0;
}
