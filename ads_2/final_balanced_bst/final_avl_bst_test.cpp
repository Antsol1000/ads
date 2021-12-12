#include<fstream>
#include<iostream>
#include<ctime>
#include<string>
#include<algorithm>
#include"../headers/tree.hpp"

const int SIZE_STEP = 5000;
const int MAX_SIZE = 300000;
const int NUM_OF_TESTS = MAX_SIZE / SIZE_STEP;

double average_array(double arr[], int len){
	double sum = 0;
	int i=0;
	while(i<len){
		sum+=(double) arr[i];
		i++;
	}
	return (double)sum/(double)len;
}

int main() {
    srand(time(0));
    int h;
    // open file with results of trials
    std::ofstream wyniki;
    wyniki.open("AVL_individual.csv");
   wyniki << "test_number;number_of_records;height;add_time;search_time;remove_time" << std::endl;
    int runs = 10;
	double time_array[3][runs];

    for (int test_number = 1; test_number <= NUM_OF_TESTS; test_number++) {

        // create an ARRAY with records from data file
        int SIZE = SIZE_STEP * test_number;
        std::string *ARRAY = new std::string[SIZE];
        std::ifstream file;
        file.open("..//data_2.csv");
        for (int i = 0; i < SIZE; i++) {
            file >> ARRAY[i];
        }
        file.close();
        for(int run=0; run<runs;run++){
        // create data structure
        BalancedBST tree;
        clock_t start_t, end_t;

        // add all elements and measure time

        std::random_shuffle(ARRAY, ARRAY + SIZE);
        for (int i = 0; i < SIZE - 5000; i++) {
            tree.insert(new Student(ARRAY[i].substr(8, 12), ARRAY[i].substr(21, 12), std::stoi(ARRAY[i].substr(0, 7))));
        }
        start_t = clock();
        for (int i = SIZE - 5000; i < SIZE; i++) {
            tree.insert(new Student(ARRAY[i].substr(8, 12), ARRAY[i].substr(21, 12), std::stoi(ARRAY[i].substr(0, 7))));
        }
        end_t = clock();
        time_array[0][run] = (double) (end_t - start_t);


        h = tree.print_height();

        // shuffle the array and measure time of finding elements
        std::random_shuffle(ARRAY, ARRAY + SIZE);

        for (int i = 0; i < SIZE -5000; i++) {
            tree.find(std::stoi(ARRAY[i].substr(0, 7)));
        }
        start_t = clock();
        for (int i = SIZE -5000; i < SIZE; i++) {
            tree.find(std::stoi(ARRAY[i].substr(0, 7)));
        }
        end_t = clock();
        time_array[1][run] = (double) (end_t - start_t);



        // shuffle the array and measure time of removing elements
        std::random_shuffle(ARRAY, ARRAY + SIZE);

        for (int i = 0; i < SIZE-5000; i++) {
            tree.remove(std::stoi(ARRAY[i].substr(0, 7)));
        }
        start_t = clock();
        for (int i = SIZE-5000; i < SIZE; i++) {
            tree.remove(std::stoi(ARRAY[i].substr(0, 7)));
        }
        end_t = clock();
        time_array[2][run] = (double) (end_t - start_t);



        // delete data structure and ARRAY with records
        }
        delete []ARRAY;

        // print results to the file
        wyniki << test_number  << ";" << SIZE << ";" <<h<<";"<< average_array(time_array[0],runs) << ";" << average_array(time_array[1],runs) << ";" << average_array(time_array[2],runs) << std::endl;

        std::cout << "test nr" << test_number <<"wysokosc : "<<h<< "  " << SIZE << "   " << average_array(time_array[0],runs) << "   " << average_array(time_array[1],runs) << "   " << average_array(time_array[2],runs) << std::endl;
    }

    // close results file
    wyniki.close();

    return 0;
}
