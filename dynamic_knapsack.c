#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//dynamic 0/1 knapsack

int bestChoice[100];

//dynamic knapsack function
int dynamic(int n,int limit,int tprofit[],int tweight[]) {
	int i,w,result=0;
	int B[n+1][limit+1];
	int totalWeight,totalProfit;

	for(w=0;w<=limit;w++)
		B[0][w]=0;
	for(i=0;i<=n;i++)
		B[i][0]=0;

	for(i=1;i<=n;i++){
		for(w=1;w<=limit;w++){
			if((tweight[i-1] <= w) && ((B[i-1][w-tweight[i-1]] + tprofit[i-1]) > B[i-1][w])) {
				B[i][w]=B[i-1][w-tweight[i-1]] + tprofit[i-1];
			}
			else {
				B[i][w]=B[i-1][w];
			}
		}
	}
	//initializing bestChoice of array to 0
	for(i=0;i<n;i++)
		bestChoice[i]=0;

	w=limit;
	i=n;

	//if item is selected then set that item in bestchoice array as 1
	while(B[i][w]!=0) {
		if(B[i][w] == B[i-1][w]){
			i=i-1;
		} 
		else{
			bestChoice[i-1]=1;
			w=w-tweight[i-1];
			i=i-1;
		}
	}

	//comparing the bestChoice item array and printing the selected items
	totalWeight = 0;
	totalProfit = 0;
	printf("\nSelected Items:\n");
	printf("---------------------------------------------");
	for(i=0;i<n;i++) {
		if(bestChoice[i]==1) {
			totalProfit = totalProfit + tprofit[i];
			totalWeight = totalWeight + tweight[i];
			printf("\nItem%d, Profit = $%d  Weight = %d",i+1,tprofit[i],tweight[i]);
		}
	}
	printf("\n---------------------------------------------\n");
	printf("Total Profit = $%d\n",totalProfit);
	printf("Total Weight = %d\n",totalWeight);
	return 0;
}

//main function to read a file and taking inputs
int main(int argc,char * argv[]){
	int size;
	int capacity;
	int weight[100];
	int profit[100];
	char line[100],*token;
    int counter=0;
    int pi=0,wi=0;
	
	if(argc <= 1){
                printf("Missing arguments\n");
	}
	else if(argc == 2){
		FILE * fp = fopen(argv[1],"r");
		//printf("\nINSIDE MAIN\n");
   			while((fgets(line,100,fp))!=NULL){
        		token = strtok(line,",");
        			while(token!=NULL){
            			if(counter==0){
                			size=atoi(token);
            			}
            			else if(counter==1){
                			capacity=atoi(token);
            			}
            			else if(counter>1 && counter<size+2){
                			profit[pi]=atoi(token);
                			pi++;
            			}
            			else if(counter>=size+2){
                			weight[wi]=atoi(token);
							wi++;
            			}
            			else{
            
            			}
                 token = strtok(NULL,",");
                 counter++;
            }
    }
    dynamic(size,capacity,profit,weight);
    fclose(fp);
	}
	return 0;
}
