#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

int maxprofit,num,n,C;
int include[10],bestset[10];
float bound;

typedef struct item{
	int w;
	int p;
	float p_w;
}item;
item item_array[10];

void sort(){
	item temp;
	for (int e = 1; e <= n; e++){
		for (int s = e + 1; s <= n; s++){
                	if (item_array[e].p_w < item_array[s].p_w){
	                	temp=item_array[e];
		    		item_array[e] = item_array[s];
                    		item_array[s] = temp;
                	}
            	}
        }
}

//compute upper bound
float KWF4(int i, int weight, int profit, int C){
	int bound = profit;
	int x[n];
	for(int j=i;j<n;j++){
		x[j]=0;
	}
	while(weight<C && i<=n){
		if(weight+item_array[i].w <= C){
			x[i]=1;
			weight = weight + item_array[i].w;
			bound = bound + item_array[i].p;
		}
		/*else{
			x[i] = (C-weight)/item_array[i].w;
			weight = C;
			bound = bound + item_array[i].p * x[i];
		}*/
		i++;
	}
	return bound;
}

bool promising(int i,int weight,int profit, int C){
	//cannot get a solution by expanding node i
	if(weight >= C){
		return false;
	}
	//sort array
	bound = KWF4(i+1,weight,profit,C);
	return (bound > maxprofit);
}

void knapsack(int i, int profit, int weight, int C){
	if(weight <= C && profit > maxprofit){
		//save better solution
		maxprofit = profit;
		num = i;
		for(int s=1;s<=n;s++){
			bestset[s] = include[s];
		}
	}
	if(promising(i,weight,profit,C)){
		include[i+1]=1;
		knapsack(i+1,profit+item_array[i+1].p,weight+item_array[i+1].w,C);
		include[i+1]=0;
		knapsack(i+1 ,profit,weight,C);
	}
}

int main(int argc, char* argv[]){
	if(argc <= 1){
                printf("Missing arguments\n");
	}
	else if(argc == 2){
		FILE * fp = fopen(argv[1],"r");
		char line[100],*token;
		int counter=0;
		int item_profit=1;
		int item_weight=1;

		item_array[0].p=-99;
		item_array[0].w=1;
	
		while((fgets(line,100,fp))!=NULL){
			token = strtok(line,",");
			while(token!=NULL){
				if(counter==0){
					n=atoi(token);
				}
				else if(counter==1){
					C=atoi(token);
				}
				else if(counter>1 && counter<n+2){
					item_array[item_profit].p=atoi(token);
					item_profit++;
				}
				else if(counter>=n+2){
					item_array[item_weight].w=atoi(token);
					item_weight++;
				}
				else{
				
				}
        		 	token = strtok(NULL,",");
        		 	counter++;
        		 }
		}

		num=0;
		for(int m=0;m<=n;m++){
			item_array[m].p_w=(float)item_array[m].p/item_array[m].w;
		}
		//SORT ITEMS BY P_W VALUE
		sort();
		knapsack(0,0,0,C);
		printf("\n\nSELECTED ITEMS:");
		printf("\n------------------------------------------------");
		int total_weight=0;
		for(int i=1;i<=num;i++){	
			if(bestset[i]!=0){
				printf("\nWeight = %d Profit = $ %d",item_array[i].w,item_array[i].p);
				total_weight = total_weight + item_array[i].w;
			}
		}
		printf("\n------------------------------------------------");
		//printf("\n");
		printf("\nTotal profit = $ %d",maxprofit);
		printf("\nTotal weight = %d",total_weight);
		printf("\n\n");
	  }	

	else{ 
		printf("Too many arguments!!\n");
	}
	return 0;
}
