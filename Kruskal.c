
/******************************************************************************

    Kruskal Algorithm
    1.Graph represented in Adjacency Matrix
    2. Struct edge to store data about edges
    3.BubleSort is used to sort the edges
    4.Union-find Algorithm is used to find find cycles

*******************************************************************************/

#include <stdio.h>
#define max 11

struct edge
{
    int src;
    int dest;
    int weight;
};

int menu(void);

int adjacencymatrix(struct edge farr[max],int adjmat[max][max],int vertex,int edge);
void addEdge(int adjmat[max][max], int src, int dest, int weight);
void bubblesort(struct edge arr[max],int fn);

//create and display mst
int createMST(struct edge arr[max],int adjmat[max][max],int vertex,int edge,struct edge mst[max]);
void displayMST(struct edge mst[max],int mstEdges,int cost);

//union find algo
int find(int unionset[max],int source,int destin);
void mergeSet(int unionset[max],int source,int destin,int edge);

//display adj matrix and edgeset
void display(int farr[max][max],int fn);
void displayedges(struct edge arr[max],int vertex);

int main(void)
{
    int choice = 0;     //initialising all the variables
    int flag = 0;
    int vertex = 0;
    int edge = 0;
    int mste = 0;
    int cost = 0;
    int i = 0;
    int j = 0;
    int adjmat[max][max];
    struct edge arr[max];
    struct edge mst[max];
    
    for(i = 0; i <= max ;i++)
    {
        for(j = 0; j <= max; j++)
        {
            adjmat[i][j] = 0;  //initialising to zero to avoid garbage value
        }
    }
    
    
    while(flag == 0)
    {
        choice = menu();
        switch(choice)
        {
            case 0:
              printf("\n\tEnd");
              flag = 1;
            break;
            
            case 1: //creating adj matrix
            
              printf("\n\tEnter number of vertices");
              scanf("%d",&vertex);
              
              if(vertex > max || vertex < 1)
              {
                  printf("\n\tExceeding the max limit available");
                  
                  
              }
              else
              {
                  mste = vertex - 1;
                  printf("\n\tMSTE: %d",mste);
                  printf("\n\tEnter the number of edges");
                  scanf("%d",&edge);
                  
                  adjacencymatrix(arr,adjmat,vertex,edge);  //creating adj matrix and edge set
                  
              }
            break;
            
            case 2:  //displaying adj matrix
            
               display(adjmat,vertex);  //display matrix 
               
            break;
            
            case 3:  //printing sorted edgeset
              bubblesort(arr,vertex);  //sorting the edge set
              displayedges(arr,vertex);
              
            break;
            
            case 4:  //creating and printing MST
              bubblesort(arr,vertex);  //sorting the edge set
              
              cost = createMST(arr,adjmat,vertex,edge,mst);
              
              displayMST(mst,mste,cost);
              
            break;
            
            default:  //invalid choice
            
              printf("\n\tEnter a vaild choice\n");
              
            break;
        }
    }
    
}


int menu(void)
{
    int ch = 0;
    printf("\n\tEnter what you want to do");
    printf("\n\t1.Enter the graph data");
    printf("\n\t2.Display adjacency matrix");
    printf("\n\t2.Display sorted edge set");
    printf("\n\t4.Create and print MST");
    printf("\n\t0.End");
    printf("\n\tYour choice: ");
    scanf("%d",&ch);
    return ch;
}


int adjacencymatrix(struct edge arr[],int adjmat[max][max],int vertex,int edge)
{
    int succ = 0;
    int src = 0;
    int dest = 0;
    int weight = 0;
    int cost = 0;
    int i = 0;
    int j = 0;
    for(i = 0; i <= vertex ;i++)
    {
        arr[i].src = 0;  //setting all elements to 0 initially
        arr[i].dest = 0;
        arr[i].weight = 0;
    }
    
    i = 0;
    
    while(i < edge)  //accept the number of edges user has asked for
    {
        printf("\n\tEnter source node: ");
        scanf("%d",&src);
        if(src > vertex || src < 1)  //source cant be greater than the last possible node and smaller than 0
        {
            printf("\n\tPlease enter a valid node\n"); 
        }
        else
        {
           printf("\n\tenter destination node: ");
           scanf("%d",&dest); 
           if(dest > vertex || dest < 1)    //destination cant be greater than the last possible node and smaller than 0
           {
               printf("\n\tPlease enter a valid node");  //if node is greater than the set value
           }
           else
           {
               printf("\n\tEnter weight: ");
               scanf("%d",&weight);
               arr[i+1].src = src;
               arr[i+1].dest = dest;
               arr[i+1].weight = weight;
               
               addEdge(adjmat,src,dest,weight);  //adding data to adjacency matrix
               i++;  //increment
               
           }  //dest if else
           
        }  //src if else
        //displayedges(arr,vertex);  
    }  //while loop
       
}

