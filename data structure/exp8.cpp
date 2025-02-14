#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXVERTEX 100
#define MAXEDGE 20000

//锟斤拷锟斤拷峁癸拷锟?
typedef struct Vertex {
	int id;//锟斤拷锟斤拷锟斤拷
	int w;//锟斤拷锟斤拷权值
	int degree;//锟斤拷锟斤拷亩锟?
	long edges[MAXVERTEX];//锟竭的憋拷锟?
};

//锟竭结构锟斤拷
typedef struct Edge {
	long id;//锟竭的憋拷锟?
	int h;//锟斤拷头锟斤拷锟斤拷锟斤拷
	int t;//锟斤拷尾锟斤拷锟斤拷锟斤拷
	int w;//权值
};

//图锟结构锟斤拷
typedef struct Graph {
	Vertex v[MAXVERTEX];//锟斤拷锟斤拷锟斤拷锟斤拷
	Edge e[MAXEDGE];//锟斤拷锟斤拷锟斤拷
	bool dirctional;//t:锟斤拷锟斤拷图锟斤拷f:锟斤拷锟斤拷图
	bool weighted;//t:锟斤拷权图锟斤拷f:锟斤拷权图
	unsigned nv;//锟斤拷锟斤拷锟斤拷
	unsigned ne;//锟斤拷锟斤拷
};

//锟斤拷锟斤拷一锟斤拷锟斤拷锟酵硷拷锟斤拷锟斤拷锟絥锟斤拷锟斤拷锟姐，每锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷叩母锟斤拷锟轿猵
int randgengraph(int n, float p, bool directional, bool weighted, const char* filename, int seed) {
	srand(seed);
	char* content = (char*)malloc(5000000);
	if (!content) {
		printf("锟斤拷锟斤拷娲拷占锟绞э拷埽锟絓n");
		exit(0);
	}
	FILE* fp = fopen(filename, "wb");
	if (!fp) {
		printf("锟斤拷锟斤拷图锟侥硷拷%s时失锟杰ｏ拷\n",filename);
		exit(0);
	}
	long offset = 0;//content锟斤拷前锟斤拷写锟斤拷位锟斤拷
	int ne = 0;//锟斤拷锟缴憋拷锟斤拷
	for (int i = 0; i < n; i++)
		offset += sprintf(content + offset, "%3d %5d\n", i, rand() % 100);//写锟诫顶锟斤拷谋锟脚和讹拷锟斤拷锟斤拷锟饺ㄖ?
	int pn = (int)(10000 * p);
	if (directional) {//锟斤拷锟斤拷图
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if (i != j && rand() % 10000 < pn) {
					offset += sprintf(content + offset, "%3d %3d %4d\n", i, j, weighted ? rand() % 100 : 1);
					ne++;
				}
	}
	else {//锟斤拷锟斤拷图
		for(int i = 0; i < n; i++)
			for(int j = i; j < n; j++)
				if (i != j && rand() % 10000 < pn) {
					offset += sprintf(content + offset, "%3d %3d %4d\n", i, j, weighted ? rand() % 100 : 1);
					ne++;
				}
	}
	char ch[40];
	int sz = sprintf(ch, "%d %7d %5s %5s\n", n, ne, weighted ? "true" : "flase", directional ? "true" : "flase");
	fwrite(&ch, sz, 1, fp);//写锟斤拷图锟侥讹拷锟斤拷锟斤拷锟酵憋拷锟斤拷
	fwrite(content, offset, 1, fp);//写锟斤拷图锟侥讹拷锟斤拷捅叩锟斤拷锟较?
	fclose(fp);
	free(content);
}

