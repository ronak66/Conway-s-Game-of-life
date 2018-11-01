#include<iostream>
#include <fstream>
#include "GridCell.h"
#include "Grid.h"

using namespace std;

int main(){
    srand(time(NULL));
    int x,y,l;
    cin >> x >> y >> l;
    gridcell **grids = new gridcell*[x];
    for(int i=0;i<x;i++){
        grids[i] = new gridcell[y];
    }
    grid g(grids,x,y);
    if(l <= (x-2)*(y-2) && x > 0 && y > 0 && l > 0){
        g.generate_initial_state (l);
        cout << g << endl;
        g.update_neighborhood();
        int test=0;
        for(int i =0 ;i<5;i++){
            test = g.generate_next_state();
            if(test == 1) break;
            cout << g << endl;
        }
        cout << g << endl;
    }
    return 0;
}

// int main(){
//     srand(time(NULL));
//     ifstream infile;
// }
