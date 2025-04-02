#include<stdio.h>
#define SIZE 6
using namespace std;

int sudoku[SIZE][SIZE][SIZE];
int cnt;

bool check_x(int z, int x, int y){
    for (int i = 0; i < SIZE ; i++)
    {
        if(i != x && sudoku[z][i][y] != 0 && sudoku[z][i][y] == sudoku[z][x][y]){
            return false;
        }
    }
    return true;
}
bool check_y(int z, int x, int y){
    for (int i = 0; i < SIZE ; i++)
    {
        if(i != y && sudoku[z][x][i] != 0 && sudoku[z][x][i] == sudoku[z][x][y]){
            return false;
        }
    }
    return true;
}
bool check_z(int z, int x, int y){
    for (int i = 0; i < SIZE ; i++)
    {
        if(i != z && sudoku[i][x][y] != 0 && sudoku[i][x][y] == sudoku[z][x][y]){
            return false;
        }
    }
    return true;
}
bool check_box(int z, int x, int y){
    int box_x = (x/2)*2;
    int box_y = (y/3)*3;
    for(int i=0 ; i<2 ; i++){
        for(int j=0 ; j<3 ; j++){
            int xx = box_x + i;
            int yy = box_y + j;
            if(!(x == xx && y == yy) && sudoku[z][xx][yy] != 0 && sudoku[z][xx][yy] == sudoku[z][x][y])
                return false;
        }
    }
    return true;
}
bool is_on_diagonal(int z, int x, int y, bool *x_rev, bool *y_rev){
    if(x==y && y==z){
        *x_rev = false;
        *y_rev = false;
        return true;
    }
    else if(x==y && x+z == SIZE - 1){
        *x_rev = true;
        *y_rev = true;
        return true;
    }
    else if(x==z && y+z == SIZE - 1){
        *x_rev = false;
        *y_rev = true;
        return true;
    }
    else if(y==z && x+z == SIZE - 1){
        *x_rev = true;
        *y_rev = false;
        return true;
    }
    else
        return false;
}
int diag_idx(bool rev, int i){
    return rev * (SIZE-1) - rev * 2* i + i;
}
bool check_diagonal(int z, int x, int y){
    bool x_reverse;
    bool y_reverse;
    if(!is_on_diagonal(z, x, y, &x_reverse, &y_reverse)){
        return true;
    }
    for(int i=0 ; i<SIZE ; i++){
        if(i != z && sudoku[i][diag_idx(x_reverse, i)][diag_idx(y_reverse, i)] != 0 && sudoku[i][diag_idx(x_reverse, i)][diag_idx(y_reverse, i)] == sudoku[z][x][y]){
            return false;
        }
    }
    return true;
}
bool check(int z, int x, int y){
    // printf("checking...\n");
    // printf("x: %d", check_x(z, x, y));
    // printf("y: %d", check_y(z, x, y));
    // printf("z: %d", check_z(z, x, y));
    // printf("diag: %d\n", check_diagonal(z, x, y));
    
    return check_x(z,x,y) & check_y(z,x,y) & check_z(z,x,y) & check_diagonal(z,x,y) & check_box(z,x,y);
}
void print(){
    printf("-----solution %d-----\n", cnt);
    for(int i=0 ; i<SIZE ; i++){
        for(int j=0 ; j<SIZE ; j++){
            for(int k=0 ; k<SIZE ; k++){
                printf("%d ", sudoku[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
void solve(int z, int x, int y){
    if(z>=SIZE){
        cnt++;
        print();
        return;
    }
    if(sudoku[z][x][y] != 0){
        int next_y = y+1;
        int next_x = x;
        int next_z = z;
        if(next_y >= SIZE){
            next_x++;
            next_y = 0;
        }
        if(next_x >= SIZE){
            next_z++;
            next_x = 0;
        }
        solve(next_z, next_x, next_y);
        return;
    }
    for(int i=1 ; i<=SIZE ; i++){
        sudoku[z][x][y] = i;
        if(!check(z,x,y)){
            sudoku[z][x][y] = 0;
            continue;
        }
        else{
            int next_y = y+1;
            int next_x = x;
            int next_z = z;
            if(next_y >= SIZE){
                next_x++;
                next_y = 0;
            }
            if(next_x >= SIZE){
                next_z++;
                next_x = 0;
            }
            solve(next_z, next_x, next_y);
            sudoku[z][x][y] = 0;
        }
    }
}
int main(){
    for(int i=0 ; i<SIZE ; i++){
        for(int j=0 ; j<SIZE ; j++){
            for(int k=0 ; k<SIZE ; k++){
                scanf("%d", &sudoku[i][j][k]);
            }
        }
    }
    solve(0,0,0);
    printf("%d solutions\n", cnt);
    return 0;
}