void addEdge(int adjmat[max][max], int src, int dest, int weight)   //function definition
{
    adjmat[src][dest] = weight;   //a[5][4]
    adjmat[dest][src] = weight;   //a[4][5]
}


void display(int farr[max][max],int fn)   //display matrix
{
    int i = 0;
    int j = 0;
    for( i = 1; i<= fn ; i++)
    {
        for( j = 1;j <= fn;j++)
        {
            printf("\t%d",farr[i][j]);
        }
        printf("\n");
    }
}


void bubblesort(struct edge arr[max],int fn)   //sorting the edgeset in ascending order
{
   int i = 0;
   int j = 0;
   struct edge temp ;  //temp variable of type struct edge
   for(i = 1; i <= fn; i++)
   {
       for(j = 1; j <= fn -1 ; j++)  
       {
           if(arr[j].weight > arr[j+1].weight)
           {
               temp = arr[j];
               arr[j] = arr[j+1];
               arr[j+1] = temp;
           }
       }
   }
   //displayedges(arr,fn);  //display sorted edge set
}



void displayedges(struct edge arr[max],int vertex)
{
    int i = 0;
    i = 1;
    printf("\n\tSorted edges");
    printf("\n\tSource\tDestination\tWeight");
    for(i = 1; i<= vertex ;i++)
    {
        printf("\n\t%d \t\t%d\t %d",arr[i].src,arr[i].dest,arr[i].weight);
    }
    
}

//create MST

int createMST(struct edge arr[max],int adjmat[max][max],int vertex,int edge,struct edge mst[max])
{
   int result = 0; //check result
   int source = 0; //source
   int destin = 0; //destination vertex
   int visited = 0; //check cycle
   int index = 0;  //for mst set
   int i = 0;   //counter
   int unionset[max];  //adding edges here
   int cost = 0;
   
   for(i = 0; i < max; i++)  //setting the union set
   {
       unionset[i] = i;
   }
   for(i = 1; i<= edge; i++)
   {
       source = arr[i].src;
       destin = arr[i].dest;
       visited = find(unionset,source,destin);  //find returns 1 when cycle detected
       
       if(visited == 0)
       {
           //not in same set, no cycle, can merge
           index++;
           //printf("\n\t%d \n",index);
           mergeSet(unionset,source,destin,edge);
           mst[index] = arr[i];
           cost = cost + mst[index].weight;
           
       }
       else
       {
           //Cycle detected not to be merged
           //printf("\n\tCycle detected\n");
       }
   }
   //displayMST(mst,index,cost);

   return cost;
}

//FIND CYCLE

int find(int unionset[max],int source,int destin)
{
    int result = 0;
    if(unionset[source] == unionset[destin])  
    {
        result = 1;
    }
    return result;
}

//MERGE 2 SETS
void mergeSet(int unionset[max],int source,int destin,int edge)
{
    int temp = 0;
    int i =0;
    temp = unionset[source];  //setting temp variable as source node
    i = 1;
    for(i = 1; i <= edge;i++)  //iterating for the number of edges present
    {
        if(unionset[i] == temp)  //if set i found
        {
             unionset[i] = unionset[destin]; //merge
        }
    }
}


//displayMST    
void displayMST(struct edge mst[max],int mstEdges,int cost)
{
    int i = 0;
    i  = 1;
    for(i = 1;i <= mstEdges;i++)
    {
        printf("\n\tEdge %d: ",i);
        printf("%d -> %d = %d",mst[i].src,mst[i].dest,mst[i].weight);
    }
    printf("\n\tcost = %d",cost);
}