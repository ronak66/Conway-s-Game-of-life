#include<iostream>
#include "GridCell.h"
using namespace std;


// Constructor and Destructor
gridcell::gridcell(int x, int y): x(x), y(y) {

}
// copy constructor
gridcell::gridcell(gridcell& old_cell){
    x = old_cell.x;
    y = old_cell.y;
    state = old_cell.get_state();
    // unsigned char *a = old_cell.get_neighborhood();
    for(int i=0;i<8;i++){
        neighborhood[i] = old_cell.neighborhood[i];
    }
}
// overloading equall operator
void gridcell::operator=(gridcell& old_cell){
    x = old_cell.x; 
    y = old_cell.y;
    state = old_cell.get_state();
    // unsigned char *a = old_cell.get_neighborhood();
    for(int i=0;i<8;i++){
        neighborhood[i] = old_cell.neighborhood[i];
    }
}
gridcell::~gridcell(){

}

// Definations of all the methods of the class
int gridcell::count_live_neighbors(){

    int count=0;
    for(int i=0;i<8;i++){
        if(neighborhood[i] == '1') count++;
    }
    return count;
}

//Frind function
ostream& operator<< (ostream & os, gridcell & cell){
    if(cell.state == '0') os << "o ";
    else os << "+ ";
}