//锟斤拷锟侥硷拷锟叫讹拷锟斤拷图锟斤拷锟斤拷锟节达拷锟斤拷锟斤拷锟斤拷图锟侥憋拷示
void initgraph(Graph* g, const char* gfile) {
	FILE* fp = fopen(gfile, "r");
	if (!fp) {
		printf("锟斤拷取图锟斤拷锟斤拷锟侥硷拷锟斤拷锟斤拷锟斤拷\n");
		exit(0);
	}
	char bv[10];
	//锟斤拷取图锟侥伙拷锟斤拷锟斤拷息
	fscanf(fp, "%u%u%s", &(g->nv), &(g->ne), bv);
	//printf("%d %d %s", g->ne, g->nv, bv);
	g->weighted = strcmp(bv, "true") == 0 ? true : false;
	fscanf(fp, "%s", bv);
	g->dirctional = strcmp(bv, "true") == 0 ? true : false;
	//锟斤拷取锟斤拷锟斤拷锟斤拷息
	for (int i = 0; i < g->nv; i++) {
		fscanf(fp, "%d%d", &(g->v[i].id), &(g->v[i].w));
		g->v[i].degree = 0;
		//printf("锟斤拷锟斤拷%d-权%d\n", g->v[i].id, g->v[i].w);
	}
	//锟斤拷取锟斤拷锟斤拷息
	for (unsigned long i = 0; i < g->ne; i++) {
		fscanf(fp, "%u%u%d", &(g->e[i].h), &(g->e[i].t), &(g->e[i].w));
		//printf("锟斤拷:%u-%u=>%d\n", g->e[i].h, g->e[i].t, g->e[i].w);
		g->e[i].id = i;
		unsigned h, t;
		h = g->e[i].h;
		t = g->e[i].t;
		g->v[h].edges[g->v[h].degree++] = i;
		if(g->dirctional==false)
			g->v[t].edges[g->v[t].degree++] = i;
	}
	fclose(fp);
}

inline long getEdgeIdx(Graph* g, long id);

//锟斤拷印锟节接憋拷锟斤拷锟斤拷息
void printgraph(Graph* g) {
	printf("图锟侥伙拷锟斤拷锟斤拷息:锟斤拷锟斤拷锟斤拷(%u)-锟斤拷锟斤拷(%lu)-%s-%s\n", g->nv, g->ne, g->weighted ? "锟斤拷权图" : "锟斤拷权图", g->dirctional ? "锟斤拷锟斤拷图" : "锟斤拷锟斤拷图");
	for (int i = 0; i < g->nv; i++) {
		printf("ID(%u)-锟斤拷(%d)-权(%d)-锟竭憋拷 t(eid|w):%u", g->v[i].id, g->v[i].degree, g->v[i].w, g->v[i].id);
		for (int j = 0; j < g->v[i].degree; j++) {
			unsigned long E = g->v[i].edges[j];
			unsigned long e = getEdgeIdx(g, E);
			if (g->v[i].id == g->e[e].h)
				printf("->%u(%d, %d)", g->e[e].t, g->e[e].id, g->e[e].w);
			else 
				printf("->%u(%d, %d)", g->e[e].h, g->e[e].id, g->e[e].w);
		}
		printf("\n");
	}
}

//锟斤拷锟揭革拷锟斤拷锟斤拷诺亩锟斤拷悖拷锟斤拷锟斤拷涠ワ拷锟斤拷锟斤拷锟斤拷卤锟?
inline int getVexIdx(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return i;
	printf("input wrong vertex id in getVexIdx()!\n");
	system("pause");
	exit(0);
}

//锟斤拷锟揭革拷锟斤拷锟斤拷诺亩锟斤拷悖拷锟斤拷锟斤拷锟饺ㄖ?
inline int getVexW(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].w;
	printf("input wrong vertex id in getVexW()!\n");
	system("pause");
	exit(0);
}

//锟斤拷锟揭革拷锟斤拷锟斤拷诺亩锟斤拷悖拷锟斤拷锟斤拷锟斤拷
inline int getVexDegree(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].degree;
	printf("input wrong vertex id in getVexDegree()!\n");
	system("pause");
	exit(0);
}

