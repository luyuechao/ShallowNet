#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "mlp.h"


int main(int argc, char **argv){
    const int sample_num = 16; // number of test data
    const int input_size = 4;   // input_size (dimension) of input vector
    // number of labels
    const int label = 2;
    
    // create MLP(input: 4, hidden: 3, output: 2)
    mlp net(input_size, 3, label);
  
    // train data
    float train_set[input_size * sample_num];
    // label data
    int teacher[sample_num];
    
    // load CSV
    string inputFile = (argc > 1) ? argv[1]: "sample.csv";
    FILE *fp = fopen(inputFile.c_str(), "r");
   
    if(fp==NULL) { return -1; }
    
    for(int i = 0; i < sample_num; i++){
        // load data
        for(int j = 0; j < input_size; j++) 
         { fscanf(fp, "%f,", train_set + input_size * i + j);}
        
        // load label
        fscanf(fp, "%d,", teacher + i);
 
    }
   
    // train MLP
    // repeat time is your choice
    cout << "Please input iteration steps:"<< endl;
     
    int iteration;
    cin >> iteration;
    const float eta = 0.1; // learning rate
    net.train(train_set, teacher, sample_num, iteration, eta);
    // show the result
    
    cout << endl << "Let's test trained neural network!"<< endl;
    cout << "Input   |  Output" << endl;
    for(int i = 0; i < sample_num; i++){

        for(int j = 0; j < input_size; j++)
        { cout << train_set[input_size * i + j] << " ";}
        cout << "->    ";
        cout << net.predict(train_set + input_size * i) << endl;
    }
    
    // save and load etrain_setample
    /*
    net.save("data.csv");
    mlp net2("data.csv");
    for(int i=0; i<sample_num; i++){
        cout << net2.predict(train_set+input_size*i) << endl;
    }
    */
    return 0;
}
