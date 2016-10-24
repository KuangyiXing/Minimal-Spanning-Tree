/*Kruskal algorithm */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>




struct vertice{
 
  int id;
  int parent_id;
  double key;
  int is_visited;

};


struct edge{

  int source_id;
  int destination_id; 
  double weight;
  int order;
  
};

int num = 0;

void quick_sort( struct edge[], int , int );
int partition(struct edge [], int , int );
struct vertice MakeSet(int );
int Find(struct vertice [], struct vertice );
void Union(struct vertice[] ,struct vertice ,struct vertice );
void Kruskal(struct vertice[], struct edge[],int, int);
void Prim(struct vertice[],double[][num],int,int);
void min_heapify(struct vertice [],int, int);
void build_min_heap(struct vertice [], int);
int mst();


double k_sum = 0.0;
double p_sum = 0.0;
float k_time = 0.0;
float p_time = 0.0;

int main(){
    
   int i;
   double k_length[4] = {0.0};
   double p_length[4] = {0.0};
   float k_rtime[4] = {0.0};
   float p_rtime[4] = {0.0};
   
   for (int i = 0; i < 20; i++)
   {
   num = 10;
   mst();
   k_length[0] += k_sum;
   p_length[0] += p_sum;
   k_rtime[0] += k_time;
   p_rtime[0] += p_time;
   
   num = 100;
   mst();
   k_length[1] += k_sum;
   p_length[1] += p_sum;
   k_rtime[1] += k_time;
   p_rtime[1] += p_time;
   
   num = 500;
   mst();
   k_length[2] += k_sum;
   p_length[2] += p_sum;
   k_rtime[2] += k_time;
   p_rtime[2] += p_time;
   
   num = 1000;
   mst();
   k_length[3] += k_sum;
   p_length[3] += p_sum;
   k_rtime[3] += k_time;
   p_rtime[3] += p_time;
   }
   
   for(int i = 0; i <4; i++){
     
     switch (i) {
     case 0 :
     printf ("Vertice num is 10 \n"); 
     break;
     
     case 1 :
     printf ("Vertice num is 100 \n"); 
     break;
     
     case 2 :
     printf ("Vertice num is 500 \n"); 
     break;
     
     case 3 :
     printf ("Vertice num is 1000 \n"); 
     break;
     
     
     }
     
     
     
     
     
     
     printf("Kruskal - Average length : %f Average running time is : %lf \n", k_length[i]/20,k_rtime[i]/20);
     printf("Prim - Average length : %f Average running time is : %lf \n", p_length[i]/20, p_rtime[i]/20);
   
   }
   
   return 0;
   
   




}





int mst()
{
     struct timeval start,end;
     
     float k_delta;
     float p_delta;
     
     srand(time(NULL));
     
     int edge_num = (num * (num - 1))/2;
     int edge_index = 0;
     int i,j;
     
     double g[num][num];
     struct edge e[edge_num];
     struct vertice v[num];


     
  //   printf("Unsorted array is : ");
     for(i = 0;i < num ;i++)
     {
        g[i][i] = 1;
       for(j = i + 1;j< num;j++)
        {
            e[edge_index].source_id = i;
            e[edge_index].destination_id = j;
           // e[edge_index].weight = (rand()+0.5)/(RAND_MAX+1.0);
            e[edge_index].weight = (double) rand()/(double) RAND_MAX;
            e[edge_index].order = edge_index;
            
            
            g[i][j] = e[edge_index].weight;        
            g[j][i] = g[i][j];
          
            
            
            
         //   w[edge_index] = e[edge_index].weight;
         
       //    w[edge_index] = rand();
           //  w[edge_index] = (rand()+0.5)/(RAND_MAX+1.0);
           //  e[edge_index].weight = w[edge_index];
        // 
         // w[edge_index] = 1- edge_index * 0.01;
       //   printf("%f source id is %d destination id is %d \n",e[edge_index].weight,e[edge_index].source_id,e[edge_index].destination_id);
          edge_index ++;  
        //  printf("the iteration number is %d",edge_index);
         }
         }
      

  gettimeofday(&start,NULL);
  Kruskal(v,e,num,edge_num);
  gettimeofday(&end,NULL);
  k_delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
  k_time = k_delta;
 // printf("running time is %lf\n", k_delta);
  
  
  
     
  gettimeofday(&start,NULL); 
  Prim(v,g,num,edge_num);
  gettimeofday(&end,NULL);
  p_delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
  p_time = p_delta;
//  printf("running time is %lf\n", p_delta);
  
      
  return 0;


}








void Kruskal(struct vertice v[],struct edge e[],int num, int edge_num){
    
    int i,j;
    double sum = 0;    
    quick_sort(e,0,edge_num -1);
    
    
    for(i = 0; i < num; i++ )
      {     
       v[i] = MakeSet(i);   
     //  printf("id: %d parent_id : %d rank : %d",v[i].id, v[i].parent_id,v[i].rank);  
       } 
    
   // printf("Sorted array is:  ");
  //	for(i = 0; i < edge_num; i++) printf(" %f source id is %d destination id is %d \n", e[i].weight,e[i].source_id,e[i].destination_id);


      // exit(0);
      
       for(i =0; i < edge_num;i++)   
       {        
                struct vertice a = v[e[i].source_id];
                struct vertice b = v[e[i].destination_id];
                
                if(Find(v,a) != Find(v,b)){
           //         printf("%d and %d are not in the same set\n",a.id,b.id);
                    sum += e[i].weight;
           //         printf("sum is %f\n",sum);
                    Union(v,a,b);
                         
                }
        
        }
        
       k_sum = sum; 
   //   printf("Vertice num : %d Kruskal : Sum is %f ",num,sum);  
  
   
}