//锟斤拷锟揭革拷锟斤拷锟斤拷诺亩锟斤拷锟?,锟斤拷锟斤拷锟斤拷锟斤拷锟叫憋拷
inline long* getEdgesByNode(Graph* g, int id, int* ne) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id) {
			*ne = g->v[i].degree;
			return g->v[i].edges;
		}
	printf("input wrong vertex id in getEdgesByNode()!\n");
	system("pause");
	exit(0);
}

//锟斤拷锟揭革拷锟斤拷锟斤拷诺谋撸锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟铰憋拷
inline long getEdgeIdx(Graph* g, long id) {
	for (long i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return i;
	printf("input wrong edge id in getEdgeIdx()!\n");
	system("pause");
	exit(0);
}

//锟斤拷锟揭革拷锟斤拷锟斤拷诺谋撸锟斤拷锟斤拷锟斤拷锟饺ㄖ?
inline int getEdgeW(Graph* g, long id) {
	for (long i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return g->e[i].w;
	printf("input wrong edge id in getEdgeW()!\n");
	system("pause");
	exit(0);
}

//锟斤拷锟揭革拷锟斤拷锟斤拷诺谋撸锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?
inline void getVexByEdge(Graph* g, long id, int* h, int* t) {
	long i;
	for (i = 0; i < g->ne; i++)
		if (g->e[i].id == id) {
			*h = g->e[i].h;
			*t = g->e[i].t;
			return;
		}	
	printf("input wrong edge id %d in getVexByEdge()!\n",id);
	system("pause");
	exit(0);
}

//通锟斤拷权值锟斤拷锟揭讹拷锟斤拷锟斤拷
inline int locateVex(Graph* g, int w) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].w == w)
			return g->v[i].id;
	return -1;
}

//通锟斤拷权值锟斤拷锟揭边憋拷锟?
inline int locateEdge(Graph* g, int w) {
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].w == w)
			return g->e[i].id;
	return -1;
}

//锟斤拷锟矫讹拷锟斤拷权值
inline void setVexW(Graph* g, int id, int w) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id) {
			g->v[i].w = w;
			return;
		}		
	printf("input wrong vertex id in setVexW()!\n");
	exit(0);
}

//锟斤拷锟矫憋拷权值
inline void setEdgeW(Graph* g, int id, int w) {
	for (long i = 0; i < g->ne; i++)
		if (g->e[i].id == id) {
			g->e[i].w = w; 
			return;
		}	
	printf("input wrong edge id in setEdgeW()!\n");
	exit(0);
}

//删锟斤拷锟斤拷
void deleteEdge(Graph* g, long id) {
	int i,j,h,t;
	getVexByEdge(g,id,&h,&t);
	//printf("h=%d,t=%d\n",h,t);
	for(i=0;i<g->v[t].degree;i++){
		if(g->v[t].edges[i]==id)
			break;
	}
	for(j=i+1;j<g->v[t].degree;j++){
		g->v[t].edges[j-1]=g->v[t].edges[j];
	}
	g->v[t].degree--;
	if(g->dirctional==false){
		for(i=0;i<g->v[h].degree;i++){
			if(g->v[h].edges[i]==id)
				break;
		}
		for(j=i+1;j<g->v[h].degree;j++){
			g->v[h].edges[j-1]=g->v[h].edges[j];
		}
		g->v[h].degree--;
	}
	i=getEdgeIdx(g,id);
	for(j=i+1;j<g->ne;j++){
		g->e[j-1]=g->e[j];
	}
	g->ne--;
}


//删锟斤拷锟斤拷锟斤拷
void deleteVex(Graph* g, int id) {
	int i,j,h,t;
	i=getVexIdx(g,id);
	for(j=g->v[i].degree-1;j>=0;j--){
		deleteEdge(g,g->v[i].edges[j]);
	}
	if(g->dirctional==true){
		for(j=g->ne-1;j>=0;j--){
			getVexByEdge(g,g->e[j].id,&h,&t);
			if(h==id)
				deleteEdge(g,g->e[j].id);
		}
	}
	for(j=i+1;j<g->nv;j++){
		g->v[j-1]=g->v[j];
	}
	g->nv--;
}


