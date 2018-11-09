#include<iostream>
#include "GridCell.h"
#include "Grid.h"
#include "Multiverse.h"

using namespace std;

// Constructor and Destructor
multiverse::multiverse(grid **multiverses,int Mnum_rows,int Mnum_colums,int Gnum_rows,int Gnum_colums):multiverses(multiverses),Mnum_rows(Mnum_rows),Mnum_colums(Mnum_colums){
    for(int i=0;i<Mnum_rows;i++){
        for(int j=0;j<Mnum_colums;j++){
            gridcell **eachGrid = new gridcell*[Gnum_rows];
            for(int i=0;i<Gnum_rows;i++){
                eachGrid[i] = new gridcell[Gnum_colums];
            }
            multiverses[i][j].set_grids(eachGrid,Gnum_rows,Gnum_colums);
        }
    }
}
// copy constructor
multiverse::multiverse(multiverse& old_multiverse){
    Mnum_rows = old_multiverse.Mnum_rows;
    Mnum_colums = old_multiverse.Mnum_colums;
    multiverses = new grid*[Mnum_rows];
    for(int i=0;i<Mnum_rows;i++){
        multiverses[i] = new grid[Mnum_colums];
    }
    for(int i=0;i<Mnum_rows;i++){
        for(int j=0;j<Mnum_colums;j++){
            multiverses[i][j] = old_multiverse.multiverses[i][j];
        }
    }
}
// Overloding equall operator
void multiverse::operator=(multiverse& old_multiverse){
    Mnum_rows = old_multiverse.Mnum_rows;
    Mnum_colums = old_multiverse.Mnum_colums;
    multiverses = new grid*[Mnum_rows];
    for(int i=0;i<Mnum_rows;i++){
        multiverses[i] = new grid[Mnum_colums];
    }
    for(int i=0;i<Mnum_rows;i++){
        for(int j=0;j<Mnum_colums;j++){
            multiverses[i][j] = old_multiverse.multiverses[i][j];
        }
    }
}
multiverse::~multiverse(){
    for(int i=0;i<Mnum_rows;i++) delete[] multiverses[i];
    delete[] multiverses;
}



// Definations of all the methods of the class

void multiverse::Mupdate_neighborhood(){
    for(int i=0;i<Mnum_rows;i++){
        for(int j=0;j<Mnum_colums;j++){
            int number = 0;
            for(int p=i-1;p<=i+1;p++){
                for(int q=j-1;q<=j+1;q++){
                    if(!(p==i && q==j)){
                        if(p<Mnum_rows && q<Mnum_colums && p>=0 && q>=0)
                            multiverses[i][j].set_Gneighborhood(number, multiverses[p][q].get_Gstate());
                        else
                            multiverses[i][j].set_Gneighborhood(number,'x');
                        number++;
                    }
                }
            }
        }
    }
}

