#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
typedef struct Directory{
    int sr_no;
    char name[100];
    char first[50];
    char last[50];
    char ph_no[20];
    long int cell_no;
    char concat[100];
}Directory;
Directory dir[100],di;

int count =0,quick_counter=0,quick_start=0;

void display();
void create(char *);
void concat();
void merge(int ,int ,int );
void mergeSort(int ,int );
int partition(int ,int );
void rquicksort(int ,int );
void sortDirectory();
int binarySearch(char *,int ,int );
void searchDirectory(char *);
void insertEntry(char* ,char* );
void deleteEntry(char*,char*,int);

void display(){
	printf("\n=============PHONE DIRECTORY=====================");
	for(int i=0;i<count;i++){
		printf("\n%d %s %s, %s",i+1,dir[i].first,dir[i].last,dir[i].ph_no);
	}
	printf("\n=================================================");
	printf("\n\n\n");
}


void create(char file_name[45]){
	int i=0,ph_len =13,k;
        char sr[3];
        FILE * fp = fopen(file_name,"r");
        if(fp != NULL){
        	while(EOF != fscanf(fp,"%s %s %s %s ",sr,dir[count].first ,dir[count].last,dir[count].ph_no)){
        		
			count++;
		}
	}

	for(i=0;i<count;i++){
	        int len = strlen(dir[i].last);
		dir[i].last[len-1] ='\0';
		strcat(dir[i].name,dir[i].first);
		strcat(dir[i].name," ");
		strcat(dir[i].name,dir[i].last);
		strcat(dir[i].name,"\0");
	}

	fclose(fp);
}



void concat(){
	int i=0;
	for(i=0;i<count;i++){
	
		strcpy(dir[i].concat,dir[i].last);
    		strcat(dir[i].concat,dir[i].first);
    }
}


void merge(int low,int mid,int high){
	int L = mid-low+1;    //no. of elements in left sub-array
	int R = high-mid;    //no. of elements in the right sub-array
	Directory left[L], right[R];
	for(int j=0;j<L;j++){
	        left[j].sr_no = dir[low+j].sr_no;
	        strcpy(left[j].first,dir[low+j].first);
	        strcpy(left[j].last,dir[low+j].last);
	        strcpy(left[j].ph_no,dir[low+j].ph_no);
	}
	for(int k=0;k<R;k++){
	        right[k].sr_no = dir[low+k].sr_no;
                strcpy(right[k].first,dir[mid+1+k].first);
                strcpy(right[k].last,dir[mid+1+k].last);
                strcpy(right[k].ph_no,dir[mid+1+k].ph_no);
	}
	int i=0,j=0,k=low;
	while(i<L || j<R){
	        int a = strcmp(left[i].last, right[j].last);
	        if(i >= L){
	                dir[k++] = right[j++];
	                continue;
	        }
           	if(j >= R){
                	dir[k++] = left[i++];
                	continue;
           	}
           	if(a<0){
                	dir[k++] = left[i++];
           	}
        	else if(a==0){
            		int b = strcmp(left[i].first,right[j].first);
            		if(b<0){
                		dir[k++] = left[i++];
            		}
            		else{
                		dir[k++] = right[j++];
            		}
        	}
        	else{
                	dir[k++] = right[j++];
         	}
    	}
}

void mergeSort(int low,int high){
	if(low<high){
	        int mid = (low+high)/2;
	        mergeSort(low,mid);
	        mergeSort(mid+1,high);
	        merge(low,mid,high);
	}
}

int partition(int start,int end){
	srand(time(NULL));
	int pivot_index = (rand() % (end - start)) + start;
	Directory pivot = dir[pivot_index];
	dir[pivot_index] = dir[end];
	dir[end] = pivot;
	int i = start-1;
	for(int j=start;j<=end-1;j++){
		if(strcmp(dir[j].ph_no,pivot.ph_no)<=0){
			i=i+1;
			Directory temp=dir[j];
			dir[j]=dir[i];
			dir[i]=temp;
		}
	}
	Directory temp1=dir[end];
			dir[end]=dir[i+1];
			dir[i+1]=temp1;
	return i+1;
}