//锟斤拷锟接讹拷锟斤拷
void addVex(Graph* g, int w) {
	g->v[g->nv].degree=0;
	g->v[g->nv].w=w;
	g->v[g->nv].id=g->v[g->nv-1].id+1;
	g->nv++;
}

//锟斤拷锟接憋拷
void addEdge(Graph* g, int w, int h, int t) {
	g->e[g->ne].id=g->e[g->ne-1].id+1;
	g->e[g->ne].w=w;
	g->e[g->ne].h=h;
	g->e[g->ne].t=t;
	g->v[t].edges[g->v[t].degree++]=g->e[g->ne].id;
	if(g->dirctional==false){
		g->v[h].edges[g->v[h].degree++]=g->e[g->ne].id;
	}
	g->ne++;
}

int judge(Graph* g,int id1,int id2){		//id1能否到id2
	int s[MAXVERTEX],visited[MAXVERTEX];
	int i,j,h,t,count=0,temp;
	for(i=0;i<MAXVERTEX;i++){
		visited[i]=0;
	}
	for(i=0;i<g->v[id2].degree;i++){
		getVexByEdge(g,g->v[id2].edges[i],&h,&t);
		s[count++]=h;
		printf("h=%d\n",h);
		visited[h]=1;
	}
	printf("\n");
	while(count>0){
		temp=s[--count];
		printf("temp=%d\n",temp);
		if(temp==id1){
			return 1;
		}
		for(i=0;i<g->v[temp].degree;i++){
			getVexByEdge(g,g->v[temp].edges[i],&h,&t);
			if(!visited[h]){
				s[count++]=h;
				printf("h=%d\n",h);
				visited[h]=1;
			}
		}
	}
	return 0;
}

void dfs(Graph *g,int id){
	int s[MAXVERTEX],visited[MAXVERTEX];
	int i,h,t,count=0,temp;
	printf("dfs result:\n");
	printf("id=%d,w=%d\n",id,g->v[id].w);
	for(i=0;i<MAXVERTEX;i++){
		visited[i]=0;
	}
	visited[id]=1;
	for(i=0;i<g->v[id].degree;i++){
		getVexByEdge(g,g->v[id].edges[i],&h,&t);
		if(t==id){
			t=h;
		}
		s[count++]=t;
		//printf("h=%d\n",h);
	}
	while(count>0){
		temp=s[--count];
		if(!visited[temp]){
			printf("id=%d,w=%d\n",temp,g->v[getVexIdx(g,temp)].w);
			visited[temp]=1;
			for(i=0;i<g->v[getVexIdx(g,temp)].degree;i++){
				getVexByEdge(g,g->v[getVexIdx(g,temp)].edges[i],&h,&t);
				if(t==temp){
					t=h;
				}
				if(!visited[t]){
					s[count++]=t;
					//printf("t=%d\n",t);
				}
			}
		}
	}
}

void bfs(Graph *g,int id){
	int s[MAXVERTEX],visited[MAXVERTEX];
	int i,h,t,count=0,temp;
	printf("bfs result:\n");
	printf("id=%d,w=%d\n",id,g->v[id].w);
	for(i=0;i<MAXVERTEX;i++){
		visited[i]=0;
	}
	visited[id]=1;
	for(i=0;i<g->v[id].degree;i++){
		getVexByEdge(g,g->v[id].edges[i],&h,&t);
		if(t==id){
			t=h;
		}
		s[count++]=t;
		//printf("t=%d\n",t);
		visited[t]=1;
	}
	while(count>0){
		temp=s[0];
		for(i=1;i<count;i++){
			s[i-1]=s[i];
		}
		count--;
		printf("id=%d,w=%d\n",temp,g->v[temp].w);
		for(i=0;i<g->v[temp].degree;i++){
			getVexByEdge(g,g->v[temp].edges[i],&h,&t);
			if(t==temp){
				t=h;
			}
			if(!visited[t]){
				s[count++]=t;
				//printf("h=%d\n",h);
				visited[t]=1;
			}
		}
	}
}

