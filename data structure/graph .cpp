#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXVERTEX 100
#define MAXEDGE 20000

//����ṹ��
typedef struct Vertex {
	int id;//������
	int w;//����Ȩֵ
	int degree;//����Ķ�
	long edges[MAXVERTEX];//�ߵı��
};

//�߽ṹ��
typedef struct Edge {
	long id;//�ߵı��
	int h;//��ͷ������
	int t;//��β������
	int w;//Ȩֵ
};

//ͼ�ṹ��
typedef struct Graph {
	Vertex v[MAXVERTEX];//��������
	Edge e[MAXEDGE];//������
	bool dirctional;//t:����ͼ��f:����ͼ
	bool weighted;//t:��Ȩͼ��f:��Ȩͼ
	unsigned nv;//������
	unsigned ne;//����
};

//����һ�����ͼ������n�����㣬ÿ������������������ߵĸ���Ϊp
int randgengraph(int n, float p, bool directional, bool weighted, const char* filename, int seed) {
	srand(seed);
	char* content = (char*)malloc(5000000);
	if (!content) {
		printf("����洢�ռ�ʧ�ܣ�\n");
		exit(0);
	}
	FILE* fp = fopen(filename, "wb");
	if (!fp) {
		printf("����ͼ�ļ�%sʱʧ�ܣ�\n",filename);
		exit(0);
	}
	long offset = 0;//content��ǰ��д��λ��
	int ne = 0;//���ɱ���
	for (int i = 0; i < n; i++)
		offset += sprintf(content + offset, "%3d %5d\n", i, rand() % 100);//д�붥��ı�źͶ������Ȩֵ
	int pn = (int)(10000 * p);
	if (directional) {//����ͼ
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if (i != j && rand() % 10000 < pn) {
					offset += sprintf(content + offset, "%3d %3d %4d\n", i, j, weighted ? rand() % 100 : 1);
					ne++;
				}
	}
	else {//����ͼ
		for(int i = 0; i < n; i++)
			for(int j = i; j < n; j++)
				if (i != j && rand() % 10000 < pn) {
					offset += sprintf(content + offset, "%3d %3d %4d\n", i, j, weighted ? rand() % 100 : 1);
					ne++;
				}
	}
	char ch[40];
	int sz = sprintf(ch, "%d %7d %5s %5s\n", n, ne, weighted ? "true" : "flase", directional ? "true" : "flase");
	fwrite(&ch, sz, 1, fp);//д��ͼ�Ķ������ͱ���
	fwrite(content, offset, 1, fp);//д��ͼ�Ķ���ͱߵ���Ϣ
	fclose(fp);
	free(content);
}

//���ļ��ж���ͼ�����ڴ�������ͼ�ı�ʾ
void initgraph(Graph* g, const char* gfile) {
	FILE* fp = fopen(gfile, "r");
	if (!fp) {
		printf("��ȡͼ�����ļ�����\n");
		exit(0);
	}
	char bv[10];
	//��ȡͼ�Ļ�����Ϣ
	fscanf(fp, "%u%u%s", &(g->nv), &(g->ne), bv);
	//printf("%d %d %s", g->ne, g->nv, bv);
	g->weighted = strcmp(bv, "true") == 0 ? true : false;
	fscanf(fp, "%s", bv);
	g->dirctional = strcmp(bv, "true") == 0 ? true : false;
	//��ȡ������Ϣ
	for (int i = 0; i < g->nv; i++) {
		fscanf(fp, "%d%d", &(g->v[i].id), &(g->v[i].w));
		g->v[i].degree = 0;
		//printf("����%d-Ȩ%d\n", g->v[i].id, g->v[i].w);
	}
	//��ȡ����Ϣ
	for (unsigned long i = 0; i < g->ne; i++) {
		fscanf(fp, "%u%u%d", &(g->e[i].h), &(g->e[i].t), &(g->e[i].w));
		//printf("��:%u-%u=>%d\n", g->e[i].h, g->e[i].t, g->e[i].w);
		g->e[i].id = i;
		unsigned h, t;
		h = g->e[i].h;
		t = g->e[i].t;
		g->v[t].edges[g->v[t].degree++] = i;
		if(g->dirctional==false)
			g->v[h].edges[g->v[h].degree++] = i;
	}
	fclose(fp);
}

inline long getEdgeIdx(Graph* g, long id);

