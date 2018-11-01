#include<iostream>
#include "GridCell.h"
#include "Grid.h"

using namespace std;

// Constructor and Destructor
grid::grid(gridcell **grids,int num_rows,int num_colums):grids(grids),num_rows(num_rows),num_colums(num_colums){
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<num_colums;j++){
            grids[i][j].set_x(i);
            grids[i][j].set_y(j);
        }
    }
}
// copy constructor
grid::grid(grid& old_grid){
    num_rows = old_grid.num_rows;
    num_colums = old_grid.num_colums;
    grids = new gridcell*[num_rows];
    for(int i=0;i<num_rows;i++){
        grids[i] = new gridcell[num_colums];
    }
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<num_colums;j++){
            grids[i][j] = old_grid.grids[i][j];
        }
    }
}
// Overloding equall operator
void grid::operator=(grid& old_grid){
    num_rows = old_grid.num_rows;
    num_colums = old_grid.num_colums;
    grids = new gridcell*[num_rows];
    for(int i=0;i<num_rows;i++){
        grids[i] = new gridcell[num_colums];
    }
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<num_colums;j++){
            grids[i][j] = old_grid.grids[i][j];
        }
    }
}
grid::~grid(){
    for(int i=0;i<num_rows;i++) delete[] grids[i];
    delete[] grids;
}

// Getters and setters
void grid::set_grids(gridcell **a,int num_rows,int num_colums){
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<num_colums;j++){
            grids[i][j].set_x(i);
            grids[i][j].set_y(j);
        }
    }
}


// Definations of all the methods of the class
void grid::generate_initial_state (int live_cells){
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<num_colums;j++){
            grids[i][j].set_state('0');
        }
    }
    for(int i=0;i<live_cells;i++){
        int x = (((int)rand())%(num_rows-2)) + 1;
        int y = (((int)rand())%(num_colums-2)) + 1;
        grids[x][y].set_state('1');
    }
}

void grid::update_neighborhood(){
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<num_colums;j++){
            int number = 0;
            for(int p=i-1;p<=i+1;p++){
                for(int q=j-1;q<=j+1;q++){
                    if(!(p==i && q==j)){
                        if(p<num_rows && q<num_colums && p>=0 && q>=0)
                            grids[i][j].set_neighborhood(number, grids[p][q].get_state());
                        else
                            grids[i][j].set_neighborhood(number,'x');
                        number++;
                    }
                }
            }
        }
    }
}

void grid::print_grid(){
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<num_colums;j++){
            if(grids[i][j].get_state() == '1') printf("+ ");
            else printf("o ");
        }
        printf("\n");
    }
}

int grid::generate_next_state(){
    int flag = 0;
    grid copied_g = *this;
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<num_colums;j++){
            unsigned char *neighborhood = grids[i][j].get_neighborhood();
            int count = 0;
            for(int k=0;k<8;k++){
                if(neighborhood[k] == '1') count ++;
            }
            unsigned char cell_state = grids[i][j].get_state();
            if(cell_state == '1'){
                if(count < 2) grids[i][j].set_state('0');
                else if(count > 3)  grids[i][j].set_state('0');
            }
            else{
                if(count == 3) grids[i][j].set_state('1');
            }
            if(i == 0 || j == 0 || i == num_rows-1 || j == num_colums-1){
                if(grids[i][j].get_state() == '1'){
                    flag = 1;
                    cout << "Invalid generation" << endl;
                    break;
                }
            }
        }
        if(flag  == 1) break;
    }
    if(flag == 0){
        update_neighborhood();
        return 0;
    }
    else{
        *this = copied_g;
        return 1;
    }
}

int grid::valid_grid_check(){
    int i=0,j;
    int flag = 0;
    for( j=0;j<num_colums;j++){
        if(grids[i][j].get_state() == '1'){
            flag = 1;
            break;
        }
    }
    if(flag == 1) return 0;
    i = num_rows-1;
    for(j=0;j<num_colums;j++){
        if(grids[i][j].get_state() == '1'){
            flag = 1;
            break;
        }
    }
    if(flag == 1) return 0;
    j = 0;
    for( i=0;i<num_rows-1;i++){
        if(grids[i][j].get_state() == '1'){
            flag = 1;
            break;
        }
    }
    if(flag == 1) return 0;
    j = num_colums-1;
    for( i=0;i<num_rows-1;i++){
        if(grids[i][j].get_state() == '1'){
            flag = 1;
            break;
        }
    }
    if(flag == 1) return 0;
    return 1;
}


// Friend function
ostream& operator<< (ostream & os, grid & g){
    for(int i=0;i<g.num_rows;i++){
        for(int j=0;j<g.num_colums;j++){
            os << g.grids[i][j];
        }
        os << endl;
    }
    return os;
}