int component(Graph *g){
	int s[MAXVERTEX],visited[MAXVERTEX];
	int i,j,h,t,count=0,temp,num=0;
	for(i=0;i<MAXVERTEX;i++){
		visited[i]=0;
	}
	for(i=0;i<g->nv;i++){
		if(!visited[g->v[i].id]){
			for(j=0;j<g->v[i].degree;j++){
				getVexByEdge(g,g->v[i].edges[j],&h,&t);
				if(t==i){
					t=h;
				}
				s[count++]=t;
				//printf("h=%d\n",h);
				visited[t]=1;
			}
			while(count>0){
				temp=s[--count];
				for(j=0;j<g->v[temp].degree;j++){
					getVexByEdge(g,g->v[temp].edges[j],&h,&t);
					if(t==temp){
						t=h;
					}
					if(!visited[t]){
						s[count++]=t;
						//printf("h=%d\n",h);
						visited[t]=1;
					}
				}
			}
			num++;
		}
	}
	return num;
}

void dijkstra(Graph *g,int idx){
	int i,j,k,min,temp,h,t,id;
	int path[MAXVERTEX],d[MAXVERTEX],flag[MAXVERTEX];
	id=getVexIdx(g,idx);
	for(i=0;i<g->nv;i++){
		flag[i]=0;
		path[i]=-1;
		d[i]=999999;
	}
	flag[id]=1;
	d[id]=0;
	for(i=0;i<g->v[id].degree;i++){
		getVexByEdge(g,g->v[id].edges[i],&h,&t);
		if(t==id){
			t=h;
		}
		d[t]=g->e[g->v[id].edges[i]].w;
	}
	for(i=0;i<g->nv;i++){
		min=999999;
		for(j=0;j<g->nv;j++){
			if(flag[j]==0&&d[j]<min){
				min=d[j];
				k=j;
			}
		}
		flag[k]=1;
		for(j=0;j<g->v[k].degree;j++){
			getVexByEdge(g,g->v[k].edges[j],&h,&t);
			if(t==g->v[k].id){
				t=h;
			}
			temp=min+g->e[g->v[k].edges[j]].w;
			if(flag[t]==0&&temp<d[t]){
				d[t]=temp;
				path[t]=k;
			}
		}
	}
	for(i=0;i<g->nv;i++){
		if(d[i]!=999999){
			printf("%d->%d:%d,path:",idx,g->v[i].id,d[i]);
			temp=i;
			printf("%d",g->v[i]);
			while(path[temp]!=-1){
				printf("%d",g->v[path[temp]].id);
				temp=path[temp];
			}
			printf("%d",idx);
			printf("\n");
		}
	}
}

int main() {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	if (!g) {
		printf("error\n");
		exit(0);
	}	
	randgengraph(10, 0.3, 0, 1, "graph.txt", 1);
	initgraph(g, "graph.txt");
	printgraph(g);
	
	int* h;
	h = (int*)malloc(sizeof(int)); 
	int* t;
	t = (int*)malloc(sizeof(int)); 
	//addVex(g, 30);
	//addEdge(g, 50, 1, 3);
	//getVexByEdge(g, 10, h, t);
	//printf("%d %d\n", *h, *t);
	//deleteEdge(g, 10);
	//deleteVex(g, 5);
	//printf("deletevex success\n");
    //printgraph(g);
	//printf("%d",judge(g,5,6));        
	bfs(g,1);
	dfs(g,1);
	printf("there are %d components\n",component(g));
	dijkstra(g,5);
    system("pause");
} 