void multiverse::print_multiverse(){
    // for(int i=0;i<Mnum_rows;i++){
    //     for(int j=0;j<Mnum_colums;j++){
    //         cout << multiverses[i][j].get_Gstate() << " ";
    //         // cout << multiverses[i][j];
    //     }
    //     printf("\n");
    // }
    // cout << endl;

    for(int i=0;i<Mnum_rows;i++){
        int Gnum_rows = multiverses[0][0].get_num_rows();
        int Gnum_colums =  multiverses[0][0].get_num_colums();
        for(int p=0;p<Gnum_rows;p++){
            for(int j=0;j<Mnum_colums;j++){
                for(int q=0;q<Gnum_colums;q++){
                    if(multiverses[i][j].get_cell(p,q).get_state() == '1') cout << "+";
                    else cout << "o";
                }
                cout << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

int multiverse::Mgenerate_next_state(){
    int flag = 0;
    multiverse copied_m = *this;
    for(int i=0;i<Mnum_rows;i++){
        for(int j=0;j<Mnum_colums;j++){
            unsigned char *neighborhood = multiverses[i][j].get_Gneighborhood();
            int count = 0;
            for(int k=0;k<8;k++){
                if(neighborhood[k] == '1') count ++;
            }
            unsigned char cell_state = multiverses[i][j].get_Gstate();
            if(cell_state == '1'){
                if(count < 2 or count > 3) {multiverses[i][j].set_Gstate('0');multiverses[i][j].make_dead();}
                // else if(count > 3)  {multiverses[i][j].set_Gstate('0');multiverses[i][j].make_dead();}
            }
            else{
                if(count == 3) {multiverses[i][j].set_Gstate('1');multiverses[i][j].make_live();}
            }
            if(i == 0 || j == 0 || i == Mnum_rows-1 || j == Mnum_colums-1){
                if(multiverses[i][j].get_Gstate() == '1'){
                    flag = 1;
                    // cout << "Invalid generation" << endl;
                    break;
                }
            }
        }
        if(flag  == 1) break;
    }
    if(flag == 0){
        Mupdate_neighborhood();
        return 0;
    }
    else{
        *this = copied_m;
        return 1;
    }
}

int multiverse::valid_multiverse_check(){
    int i=0,j;
    int flag = 0;
    for( j=0;j<Mnum_colums;j++){
        if(multiverses[i][j].get_Gstate() == '1'){
            flag = 1;
            break;
        }
    }
    if(flag == 1) return 0;
    i = Mnum_rows-1;
    for(j=0;j<Mnum_colums;j++){
        if(multiverses[i][j].get_Gstate() == '1'){
            flag = 1;
            break;
        }
    }
    if(flag == 1) return 0;
    j = 0;
    for( i=0;i<Mnum_rows-1;i++){
        if(multiverses[i][j].get_Gstate() == '1'){
            flag = 1;
            break;
        }
    }
    if(flag == 1) return 0;
    j = Mnum_colums-1;
    for( i=0;i<Mnum_rows-1;i++){
        if(multiverses[i][j].get_Gstate() == '1'){
            flag = 1;
            break;
        }
    }
    if(flag == 1) return 0;
    return 1;
}


void multiverse::initial_state(){
    for(int i=0;i<Mnum_rows;i++){
        for(int j=0;j<Mnum_colums;j++){
            if(i == 0 or j == 0 or i == Mnum_rows-1 or j == Mnum_colums-1) {multiverses[i][j].set_Gstate('0');multiverses[i][j].make_dead();}
            else if(i%2 == 0){
                if(j%2 == 0) {multiverses[i][j].set_Gstate('1');multiverses[i][j].make_live();}
                else {multiverses[i][j].set_Gstate('0');multiverses[i][j].make_dead();}
            }
            else{
                if(j%2 == 0) {multiverses[i][j].set_Gstate('0');multiverses[i][j].make_dead();}
                else {multiverses[i][j].set_Gstate('1');multiverses[i][j].make_live();}
            }
        }
    }
    Mupdate_neighborhood();
}

void multiverse::kth_gen_grid(int k){

    multiverse copied_m = *this;
    for(int i=0;i<Mnum_rows;i++){
        for(int j=0;j<Mnum_colums;j++){
            int rol = k;
            while(rol){
                int t = multiverses[i][j].generate_next_state();
                if(t == 1) break;
                rol--;
            }
            int numLive_cells = multiverses[i][j].count_live_cells();
            int total_cell = multiverses[i][j].get_num_rows() *  multiverses[i][j].get_num_colums();
            // cout << multiverses[i][j].get_num_rows() <<" "<<  multiverses[i][j].get_num_colums() <<endl;
            if(((numLive_cells/total_cell))*100 < 55) multiverses[i][j].set_Gstate('0');
            else multiverses[i][j].set_Gstate('1');
        }
    }
    if(valid_multiverse_check() == 0) *this = copied_m;
}

// Friend function
// ostream& operator<< (ostream & os, multiverse & m){
//     for(int i=0;i<Mnum_rows;i++){
//         for(int j=0;j<Mnum_colums;j++){
//             os << multiverses[i][j];
//         }
//         os << endl;
//     }
//     return os;
// }