void rquicksort(int start,int end){
	if(start<end){
		int part = partition(start,end);
		rquicksort(start,part-1);
		rquicksort(part+1,end);
	}
	else if(start>end){
	
	}
}

void sortDirectory(){
	mergeSort(0,count-1);
    	int a,b,i=0;
    	for(i=0;i<count;){
    		if(strcmp(dir[i].last,dir[i+1].last)==0 && strcmp(dir[i].first,dir[i+1].first)==0){			
			int start = i, end =i, jump=0;
			while(end<count && strcmp(dir[i].last,dir[end].last)==0 && strcmp(dir[i].first,dir[end].first)==0){
				end++;
			}
			end--;
			jump =i;
			rquicksort(start,end);
			i =end+1;
		}
		else{
			i++;
		}
    	}
}


void searchDirectory(char name[]){
	int a;
	a = binarySearch(name,0,count-1);
	if(a == -1){
		printf("\nName not found");
	}
	else{
		printf("\nFOUND");
		char name2[256]="";
		strcat(name2,dir[a].first);
		strcat(name2," ");
		strcat(name2,dir[a].last);
		strcat(name2,"\0");
		int j=a;
		while(j>=0 && strcmp(name,name2)==0){
			printf("\n%d %s %s, %s",j+1,dir[j].first,dir[j].last,dir[j].ph_no);
			j--;
			strcpy(name2,"");
			if(j>=0){
			strcat(name2,dir[j].first);
			strcat(name2," ");
			strcat(name2,dir[j].last);
			strcat(name2,"\0");
			}
			
		}
		j=a+1;
		if(j<count){
		strcpy(name2,"");
		strcat(name2,dir[j].first);
		strcat(name2," ");
		strcat(name2,dir[j].last);
		strcat(name2,"\0");}
		while(j<count && strcmp(name,name2)==0){
			printf("\n%d %s %s, %s\n",j+1,dir[j].first,dir[j].last,dir[j].ph_no);	
			j++;
			strcpy(name2,"");
			if(j<count){
			strcat(name2,dir[j].first);
			strcat(name2," ");
			strcat(name2,dir[j].last);
			strcat(name2,"\0");
			}
			
		}

	}
}

int binarySearch(char name[],int left,int right){
	int i=0;
	char name_temp[100];
	strcpy(name_temp,name);

	char* tok=strtok(name_temp,"\n ");
	char compare[100];
	
	Directory d;
	strcpy(d.first,tok);

	tok=strtok(NULL,"\n ");


	strcpy(d.last,tok);
	tok=NULL;
	strcpy(compare,d.last);
	strcat(compare,d.first);




	if(left <=right){ 
		int mid =left + (right - left)/2;
		
		int check = strcmp(compare,dir[mid].concat);	
		if(check==0){

			return mid;
		}
		
		if(check<0){
			return binarySearch(name,left,mid-1);	
				
		}
		
		else{
			return binarySearch(name,mid+1,right);
		}
	}
	
		
	else{

		return -1;
	}
}

