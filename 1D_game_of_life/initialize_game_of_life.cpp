#include<iostream>
#include <fstream>
#include<sstream>
#include<string>
#include<vector>
#include<bits/stdc++.h>
#include "GridCell.h"
#include "Grid.h"

using namespace std;

int main(int argc, char *argv[]){
    srand(time(NULL));
    int nGen = stoi(argv[2]);
    string filename = argv[1];
    ifstream input_file(filename);
    ofstream out_file("output.txt");
    if(input_file.is_open()){
        string line;
        getline(input_file,line);
        stringstream s(line);
        vector<string> in;
        string word;
        while(s >> word){
            in.push_back(word);
        }

        int nRows,nColums;
        nRows = stoi(in[0]);
        nColums = stoi(in[1]);
        int valid = stoi(in[2]);
        gridcell **grids = new gridcell*[nRows];
        for(int i=0;i<nRows;i++){
            grids[i] = new gridcell[nColums];
        }
        int i=0;
        while(getline(input_file,line)){
            int j=0;
            if(line[0] == 'e') break;
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
        if(test == 1 || nGen != 0) out_file << "0 0 0" << endl;
        else{
            out_file << g.get_num_rows() << " " << g.get_num_colums() << " " << nGen << endl;
            for(int i=0;i<g.get_num_rows();i++){
                for(int j=0;j<g.get_num_colums();j++){
                    if(g.get_cell(i,j).get_state() == '1') out_file << "+ ";
                    if(g.get_cell(i,j).get_state() == '0') out_file << "o ";
                }
                out_file << endl;
            }
        }
        out_file << "eof" << endl;
    }
    else cout << "Unable to open file" << endl;
    return 0;
}
