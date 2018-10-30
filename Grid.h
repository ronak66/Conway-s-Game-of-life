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

        // constructor and destructor
        grid(gridcell **grids, int num_rows,int num_colums);
        ~grid();

        // Class methods
        void generate_initial_state(int l);
        void update_neighborhood();
        void print_grid();
        void generate_next_state();

        // Getters
        gridcell get_cell(int i,int j){
            return grids[i][j];
        }
        int get_num_rows(){return num_rows;}
        int get_num_colums(){return num_colums;}

        //Setters
        void set_num_rows(int a){num_rows=a;}
        void set_num_colums(int a){num_colums=a;}
        void set_grids(gridcell **a,int num_rows,int num_colums);


    friend std::ostream& operator<< (std::ostream &, grid &);

};
#endif