void insertEntry(char* name,char* phone_number){

	int a = binarySearch(name,0,count-1);
	int flag=0;
	if(a>0){
		int j=a;
		char name2[100];
		strcpy(name2,"");
		strcat(name2,dir[a].first);
		strcat(name2," ");
		strcat(name2,dir[a].last);
		strcat(name2,"\0");
		while(j>=0 && strcmp(name,name2)==0){
			if(strcmp(dir[j].ph_no,phone_number)==0){
				flag=1;
			break;
			}
			j--;
			
			if(j>=0){
				strcpy(name2,"");
				strcat(name2,dir[j].first);
				strcat(name2," ");
				strcat(name2,dir[j].last);
				strcat(name2,"\0");			
			}			
		}
		j=a+1;
		if(j<count){
			strcpy(name2,"");
			strcat(name2,dir[j].first);
			strcat(name2," ");
			strcat(name2,dir[j].last);
			strcat(name2,"\0");
		}
		while(j<count && strcmp(name,name2)==0){
			if(strcmp(dir[j].ph_no,phone_number)==0){
				flag=1;
				break;
			}
			j++;
			
			if(j<count){
				strcpy(name2,"");
				strcat(name2,dir[j].first);
				strcat(name2," ");
				strcat(name2,dir[j].last);
				strcat(name2,"\0");
			}
			
		}
	}
	if(flag!=1){
		char name_temp[100];
		strcpy(name_temp,name);
		char* tok=strtok(name_temp,"\n ");
		char compare[100];
	
		Directory d;
		strcpy(d.first,tok);
		tok=strtok(NULL,"\n ");
		strcpy(d.last,tok);
		tok=NULL;
		strcpy(compare,d.last);
		strcat(compare,d.first);
		strcpy(dir[count].first,d.first);
		strcpy(dir[count].last,d.last);
		strcpy(dir[count].ph_no,phone_number);
		count++;
		sortDirectory();
		concat();
	}
	else
		printf("Entry already exists in the Directory\n");
	}

int main(int argc, char* argv[]){

	if(argc <= 1){
                printf("\nMissing arguments\n");
	}
	else if(argc == 2){
		create(argv[1]);
		sortDirectory();
		concat();
		int num;
		char name[30];
		char phone_num[13];
		Directory di;

	        while(1){
                	printf("\nPlease provide options: \n");
                	printf("Insert          (press 1)\n");
                	printf("Search          (press 2)\n");
                	printf("Delete          (press 3)\n");
                	printf("Show Directory  (press 4)\n");
                	printf("Exit(press 5)\n");
                	scanf("%d",&num);
                	switch(num){
                        	case 1:
                                	printf("\nEnter the name to insert: \n");
                                        scanf("%s %s",di.first,di.last);
					strcpy(di.name,di.first);
					strcpy(di.name," ");
					strcpy(di.name,di.last);
                                      	printf("\nEnter phone number: ");
                                        scanf("%s",di.ph_no);
					char name1[30];
					char name2[30];
					char name3[30];
					strcpy(name1,di.first);
					strcpy(name2," ");
					strcpy(name3,di.last);
					strcat(name1,name2);
					strcat(name1,name3);
					strcat(name1,"\0");
					insertEntry(name1,di.ph_no);					
					break;
                        	case 2:
                                	printf("\nEnter the name to be Searched: ");
					scanf("%s %s",di.first,di.last);
					char name4[30];
					char name5[30];
					char name6[30];
					strcpy(name4,di.first);
					strcpy(name5," ");
					strcpy(name6,di.last);
					strcat(name4,name5);
					strcat(name4,name6);
					strcat(name4,"\0");
					searchDirectory(name4);
                                	break;
                        	case 3:
					printf("\nEnter the entry to be deleted: ");
                                        scanf("%s %s",di.first,di.last);
					int old_count = count;
					int pos;
					int flag=0;
					for(int i=count-1;i>=0;i--){							
						if(strcmp(dir[i].first,di.first)==0 && strcmp(dir[i].last,di.last)==0){
							pos = i;
							flag=1;
							break;
						}
					}
					if(flag==0){
						printf("\nEntry not found\n");
						exit(0);

					}
					for(int i=pos; i<count; i++){
						strcpy(dir[i].first,dir[i+1].first);
						strcpy(dir[i].last,dir[i+1].last);
			                	strcpy(dir[i].ph_no,dir[i+1].ph_no);
					}
					count--;
					sortDirectory();
                                	break;
                        	case 4:
      	                          	printf("Phone Directory \n");
					display();
					
                                	break;
                        	case 5:exit(0);

                	}
        	}
	}
	else{
		printf("\nToo many arguments!!");
	}

	return 0;
}











