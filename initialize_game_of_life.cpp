#include<iostream>
#include "GridCell.h"
#include "Grid.h"

using namespace std;

int main(int argc, char *argv[]){
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
        cout << g;
        g.update_neighborhood();
    }
    int sum = 0;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            int count = grids[i][j].count_live_neighbors();
            sum += count;
        }
    }
    cout << sum << endl;
    for(int i =0 ;i<2;i++){
        g.generate_next_state();
        cout << g;
        cout << endl;
    }
}
