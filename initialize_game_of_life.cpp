#include<iostream>
#include <fstream>
#include<sstream>
#include<string>
#include<vector>
#include<bits/stdc++.h>
#include "GridCell.h"
#include "Grid.h"

using namespace std;


// int main(){
//     srand(time(NULL));
//     int x,y,l;
//     cin >> x >> y >> l;
//     gridcell **grids = new gridcell*[x];
//     for(int i=0;i<x;i++){
//         grids[i] = new gridcell[y];
//     }
//     grid g(grids,x,y);
//     if(l <= (x-2)*(y-2) && x > 0 && y > 0 && l > 0){
//         g.generate_initial_state (l);
//         cout << g << endl;
//         g.update_neighborhood();
//         int test=0;
//         for(int i =0 ;i<5;i++){
//             test = g.generate_next_state();
//             if(test == 1) break;
//             cout << g << endl;
//         }
//         cout << g << endl;
//     }
//     return 0;
// }

int main(){
    srand(time(NULL));
    ifstream input_file("input.txt");
    if(input_file.is_open()){
        string line;
        getline(input_file,line);
        stringstream s(line);
        vector<string> in;
        string word;
        while(s >> word){
            in.push_back(word);
        }

        int nRows,nColums,nGen;
        nRows = stoi(in[0]);
        nColums = stoi(in[1]);
        nGen = stoi(in[2]);
        gridcell **grids = new gridcell*[nRows];
        for(int i=0;i<nRows;i++){
            grids[i] = new gridcell[nColums];
        }
        int i=0;
        while(getline(input_file,line)){
            int j=0;
            for(int k=0;k<line.size();k+=2){
                // if(line[j] == ' ');
                if(line[k] == 'o') grids[i][j].set_state((unsigned char)'0');
                else if(line[k] == '+') grids[i][j].set_state((unsigned char)'1');
                j++;
            }
            i++;
        }
        grid g(grids,nRows,nColums);
        g.update_neighborhood();
        int test=0;
        cout << g << endl;
        for(i=0;i<nGen;i++){
            test = g.generate_next_state();
            if(test == 1) break;
            cout << g << endl;
        }
        cout << g << endl;

    }
    else cout << "Unable to open file" << endl;
    return 0;
}
