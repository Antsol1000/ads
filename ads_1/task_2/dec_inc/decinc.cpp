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
    file << "size;HSd;MSd;QSd;HSa;MSa;QSa;";
    srand(time(0));
    for (int i = 1; i <= 200; i++) {
        clock_t start_t, end_t;
        int size = 5000*i;
        clock_t s1= 0;clock_t s2 = 0;
        clock_t s3 = 0;clock_t s4 = 0;
        clock_t s5 = 0;clock_t s6 = 0;

        for(int run =0; run<10;run++){
        int size = 5000*i + run;
        int *A = new int [size];
        desc_array(A,size);
        start_t = clock();
        heap_sort(A,size);
        end_t = clock();
        clock_t total_t_ha = (end_t - start_t);
        s1 += total_t_ha;


        desc_array(A,size);
        start_t = clock();
        merge_sort(A, size);
        end_t = clock();
        clock_t total_t_ma = (end_t - start_t) ;
        s2 += total_t_ma;


        desc_array(A,size);
        start_t = clock();
        quick_sort(A, size);
        end_t = clock();
        clock_t  total_t_qa = (end_t - start_t);
        s3 += total_t_qa;

        asc_array(A,size);
        start_t = clock();
        heap_sort(A,size);
        end_t = clock();
        clock_t  total_t_hv = (end_t - start_t);
        s4 += total_t_hv;

        asc_array(A,size);
        start_t = clock();
        merge_sort(A, size);
        end_t = clock();
        clock_t total_t_mv = (end_t - start_t);
        s5 += total_t_mv;


        asc_array(A,size);
        start_t = clock();
        quicksort(A, 0, size - 1);
        end_t = clock();
        clock_t  total_t_qv = (end_t - start_t);
        s6 += total_t_qv;

        delete []A;}

        file << size <<  ";" <<s1/10<<";" <<s2/10<< ";" << s3/10<<";" <<s4/10<<";" <<s5/10<< ";" << s6/10<< ";\n";
        printf("%d;%0.4f;%0.4f;%0.4f;%0.4f;%0.4f;%0.4f;\n",size,((double) s1)/5.0,((double)s2)/5.0,((double)s3)/5.0,((double)s4)/5.0,((double)s5)/5.0,((double)s6)/5.0);

}
    file.close();
    return 0;
}
