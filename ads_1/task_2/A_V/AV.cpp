#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cmath>
#include<fstream>
#include "../../sorting_algs.hpp"


int main() {
    std::ios_base::sync_with_stdio(0);
    std::ofstream file;
    // random const asc desc A_shape V_shape
    file.open("output.csv");
    file << "size;HSa;MSa;QSa;HSa;MSa;QSa\n";
    srand(time(0));
    for (int i = 1; i <= 200; i++) {
        clock_t start_t, end_t;
        int size = 5000*i;
        clock_t s1= 0;clock_t s2 = 0;
        clock_t s3 = 0;clock_t s4 = 0;
        clock_t s5 = 0;clock_t s6 = 0;
        int *A = new int [size];
        for(int run =0; run<6;run++){

        A_shape(A,size - run);
        start_t = clock();
        heap_sort(A,size - run);
        end_t = clock();
        clock_t total_t_ha = (end_t - start_t);
        s1 += total_t_ha;
        }
        for(int run =0; run<6;run++){

        A_shape(A,size-run);
        start_t = clock();
        merge_sort(A, size- run);
        end_t = clock();
        clock_t total_t_ma = (end_t - start_t) ;
        s2 += total_t_ma;

        }
        if(i<20){
        for(int run =0; run<6;run++){
        A_shape(A,size-run);
        start_t = clock();
        quick_sort(A, size-run);
        end_t = clock();
        clock_t  total_t_qa = (end_t - start_t);
        s3 += total_t_qa;
        }}
        for(int run =0; run<6;run++){
        V_shape(A,size-run);
        start_t = clock();
        heap_sort(A,size-run);
        end_t = clock();
        clock_t  total_t_hv = (end_t - start_t);
        s4 += total_t_hv;
        }
        for(int run =0; run<6;run++){
        V_shape(A,size-run);
        start_t = clock();
        merge_sort(A, size- run);
        end_t = clock();
        clock_t total_t_mv = (end_t - start_t);
        s5 += total_t_mv;
         }
        if(i<100){
        for(int run =0; run<6;run++){
        V_shape(A,size- run);
        start_t = clock();
        quicksort(A, 0, size - 1- run);
        end_t = clock();
        clock_t  total_t_qv = (end_t - start_t);
        s6 += total_t_qv;
        }}
        delete []A;

        file << size <<  ";" <<s1/6<<";" <<s2/6<< ";" << s3/6<<";" <<s4/6<<";" <<s5/6<< ";" << s6/6<< ";\n";
        printf("%d;%0.4f;%0.4f;%0.4f;%0.4f;%0.4f;%0.4f;\n",size,((double) s1)/6.0,((double)s2)/6.0,((double)s3)/6.0,((double)s4)/6.0,((double)s5)/6.0,((double)s6)/6.0);

}
    file.close();
    return 0;
}
