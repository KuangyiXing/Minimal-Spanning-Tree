/*Kruskal algorithm */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>




struct vertice{
 
  int id;
  int parent_id;
  int rank;

};


struct edge{

  int source_id;
  int destination_id; 
  double weight;
  int order;
  
};




void quick_sort( struct edge[], int , int );
int partition(struct edge [], int , int );
struct vertice MakeSet(int );
int Find(struct vertice [], struct vertice );
void Union(struct vertice[] ,struct vertice ,struct vertice );



int main()
{
     srand(time(NULL));
     double sum = 0;
     int num = 10;
     int edge_num = (num * (num - 1))/2;
     int edge_index = 0;
     int i,j;

   //  double w[edge_num];
     struct edge e[edge_num];
     struct vertice v[num];
//     double edge[num][num];

     for(i = 0; i < num; i++ )
      {     
       v[i] = MakeSet(i);   
     //  printf("id: %d parent_id : %d rank : %d",v[i].id, v[i].parent_id,v[i].rank);  
       } 
     printf("Unsorted array is : ");
     for(i = 0;i < num ;i++)
       for(j = i+1;j< num;j++)
        {
            e[edge_index].source_id = i;
            e[edge_index].destination_id = j;
            e[edge_index].weight = (rand()+0.5)/(RAND_MAX+1.0);
            e[edge_index].order = edge_index;
         //   w[edge_index] = e[edge_index].weight;
         
       //    w[edge_index] = rand();
           //  w[edge_index] = (rand()+0.5)/(RAND_MAX+1.0);
           //  e[edge_index].weight = w[edge_index];
        // 
         // w[edge_index] = 1- edge_index * 0.01;
          printf("%f source id is %d destination id is %d \n",e[edge_index].weight,e[edge_index].source_id,e[edge_index].destination_id);
          edge_index ++;  
        //  printf("the iteration number is %d",edge_index);
         }
      
        
     quick_sort(e,0,edge_num -1);
    
    printf("Sorted array is:  ");
	for(i = 0; i < edge_num; i++)
		printf(" %f source id is %d destination id is %d \n", e[i].weight,e[i].source_id,e[i].destination_id);


      // exit(0);
      
       for(i =0; i < edge_num;i++)   
       {        
                struct vertice a = v[e[i].source_id];
                struct vertice b = v[e[i].destination_id];
                
                if(Find(v,a) != Find(v,b)){
                    printf("%d and %d are not in the same set\n",a.id,b.id);
                    sum += e[i].weight;
                    printf("sum is %f\n",sum);
                    Union(v,a,b);
                         
                }
        
        }
        
        
      printf("Sum of weight is %f\n",sum);  
      
      
  return 0;


}


void quick_sort(struct edge a[],int l,int u)
{
    int j;
    if(l<u)
    {
        j=partition(a,l,u);
        quick_sort(a,l,j-1);
        quick_sort(a,j+1,u);
    }
}
 
int partition(struct edge a[],int l,int u)
{
    int i,j,k;
    struct edge v,temp;
    v=a[l];
    i=l;
    j=u+1;
    
    do
    {
        do
            i++;
            
        while(a[i].weight<v.weight&&i<=u);
        
        do
            j--;
        while(v.weight <a[j].weight);
        
        if(i<j)
        {
            temp =a[i];
            a[i] = a[j];
            a[j] =temp;
            
            
        }
    }while(i<j);
    
    a[l]=a[j];
    a[j]=v;
    
    
    
    return(j);
}


struct vertice MakeSet(int id){

  struct vertice x;
  x.id = id;
  x.parent_id = x.id;
  x.rank = 0;
  return x;
}


int Find(struct vertice v[], struct vertice u){

   
   if (v[u.id].parent_id != v[u.id].id)
   {   
        v[u.id].parent_id = Find(v,v[u.parent_id]);
        
        }
        
     printf("my id is %d my parent id is %d \n",v[u.id].id, v[u.id].parent_id ); 
     return v[u.id].parent_id;

}



void Union(struct vertice v[],struct vertice x,struct vertice y){
  
  
  int xRoot_id, yRoot_id;
  
  xRoot_id = Find(v,x);
  yRoot_id = Find(v,y);
  
  
   printf("%d and %d are union\n", xRoot_id,yRoot_id);
  v[xRoot_id].parent_id = v[yRoot_id].id;
  


}


