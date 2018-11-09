#include<iostream>
#include <fstream>
#include<sstream>
#include<string>
#include<vector>
#include<bits/stdc++.h>
#include "GridCell.h"
#include "Grid.h"
#include "Multiverse.h"
using namespace std;

int main(int argc, char *argv[]){
    int Mnum_rows = atoi(argv[1]);
    int Mnum_colums = atoi(argv[2]);
    int Gnum_colums = atoi(argv[4]);
    int Gnum_rows = atoi(argv[3]);
    int k = atoi(argv[5]);
    int s = atoi(argv[6]);
    grid **multiverses = new grid*[Mnum_rows];
    for(int i=0;i<Mnum_rows;i++){
        multiverses[i] = new grid[Mnum_colums];
    }
    multiverse m(multiverses,Mnum_rows,Mnum_colums,Gnum_rows,Gnum_colums);
        cout << "-----------------" <<endl;
    m.initial_state();
        cout << "-----------------" <<endl;
    m.print_multiverse();
    while(s){
        m.kth_gen_grid(k);
        m.Mgenerate_next_state();
        if(m.valid_multiverse_check() == 0) break;
        s--;
        // m.print_multiverse();
        // cout << "-----------------" <<endl;
    }

}