//��ӡ�ڽӱ����Ϣ
void printgraph(Graph* g) {
	printf("ͼ�Ļ�����Ϣ:������(%u)-����(%lu)-%s-%s\n", g->nv, g->ne, g->weighted ? "��Ȩͼ" : "��Ȩͼ", g->dirctional ? "����ͼ" : "����ͼ");
	for (int i = 0; i < g->nv; i++) {
		printf("ID(%u)-��(%d)-Ȩ(%d)-�߱� t(eid|w):%u", g->v[i].id, g->v[i].degree, g->v[i].w, g->v[i].id);
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

//���Ҹ�����ŵĶ��㣬�����䶥�������±�
inline int getVexIdx(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return i;
	printf("input wrong vertex id in getVexIdx()!\n");
	system("pause");
	exit(0);
}

//���Ҹ�����ŵĶ��㣬������Ȩֵ
inline int getVexW(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].w;
	printf("input wrong vertex id in getVexW()!\n");
	system("pause");
	exit(0);
}

//���Ҹ�����ŵĶ��㣬�������
inline int getVexDegree(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].degree;
	printf("input wrong vertex id in getVexDegree()!\n");
	system("pause");
	exit(0);
}

//���Ҹ�����ŵĶ���,���������б�
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

//���Ҹ�����ŵıߣ�������������±�
inline long getEdgeIdx(Graph* g, long id) {
	for (long i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return i;
	printf("input wrong edge id in getEdgeIdx()!\n");
	system("pause");
	exit(0);
}

//���Ҹ�����ŵıߣ�������Ȩֵ
inline int getEdgeW(Graph* g, long id) {
	for (long i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return g->e[i].w;
	printf("input wrong edge id in getEdgeW()!\n");
	system("pause");
	exit(0);
}

//���Ҹ�����ŵıߣ���������������
inline void getVexByEdge(Graph* g, long id, int* h, int* t) {
	long i;
	for (i = 0; i < g->ne; i++)
		if (g->e[i].id == id) {
			*h = g->e[i].h;
			*t = g->e[i].t;
			return;
		}	
	printf("input wrong edge id in getVexByEdge()!\n");
	system("pause");
	exit(0);
}

//ͨ��Ȩֵ���Ҷ�����
inline int locateVex(Graph* g, int w) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].w == w)
			return g->v[i].id;
	return -1;
}

//ͨ��Ȩֵ���ұ߱��
inline int locateEdge(Graph* g, int w) {
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].w == w)
			return g->e[i].id;
	return -1;
}

//���ö���Ȩֵ
inline void setVexW(Graph* g, int id, int w) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id) {
			g->v[i].w = w;
			return;
		}		
	printf("input wrong vertex id in setVexW()!\n");
	system("pause");
	exit(0);
}

//���ñ�Ȩֵ
inline void setEdgeW(Graph* g, int id, int w) {
	for (long i = 0; i < g->ne; i++)
		if (g->e[i].id == id) {
			g->e[i].w = w; 
			return;
		}	
	printf("input wrong edge id in setEdgeW()!\n");
	system("pause");
	exit(0);
}

//ɾ����
void deleteEdge(Graph* g, long id) {
	int i,j,h,t;
	getVexByEdge(g,id,&h,&t);
	printf("h=%d,t=%d\n",h,t);
	for(i=0;i<g->v[h].degree;i++){
		if(g->v[h].edges[i]==id)
			break;
	}
	for(j=i+1;j<g->v[h].degree;j++){
		g->v[h].edges[j-1]=g->v[h].edges[j];
	}
	g->v[h].degree--;
	if(g->dirctional==false){
		for(i=0;i<g->v[t].degree;i++){
			if(g->v[t].edges[i]==id)
				break;
		}
		for(j=i+1;j<g->v[t].degree;j++){
			g->v[t].edges[j-1]=g->v[t].edges[j];
		}
		g->v[t].degree--;
	}
	i=getEdgeIdx(g,id);
	for(j=i+1;j<g->ne;j++){
		g->e[j-1]=g->e[j];
	}
	g->ne--;
}


//ɾ������
void deleteVex(Graph* g, int id) {
	
}


//���Ӷ���
void addVex(Graph* g, int w) {
	
}

//���ӱ�
void addEdge(Graph* g, int w, int h, int t) {
	
}

int main() {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	if (!g) {
		printf("error\n");
		exit(0);
	}	
	randgengraph(10, 0.5, 1, 1, "graph.txt", 1);
	initgraph(g, "graph.txt");
	printgraph(g);
	
	int* h;
	h = (int*)malloc(sizeof(int)); 
	int* t;
	t = (int*)malloc(sizeof(int)); 
	//addVex(g, 30)��
	//addEdge(g, 50, 1, 3)��
	getVexByEdge(g, 10, h, t);
	printf("%d %d\n", *h, *t);
	deleteEdge(g, 10);
	printf("delete success\n");
	//deleteVex(g, 5);
	printgraph(g);
	system("pause");
} 
