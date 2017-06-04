#include <stdio.h> 
#include <stdlib.h>
#define M 20
#define MAX 20 
typedef struct { int begin; int end; int weight; }edge;
typedef struct { int adj; int weight; }AdjMatrix[MAX][MAX];
typedef struct { AdjMatrix arc; int vexnum, arcnum; }MGraph;
void CreatGraph(MGraph*); 
void sort(edge*,MGraph*); 
void MiniSpanTree(MGraph*); 
int Find(int*, int); 
void Swapn(edge *,int,int);
void CreatGraph(MGraph *G){ 
	int i,j,n,m; printf("input points' count and edges' count:"); 
	scanf("%d%d",&G->vexnum,&G->arcnum); 
	for(i=1;i<= G->vexnum;i++){ 
		for(j=1;j<= G->vexnum;j++) { 
			G->arc[i][j].adj=G->arc[j][i].adj=0;
 		} 
 	} 
 	printf("input pointA pointB and weight(pointA pointB weight):\n"); 
 	for(i=1;i<= G->arcnum;i++){ 
	 	scanf("%d%d",&n,&m); G->arc[n][m].adj=G->arc[m][n].adj=1;
	 	scanf("%d",&G->arc[n][m].weight); 
 	} 
 	printf("the matrix is:\n"); 
 	for(i=1;i<= G->vexnum;i++) { 
 		for(j=1;j<= G->vexnum;j++) {
 	 		if(G->arc[i][j].adj==1) {
 	 			printf(" %d\t",G->arc[i][j].weight); 
 	 		}else {
 	 			printf(" %d\t",G->arc[i][j].adj);
 	 		} 
 	 		G->arc[j][i].weight=G->arc[i][j].weight; 
 		} 
 		printf("\n");
 	} 
 }


void sort(edge edges[],MGraph*G){ 
	int i,j;
	for(i=1;i< G->arcnum;i++) { 
		for(j=i + 1;j<=G->arcnum;j++) { 
			if(edges[i].weight>edges[j].weight) { 
				Swapn(edges,i,j); 
			} 
		} 
	}
	printf("after sort (num edge weight):\n"); 
	for(i=1;i<= G->arcnum;i++) { 
		printf("%2d. <%d--%d> %d\n",i,edges[i].begin,edges[i].end,edges[i].weight); 
	}
}

void Swapn(edge *edges,int i,int j) { 
	int temp; 
	temp=edges[i].begin; 
	edges[i].begin=edges[j].begin; 
	edges[j].begin=temp; 
	temp=edges[i].end;
	edges[i].end=edges[j].end; 
	edges[j].end=temp; 
	temp=edges[i].weight; 
	edges[i].weight= edges[j].weight; 
	edges[j].weight= temp; 
}
void MiniSpanTree(MGraph*G){ 
	int i,j,n,m,Mincost=0; 
	int k=1; 
	int parent[M]; 
	edge edges[M]; 
	for(i=1;i< G->vexnum;i++) { 
		for(j=i+ 1;j<=G->vexnum;j++) { 
			if(G->arc[i][j].adj==1) { 
				edges[k].begin=i;
				edges[k].end=j; 
				edges[k].weight=G->arc[i][j].weight;
				k++;
			}
		}
	} 
	sort(edges,G); 
	for(i=1;i<= G->arcnum;i++) { 
		parent[i]=0; 
	} 
	printf("the min span tree is:\n"); 
	for(i=1;i<= G->arcnum;i++){ 
		n= Find(parent,edges[i].begin); 
		m=Find(parent,edges[i].end); 
		if(n!=m) { 
			parent[n]=m;
			printf("<%d--%d> %d\n", edges[i].begin,edges[i].end,edges[i].weight); Mincost+=edges[i].weight; } 
		} 
		printf("the min  span tree's weight sum: Mincost=%d\n",Mincost);
}

int Find(int *parent,int f) { 
	while(parent[f]>0) { 
		f=parent[f]; 
	} 
	return f; 
}
void main(){ 
	MGraph *G; 
	G=(MGraph*)malloc(sizeof(MGraph)); 
	CreatGraph(G); 
	MiniSpanTree(G); 
}


/*
test input:

6 10

1 2 6
1 3 1
1 4 5
2 3 5
2 5 3
3 4 5
3 6 4
4 6 2
5 6 6
3 5 6

 */
