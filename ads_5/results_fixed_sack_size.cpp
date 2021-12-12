#include <iostream>
#include <fstream>
#include <ctime>
#include <list>
#include "knapsack.hpp"

#define MP(a, b) std::make_pair(a, b)


float MAX_CAPA = 1000;
float STEP_CAP =  100;
int MAX_ITEMS = 1000;
int STEP_ITEM = 100;
int num_of_vectors = 50;
int N = MAX_ITEMS / STEP_ITEM;
int S = MAX_CAPA / STEP_CAP;
//n s



int main(){
    double results[3][N][S][num_of_vectors];
    double res_fin[N][S] = {0};
    int r;int m;int sum;int ss;
    //READING
    int array_of_sums[N][S][num_of_vectors+1];
    std::list<std::list< std::vector<std::pair<int, int>>>> big_list;
    for(int n = 0; n < N ; n++){
        for(int s = 0; s < S; s++){
            std::list< std::vector<std::pair<int, int>>> lista;
            std::ifstream file;
            std::vector<std::pair<int, int>> items;

            char filename[25];
            snprintf(filename, 25, "gen-f/n_%d_s_%d.txt", (n+1)*STEP_ITEM,(int)((s+1)*STEP_CAP));
            std::cout<< filename<<std::endl;;
            file.open(filename);
            for(int i =0; i<num_of_vectors; i++){
                sum = 0;
                for(int j =0; j<(n+1)*STEP_ITEM; j++){
                        file >> r;
                        file >> m;
                        sum+=m;
                        items.push_back(MP(r, m));
                }
                array_of_sums[n][s][i] = sum;
                //std::cout<<s<<" "<<n<<" "<<array_of_sums[n][s][i]<<" "<<sum<<std::endl;
                lista.push_back(items);
                items.clear();
            }
            big_list.push_back(lista);
            file.close();
        //std::cout<<" sum "<< sum<< std::endl;
        }
    }

    int result;
    int n = 0;int s = 0;
    /*
    for (auto lista: big_list){

            int i = 0;
            int w = 0;
            std::cout<<s<<" "<<n<<" "<<array_of_sums[n][s][i]<<std::endl;
            for(auto v: lista){
                 results[0][n][s][i] = (double) dynamic_ks(MAX_CAPA, v);
                 //std::cout<< dynamic_ks(array_of_sums[n][s][i] * (s+1)*STEP_CAP, v)<<" ";
                 i++;
            }
    std::cout<<(s+1)*STEP_CAP<<" dynamic capacity: "<<array_of_sums[n][s][i-1] * (s+1) * STEP_CAP<< "   items:  "<< (n+1)*STEP_ITEM<<std::endl;
    s++;
    if(s == S){n = n % N;n++; s = 0;}
    }

    s = 0;n = 0;(
    for (auto lista: *big_list){
            start = clock();
            for(auto v: lista){
                 result = exhaustive_ks((s+1)*STEP_CAP, v);
            }
            end = clock();
            times[1][n][s] = (double) (end - start );
    std::cout<<"exhaustive capacity: "<<(s+1)*STEP_CAP<< "   items:  "<< (n+1)*STEP_ITEM<< "  time:  "<<times[1][n][s]<<std::endl;
    s++;
    if(s == S){n++;n = n%N;}
    s = s % S;

    }
*/
double pom;
    s = 0;n = 0;
    int l;
    for (auto lista: big_list){
            int i = 0;
            int w=0;

            for(auto v: lista){
                w =greedy_ks(STEP_CAP*(s+1)*100, v);l=dynamic_ks(STEP_CAP*(s+1)*100, v);
                 pom = (double)((double)w/(double)l);
                 res_fin[n][s] += pom;
                 //std::cout<<"n:"<<n<<" s:"<<s<<" res:"<<w<<" "<<l<<" p: "<<pom<<" | "<<std::endl;
                 i++;

            }
    std::cout<<" greedy capacity: "<<(s+1)*STEP_CAP<< "   items:  "<< (n+1)*STEP_ITEM<< "  result:  "<<(double)res_fin[n][s]/num_of_vectors<<std::endl;
    //std::cout<<std::endl;

    s++;
    if(s == S){n = n % N;n++; s = 0;}
    }


    //WRITING
    std::string filenames[1] = {"new_results_500-1000.csv"};
    std::ofstream file;;
    for (int i =0; i<3; i++){

            file.open(filenames[i]);
            for( int s = 0; s<S;s++){
                    file<<";"<<(s+1)*STEP_CAP;
            }
            file<<std::endl;
            for( int n = 0; n<N;n++){
                    file<<(n + 1)*STEP_ITEM;
                for( int s = 0; s<S;s++){
                    file<<";"<<res_fin[n][s]/(double) num_of_vectors;
            }

            file<<std::endl;
            }
            file.close();

    }


    return 0;}
