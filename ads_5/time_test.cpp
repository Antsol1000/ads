#include <iostream>
#include <fstream>
#include <ctime>
#include <list>
#include "knapsack.hpp"

#define MP(a, b) std::make_pair(a, b)


int MAX_CAPA = 1000;
int STEP_CAP = 50;
int MAX_ITEMS = 1000;
int STEP_ITEM = 50;

int num_of_vectors = 1000;
int N = MAX_ITEMS / STEP_ITEM;
int S = MAX_CAPA / STEP_CAP;
//n s



int main(){
    double times[3][N][S];
    int r;
    int m;
    int sum = 0;
    time_t start ,end ;
    //READING
    std::list<std::list< std::vector<std::pair<int, int>>>> big_list;
    for(int n = STEP_ITEM; n <= MAX_ITEMS; n += STEP_ITEM){
        for(int s = STEP_CAP; s <= MAX_CAPA; s += STEP_CAP){
            std::list< std::vector<std::pair<int, int>>> lista;
            std::ifstream file;
            std::vector<std::pair<int, int>> items;

            char filename[25];
            snprintf(filename, 25, "gen-f/n_%d_s_%d.txt", n,s);
            std::cout<< filename<<" s : " <<s << " n: " <<n << std::endl;
            file.open(filename);

            for(int i =0; i<num_of_vectors; i++){
                sum = 0;
                for(int j =0; j<n; j++){
                        file >> r;
                        file >> m;
                        //std::cout<<"suma:"<<r+m<<std::endl;
                        items.push_back(MP(r,m));
                }

                lista.push_back(items);
                items.clear();
            }
            big_list.push_back(lista);
            file.close();
        }
    }
    int s = 0;int n = 0;
    int result;
/*
    for (auto lista: big_list){
            start = clock();

            for(auto v: lista){
                 result = dynamic_ks((s+1)*STEP_CAP, v);
            }
            end = clock();
            times[0][n][s] = (double) (end - start );
    std::cout<<"dw: "<<(s+1)*STEP_CAP<< " n:  "<< (n+1)*STEP_ITEM<< " t:"<<times[0][n][s]<<" r: "<<result<<std::endl;
    s++;
    if(s == S){n++; n = n % N;s=0;}
    s = s % S;

    }

    s = 0;n = 0;
    for (auto lista: big_list){
            start = clock();
            for(auto v: lista){
                 result = exhaustive_ks((s+1)*STEP_CAP, v);
            }
            end = clock();
            times[1][n][s] = (double) (end - start );
    std::cout<<"ew: "<<(s+1)*STEP_CAP<< " n:  "<< (n+1)*STEP_ITEM<< " t:"<<times[1][n][s]<<" r: "<<result<<std::endl;
    s++;
    if(s == S){n++; n = n % N;s=0;}
    s = s % S;
    }
    */
    s = 0;n = 0;
    for (auto lista: big_list){
            start = clock();
            for(auto v: lista){
                 result = greedy_ks((s+1)*STEP_CAP, v);
            }
            end = clock();
            times[0][n][s] = (end - start );
    std::cout<<"gw: "<<(s+1)*STEP_CAP<< " n:  "<< (n+1)*STEP_ITEM<< " t:"<<times[0][n][s]<<" r: "<<result<<std::endl;
    s++;
    if(s == S){n++;n = n%N;s=0;}
    s = s % S;

    }


    //WRITING
    std::string filenames[1] = {"results_g.csv"};
    std::ofstream file;;
    for (int i =0; i<1; i++){
            file.open(filenames[i]);
            for( int s = 0; s<S;s++){
                    file<<";"<<(s+1)*STEP_CAP;
            }
            file<<std::endl;
            for( int n = 0; n<N;n++){
                    file<<(n+1)*STEP_ITEM<<";";
                for( int s = 0; s<S;s++){
                    file<<times[i][n][s]<<";";
            }
            file<<std::endl;

            }
            file.close();

    }


    return 0;}
