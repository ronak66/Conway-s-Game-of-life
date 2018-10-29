#include <iostream>

#ifndef GRIDCELL_HEADER
#define GRIDCELL_HEADER

class gridcell{
    private:
        int x;
        int y;
        unsigned char state;
        unsigned char neighborhood[8];

    public:
        gridcell(int x,int y);
        gridcell(){}
        // Getters
        void set_state(unsigned char ch){
            state = ch;
        }
        void set_x(int x1){x = x1;}
        void set_y(int y1){x = y1;}
        void set_neighborhood(int i,unsigned char a){
            neighborhood[i] = a;
        }

        //Setters
        unsigned char get_state(){
            return state;
        }
        int get_x(){return x;}
        int get_y(){return y;}
        unsigned char *get_neighborhood(){
            return neighborhood;
        }
        int count_live_neighbors();

    friend std::ostream& operator<< (std::ostream &, gridcell &);


};
#endif
