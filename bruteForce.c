#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//bruteForce 0/1 knapsack

//global array declaration
int bestChoice[100];

//bruteForce knapsack function
int bruteForce(int n,int limit,int tProfit[],int tWeight[]) {
	int i,j,selected=1;
	int totalWeight,totalProfit;
	int n_subset;
	int maxProfit=0;
	int temp[n];
	n_subset = pow(2.0,n);

	//Initialize the temp array by 0 
	for(i =0;i<n;i++)
		temp[i]=0;

	for(i=0;i<n_subset;i++) {
		selected=1;
		totalProfit=0;
		totalWeight=0;

		for(j=0;j<n;j++){
			if(temp[j]==1){
				totalWeight = totalWeight + tWeight[j];
				totalProfit = totalProfit + tProfit[j];
			}
		}
		if(totalProfit > maxProfit && totalWeight <= limit){
			//selected items in array. 
			for(j=0;j<n;j++){
				bestChoice[j] = temp[j];
				maxProfit = totalProfit;
			}
		}
		// subset calculation
		for(j=0;j<n;j++){
			temp[j]=temp[j]+selected;
			selected = temp[j]/2;
			//printf("Selected is %d\n",selected);
			temp[j]=temp[j]%2;	
		} 
	}

	//comparing the bestChoice item array and printing the selected items
	totalWeight = 0;
	totalProfit = 0;
	printf("\nSelected Items:\n");
	printf("---------------------------------------------");
	for(i=0;i<n;i++) {
		if(bestChoice[i]==1) {
			totalWeight = totalWeight + tWeight[i];
			totalProfit = totalProfit + tProfit[i];
			printf("\nItem%d, Profit = $%d  Weight =  %d",i+1,tProfit[i],tWeight[i]);
		}
	}
	printf("\n---------------------------------------------\n");
	printf("Total Profit = $%d\n",totalProfit);
	printf("Total Weight = %d\n\n",totalWeight);
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
                			//printf("size %d\n",size);
            			}
            			else if(counter==1){
                			//printf("\nreading capacity= %d\n",atoi(token));
                			capacity=atoi(token);
            			}
            			else if(counter>1 && counter<size+2){
                			profit[pi]=atoi(token);
                			//printf("profit is %d\n",profit[pi]);
                			pi++;
            			}
            			else if(counter>=size+2){
                			weight[wi]=atoi(token);
               	 			//printf("weight is %d\n",weight[wi]);
							wi++;
            			}
            			else{
            
            			}
                 token = strtok(NULL,",");
                 counter++;
            }
    }
    bruteForce(size,capacity,profit,weight);
    fclose(fp);
	}
	return 0;
}
