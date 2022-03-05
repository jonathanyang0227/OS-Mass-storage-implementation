#include <bits/stdc++.h>
using namespace std;
int main()
{
        // Num of partitions files.
    int num_ways = 10;
    // The size of each partition files
    int run_size = 1000;
    char input_file[] = "input.txt";
    FILE *in = fopen(input_file, "w");
    if (in == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));

    for (int i = 0; i < num_ways * run_size; i++) {
        if (i % 2 == 0){
            fprintf(in, "%d\n ", rand());
        }
        else {
            fprintf(in, "%d\n ", -rand());
        }
    }
         fclose(in);
         return 0;
}
