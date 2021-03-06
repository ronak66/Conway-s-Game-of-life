#include <iostream>
#include "GridCell.h"

#ifndef GRID_HEADER
#define GRID_HEADER

class grid{
    private:
        gridcell **grids;
        int num_rows;
        int num_colums;

        //---
        int Gx;
        int Gy;
        unsigned char Gstate;
        unsigned char Gneighborhood[8];

    public:

        // constructor and destructor
        grid(gridcell **grids, int num_rows,int num_colums,int Gx,int Gy);
        grid(){}
        // Copy constructor
        grid(grid&);
        void operator=(grid& );
        ~grid();

        // Class methods
        void generate_initial_state(int );
        void update_neighborhood();
        void print_grid();
        int generate_next_state();
        int valid_grid_check();
        //---
        int Gcount_live_neighbors();
        void make_live();
        void make_dead();
        int count_live_cells();

        // Getters
        gridcell get_cell(int i,int j){
            return grids[i][j];
        }
        int get_num_rows(){return num_rows;}
        int get_num_colums(){return num_colums;}
        //---
        unsigned char get_Gstate(){
            return Gstate;
        }
        int get_Gx(){return Gx;}
        int get_Gy(){return Gy;}
        unsigned char *get_Gneighborhood(){
            return Gneighborhood;
        }

        //Setters
        void set_num_rows(int a){num_rows=a;}
        void set_num_colums(int a){num_colums=a;}
        void set_grids(gridcell **a,int num_rows,int num_colums);
        //---
        void set_Gstate(unsigned char ch){
            Gstate = ch;
        }
        void set_Gx(int x1){Gx = x1;}
        void set_Gy(int y1){Gy = y1;}
        void set_Gneighborhood(int i,unsigned char a){
            Gneighborhood[i] = a;
        }


    friend std::ostream& operator<< (std::ostream &, grid &);

};
#endif
