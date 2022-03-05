#define _GNU_SOURCE
#include <bits/stdc++.h>
#include<stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/times.h>

using namespace std;

void set_cpu(int id)
{
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(id, &mask);
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
    {
        fprintf(stderr, "warning: could not set CPU affinity/n");
    }
}
void getmin(int file){
    char fileName[3], output;
    char fileName1[3];
    int i = 0;
    int n1;
    int n2;
    int min;
    // convert i to string
    snprintf(fileName, sizeof(fileName), "%d", file);
    FILE *in1 = fopen(fileName, "r");
    if (in1 == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    snprintf(fileName, sizeof(fileName), "%d", file+1);
    FILE *in2 = fopen(fileName, "r");
    if (in2 == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }  
    FILE *temp = fopen("texp.txt", "w");
    if (temp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    char a[20],b[20];
    stringstream si;
    while (fgets(a,20,in1)!=NULL && fgets(b,20,in2)!=NULL) {
        n1=atoi(a);
        n2=atoi(b);
        if (n1 <= n2) {
            si<<a;
        } else {
             si<<b;  
        }
    }
        while (fgets(a,20,in1)==NULL) { 
        if( fgets(b,20,in2)==NULL)
                break;
             si<<b;
           cout<<"hi"<<endl;
        }
        while (fgets(b,20,in2)==NULL) {
            if(fgets(a,20,in1)==NULL)
                break;
            else{
            si<<a;
            }
        }
        //cout<<si.str().c_str()<<endl;
         fputs(si.str().c_str(),temp);
         si.str("");
         snprintf(fileName, sizeof(fileName), "%d", file/2);
    rename("texp.txt", fileName);
    fclose(in2);
    fclose(in1);
    fclose(temp);
}
// Merges two  arr[].
/*void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m+1;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}*/

void mergeFiles(char *output_file, int n, int k)  // k ＝10
{
    double START_part,END_part;
    FILE *in[k];
    for (int i = 0; i < k + 1; i++) {
        char fileName[2];
        snprintf(fileName, sizeof(fileName), "%d", i);
        in[i] = fopen(fileName, "r");
        if (in[i] == NULL) {
            perror("Error while opening the file.\n");
            exit(EXIT_FAILURE);
        }
    }
    int count=1;
    while(k>1){
         cout<<"第"<<count<<"次merge"<<"......"<<endl;
         for (int i = 0; i < k; i+=2){
             START_part = clock();
             //compare one nums of each two files from the min and then put the num into temp 
             getmin(i);
              END_part = clock();
             cout<<"第"<<(i>>1)<<"檔案花費"<<(END_part - START_part) / CLOCKS_PER_SEC<<endl;
         }
        k=k>>1;
        count++;
    }
    //cout<<"done"<<endl;
    //change the final files to outputfile 
    rename("0", "output.txt");
    for (int i = 0; i < k; i++)
        fclose(in[i]);
    
}
// sort and divide num into partition files 
void Initial(char *input_file, int run_size, int num_ways)
{
    FILE *in = fopen(input_file, "r");
    if (in == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    FILE *out[num_ways];
    char fileName[2];
    for (int i = 0; i < num_ways; i++) {
        // convert i to string
        snprintf(fileName, sizeof(fileName), "%d", i);
        out[i] = fopen(fileName, "w");
        if (out[i] == NULL) {
            perror("Error while opening the file.\n");
            exit(EXIT_FAILURE);
        }
    }
    int *arr = (int *) malloc(run_size * sizeof(int));
    bool more_input = true;
    int next_output_file = 0;
    char s[20];
    int i;
    stringstream si;
       double START,END;
       //partition time
       START = clock();
    while (1) {
        // write num into arr from input file
        for (i = 0; i < run_size; i++) {
            if (fgets(s, 20, in) == NULL) {
                more_input = false;
                break;
            }
            arr[i]=atoi(s);
            
        }
        if(!more_input)
            break;
        // sort array using merge sort
        sort(arr,arr+run_size);
       //mergeSort(arr, 0, i - 1);
       for (i = 0; i < run_size; i++) {
        si<<arr[i];
        si<<"\n";
       }
           //cout<<si.str().c_str()<<endl;
            fputs(si.str().c_str(),out[next_output_file]); 
            si.str("");
        next_output_file++;
    }
  END = clock();
  cout<<"partition花費"<<(END - START) / CLOCKS_PER_SEC << endl;
    // close input and output files
    for (int i = 0; i < num_ways; i++)
        fclose(out[i]);
    free(arr);
    fclose(in);
}

void externalSort(char *input_file, char *output_file, int num_ways,int run_size)
{
    Initial(input_file, run_size, num_ways);
    mergeFiles(output_file, run_size, num_ways);
}

int main()
{
    double START,END;
    // Num of partitions files.
    int num_ways = 10;

    // The size of each partition files
    int run_size = 1000;

    char input_file[] = "input.txt";
    char output_file[] = "output.txt";

    // puts("cpu affinity set");
	//set_cpu(0x0003);

     START = clock();
    externalSort(input_file, output_file, num_ways, run_size);
     END = clock();
     cout << "程式總時間"<<(END - START) / CLOCKS_PER_SEC << endl;
    return 0;
}