void Prim(struct vertice v[],double g[][num],int num,int edge_num){
     
     double s = 0.0;
     int heap_size;
   //  printf("original sum is %f \n",s);
     
     int i,j;
     
    struct vertice heap[num];
     
     int front = 0;
    
     
     for(i = 0;i < num;i++){
       v[i].id = i;
       v[i].parent_id = num;  
       v[i].key = 1; 
       v[i].is_visited = 0;
       heap[i] = v[i]; 
     }
     
    heap[0].key = 0;
    
    
    heap_size = num;
    
    
    while (heap_size > 0){
    
       
       
       build_min_heap(heap,heap_size);
       
   //    for(i = 0; i< num;i++)     printf("the key of %d is %f  \n", v[i].id,v[i].key);
       
       struct vertice u = heap[0];
       
       heap[0].is_visited = 1;
       
       s += heap[0].key;
       
     //  printf("the key of %d %f is added. sum is %f \n",heap[0].id,heap[0].key,s);
       
      // for(j = 0 ; j < num;j++)
      // {
       
        //  printf("graph weight is %f from %d to %d \n",g[u.id][j],u.id,j);
              
              for (i = 0; i < heap_size;i++){
              
                        
              if(heap[i].is_visited != 1  && g[u.id][heap[i].id] < heap[i].key ){
               
             //  printf("%f and %f are comparied \n",g[u.id][j],heap[j].key);
               heap[i].parent_id = u.id;
               heap[i].key = g[u.id][heap[i].id];
               
                }
                
       //         }
            
       
       }
       
    //   for(i = 0; i< num;i++)   printf("the sorted key of %d is %f \n", v[i].id,v[i].key);
       
       heap[0] = heap[heap_size - 1] ;       
       
       
    /*   for(int i=0; i< heap_size -1;i ++)
       {
           printf("the key %d of %f at position %d\n",heap[i].id,heap[i].key,i ); 
         
       }*/
       
       
      heap_size --;
    
    }
    
  //  printf("Vertice num : %d Prim : Sum is %f ",num,s);
    
    p_sum = s;
    
    
    
/*   while(front != rear){
        
        min_heapify(heap,front);
        struct vertice u = heap[0];
        
        
        for(int i = 0;i< edge_num;i++){
           if(e[i].source_id == u.id {
                for(int j = front; j < num; j++){
                     if (e[i].destination_id == v[j])        
                            
                }
        
           
           }
        
        
        }         
         
         
          for (i = 0; i < num;i ++)
              printf("%d\n",heap[i].key);

    }*/

}


void build_min_heap(struct vertice heap[], int heap_size){

      int i;
  //    printf(" size is %d \n ",heap_size);
      for (i = heap_size - 1 ;i >= 0; i-- )
        {  //printf("from the %d begin heapify \n",i);
         min_heapify(heap,i,heap_size);}
    
      

}



void min_heapify(struct vertice heap[], int i , int heap_size){

  //   printf("the heapify from %d is successful \n", i);
     int min = i;
    // int heap_size = (sizeof(*v)/sizeof(h[0]));
     int l = 2*i+1;
     int r = 2*i+2;
     
     struct vertice temp;
     
    if(l < heap_size   && heap[l].key < heap[i].key)
        min = l;
     else 
        min = i;
        
     if(r < heap_size && heap[r].key < heap[min].key)
        min = r;
        
     
     
     if(min != i)
     {
    //    printf("the exchange number are %d %f and %d %f \n", heap[min].id,heap[min].key, heap[i].id, heap[i].key);
        
         temp = heap[min];
         heap[min] = heap[i];
         heap[i] = temp;
         
    //     printf("the minimal number are %d %f at position %d \n",heap[i].id,heap[i].key, i);
         min_heapify(heap,min,heap_size);
          
         
     }   
//     printf("the heapify from %d is finished \n", i);  
     
     



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
  return x;
}


int Find(struct vertice v[], struct vertice u){

   
   if (v[u.id].parent_id != v[u.id].id)
   {   
        v[u.id].parent_id = Find(v,v[u.parent_id]);
        
        }
        
  //   printf("my id is %d my parent id is %d \n",v[u.id].id, v[u.id].parent_id ); 
     return v[u.id].parent_id;

}



void Union(struct vertice v[],struct vertice x,struct vertice y){
  
  
  int xRoot_id, yRoot_id;
  
  xRoot_id = Find(v,x);
  yRoot_id = Find(v,y);
  
  
//   printf("%d and %d are union\n", xRoot_id,yRoot_id);
  v[xRoot_id].parent_id = v[yRoot_id].id;
  


}


