#include <iostream>
#include "Grid.h"
#include "GridCell.h"

#ifndef MULTIVERSE_HEADER
#define MULTIVERSE_HEADER

class multiverse{
    private:
        grid **multiverses;
        int Mnum_rows;
        int Mnum_colums;

    public:

        //constructor and destructor
        multiverse(grid **multiverses,int Mnum_rows,int Mnum_colums,int Gnum_rows,int Gnum_colums);
        //copy constructor
        multiverse(multiverse&);
        ~multiverse();
        void operator=(multiverse& );

        //class methods
        void Mupdate_neighborhood();
        void print_multiverse();
        int Mgenerate_next_state();
        int valid_multiverse_check();
        void initial_state();
        void kth_gen_grid(int k);

        // Getters
        grid get_grid(int i,int j){
            return multiverses[i][j];
        }
        int get_Mnum_rows(){return Mnum_rows;}
        int get_Mnum_colums(){return Mnum_colums;}

        //Setters
        void set_Mnum_rows(int a){Mnum_rows=a;}
        void set_Mnum_colums(int a){Mnum_colums=a;}
};
#endif
