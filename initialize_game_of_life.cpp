#include<iostream>
#include "GridCell.h"
#include "Grid.h"

using namespace std;

gridcell::gridcell(int x, int y): x(x), y(y) {

}

grid::grid(gridcell **grids,int num_rows,int num_colums):grids(grids),num_rows(num_rows),num_colums(num_colums){
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<num_colums;j++){
            grids[i][j].set_x(i);
            grids[i][j].set_y(j);
        }
    }
}

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

int gridcell::count_live_neighbors(){

    int count=0;
    for(int i=0;i<8;i++){
        if(neighborhood[i] == '1') count++;
    }
    return count;
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

ostream& operator<< (ostream & os, gridcell & cell){
    if(cell.state == '0') os << "o ";
    else os << "+ ";
}

ostream& operator<< (ostream & os, grid & g){
    for(int i=0;i<g.num_rows;i++){
        for(int j=0;j<g.num_colums;j++){
            os << g.grids[i][j];
        }
        os << endl;
    }
    return os;
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    int x,y,l;
    cin >> x >> y >> l;
    gridcell **grids = new gridcell*[x];
    for(int i=0;i<x;i++){
        grids[i] = new gridcell[y];
    }
    if(l <= (x-2)*(y-2) && x > 0 && y > 0 && l > 0){
        grid g(grids,x,y);
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
}
