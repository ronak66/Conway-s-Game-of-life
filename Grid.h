#include <iostream>
#include "GridCell.h"

#ifndef GRID_HEADER
#define GRID_HEADER

class grid{
    private:
        gridcell **grids;
        int num_rows;
        int num_colums;

    public:
        grid(gridcell **grids, int num_rows,int num_colums);
        void generate_initial_state(int l);
        void update_neighborhood();
        void print_grid();
        gridcell get_cell(int i,int j){
            return grids[i][j];
        }
        int get_num_rows(){return num_rows;}
        int get_num_colums(){return num_colums;}

    friend std::ostream& operator<< (std::ostream &, grid &);

};
#endif
