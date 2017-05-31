#include <iostream>
#include<stdio.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
最小生成树Prime算法
2014-12-25 23:12 
Prim算法基本思想: 
1、从图N = { V, E }中选择某一顶点u0 进行标记，之
后选择与它关联的具有最小权值的边(u0, v)，并将顶
点v 进行标记
2、反复在一个顶点被标记，而另一个顶点未被标记的各
条边中选择权值最小的边(u, v),并将未标记的顶点进
行标记
3、如此继续下去，直到图中的所有顶点都被标记为止
*/

//宏定义无穷大 
#define Infinity 10000
//宏定义最大定点数 
#define MaxVertexs 20

typedef struct mgraph{
 	   int arc[MaxVertexs][MaxVertexs];//领结矩阵 
 	   int numVertexs;//定点数 
	   int numEdges;//边数 
}MGraph;


void CreateGraph(MGraph* G){
	
 	 int i=0,j=0;
 	 G->numVertexs=9;
 	 G->numEdges=15;
	
	
	 for(i=0;i<G->numVertexs;i++){
		 
	 	for(j=0;j<G->numVertexs;j++){
			
			if(i==j){
				G->arc[i][j]=0;
			}
			else{
				G->arc[i][j]=Infinity;
			}
		 		
		}							  							 
	 }
	//输入领结矩阵下三角形的值 
	    G->arc[0][1]=6;
	    G->arc[0][2]=1; 
	    G->arc[0][3]=5; 
	    G->arc[1][2]=5; 
	    G->arc[1][4]=3; 
	    G->arc[2][3]=5; 
	    G->arc[2][4]=6; 
	    G->arc[2][5]=4; 
	    G->arc[3][5]=2;
	    G->arc[4][5]=6;
	
	//通过下三角形矩阵确定上三角形矩阵
	for(i=0;i<G->numVertexs;i++){
		
		for(j=i;j<G->numVertexs;j++)
			G->arc[j][i]=G->arc[i][j];	
	}
		 
}
//以领结矩阵的方式输出图 
void MGraphPrint(MGraph G){
	
	for(int i=0;i<G.numVertexs;i++)	{
		
		for(int j=0;j<G.numVertexs;j++){
			printf("%7d,",G.arc[i][j]);
		}
			
		printf("\n");	
	}	
} 

//最小生成树Prim算法 
/*
G---以领结矩阵存储的连通图，sv---产生最小生成树的起始点 
*/ 
void MiniSpanTree_Prim(MGraph *G,int sv){
	
	int i=0,j=0;
	
	
	int Cost[MaxVertexs];//cost数组用于存放已加入最小生成树的顶点集和与其相邻且尚未加入最小生成树顶点所形成边的权值
	int Point[MaxVertexs];//存放已经加入最小生成树顶点下标
	int Mark[MaxVertexs];//顶点标记状态，0---未被标记过的顶点，1---标记过的顶点 
	
	 
	if((sv>-1)&&(sv<G->numVertexs)){//产生最小生成树起始点的合法性检测 
		
		for(i=0;i<G->numVertexs;i++){//初始化数组 			
			Cost[i]=G->arc[sv][i];
			Point[i]=sv;
			Mark[i]=0;	
		}
		
		Mark[sv]=1;//从顶点sv开始产生最小生成树，故最开始默认顶点sv已加入到最小生成树
		
		//产生最小生成树 
		for(i=0;i<G->numVertexs;i++){
			
			int min=Infinity;
			int index;//存放边权值最小顶点下标 
			
			//查找已加入到最小生成树中顶点与相邻未加入到生成树的顶点之间所形成权值 
			for(j=0;j<G->numVertexs;j++){
				
				if((!Mark[j])&&(Cost[j]<min)){
					
					min=Cost[j];
					index=j;	
				}
			}
			
			if(index>-1){
				
				Mark[index]=1;//将查找的顶点进行标记
				printf("[%d,%d]=%d\n",Point[index]+1,index+1,Cost[index]);//下标+1，矩阵下标从零开始，图的遍历从第1个点开始，所以下标+1			
			}
			/*将刚刚查找到的顶点与先前已加入到最小生成树的顶点看成一个整体，或者说看成一个集合，重新确定这个集合中的顶点与相邻未在集合中顶点所形成边的最小权值*/
			for(j=0;j<G->numVertexs;j++){
				
				if((!Mark[j])&&(G->arc[index][j]<Cost[j])){
					
					Cost[j]=G->arc[index][j];
					Point[j]=index;//确定顶点未在集合中顶点j在最小生成树顶点集中对应的顶点 
				}	
			}				
		}		
	}	
}

int main(int argc, char *argv[]) 
{
	MGraph G;
	CreateGraph(&G);

	MGraphPrint(G);
	
	printf("最小生成树为:\n");
	MiniSpanTree_Prim(&G,1);
	return 0;
}
