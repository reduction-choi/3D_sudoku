#include<stdio.h>
#define SIZE 6
#define BOX_H 2
#define BOX_W 3

#define Q 1
#define B 2
#define N 3
#define K 4
#define P 5
#define R 6

using namespace std;

int sudoku[SIZE][SIZE];
int cnt;
char int_to_piece(int piece){
    char chess_piece[7]={'?','Q','B','N','K','P','R'};
    return chess_piece[piece];
}
bool check_col(int x, int y){
    for (int i = 0; i < SIZE ; i++)
    {
        if(i != x && sudoku[i][y] != 0 && sudoku[i][y] == sudoku[x][y]){
            return false;
        }
    }
    return true;
}
bool check_row(int x, int y){
    for(int i = 0; i < SIZE ; i++)
    {
        if(i != y && sudoku[x][i] != 0 && sudoku[x][i] == sudoku[x][y]){
            return false;
        }
    }
    return true;
}
bool check_piece(int x, int y, int piece){
    if(piece == Q || piece == B){
        int dir[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
        for(int d=0 ; d<4 ; d++){
            for(int i=1 ; i<SIZE ; i++){
                if(x+i*dir[d][0] >= 0 && x+i*dir[d][0] < SIZE && y+i*dir[d][1] >=0 && y+i*dir[d][1] < SIZE && sudoku[x+i*dir[d][0]][y+i*dir[d][1]] == piece){
                    return false;
                }
            }
        }
    }
    else if(piece == N){
        int dir[8][2] = {{2,1},{2,-1},{1,2},{1,-2},{-1,2},{-1,-2},{-2,1},{-2,-1}};
        for(int d=0 ; d<8 ; d++){
            if(x+dir[d][0] >= 0 && x+dir[d][0] < SIZE && y+dir[d][1] >=0 && y+dir[d][1] < SIZE && sudoku[x+dir[d][0]][y+dir[d][1]] == piece){
                return false;
            }
        }
    }
    else if(piece == K || piece == P){ //분기점 2: Pawn은 제외
        int dir[4][2] = {{-1,1},{-1,-1},{1,1},{1,-1}};
        for(int d=0 ; d<4 ; d++){
            if(x+dir[d][0] >= 0 && x+dir[d][0] < SIZE && y+dir[d][1] >=0 && y+dir[d][1] < SIZE && sudoku[x+dir[d][0]][y+dir[d][1]] == piece){
                return false;
            }
        }
    }
    return true;
}
bool check_box(int x, int y){//분기점 1: box조건 무시
    int box_x = (x/BOX_H)*BOX_H;
    int box_y = (y/BOX_W)*BOX_W;
    for(int i=0 ; i<BOX_H ; i++){
        for(int j=0 ; j<BOX_W ; j++){
            int xx = box_x + i;
            int yy = box_y + j;
            if(!(x == xx && y == yy) && sudoku[xx][yy] != 0 && sudoku[xx][yy] == sudoku[x][y])
                return false;
        }
    }
    return true;
}
bool check(int x, int y, int piece){
    return check_col(x,y) & check_row(x,y) & check_box(x,y) & check_piece(x,y,piece);
}
void print(){
    printf("-----solution %d-----\n", cnt);
    for(int i=0 ; i<SIZE ; i++){
        for(int j=0 ; j<SIZE ; j++){
            printf("%c ", int_to_piece(sudoku[i][j]));
        }
        printf("\n");
    }
}
void solve(int x, int y){
    if(x>=SIZE){
        cnt++;
        print();
        return;
    }
    if(sudoku[x][y] != 0){
        if(y+1 >= SIZE){
            solve(x+1,0);
        }
        else{
            solve(x,y+1);
        }
        return;
    }
    for(int i=1 ; i<=6 ; i++){
        sudoku[x][y] = i;
        if(check(x,y,i)){
            if(y+1 >= SIZE){
                solve(x+1,0);
            }
            else{
                solve(x,y+1);
            }
        }
        sudoku[x][y] = 0;
    }
}
int main(){
    for(int i=0 ; i<SIZE ; i++){
        for(int j=0 ; j<SIZE ; j++){
            scanf("%d", &sudoku[i][j]);
        }
    }
    solve(0,0);
    printf("%d solutions\n", cnt);
    return 0;
}