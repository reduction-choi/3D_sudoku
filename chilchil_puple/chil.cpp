#include<stdio.h>
int row[4][5] = {{1},{0},{2,1},{0}};
int col[6][4] = {{1},{1},{1,1},{2},{0},{1}};
//[1,2,0]이면 1 2가 제약인거임
int cnt, cc;
bool board[4][6];
bool satisfy_row(int x){
    int current = 0;
    int current_info = 0;
    if(row[x][0] == 0)
        return true;
    for(current=0 ; current<6 ; current++){
        if(board[x][current] == false){
            continue;
        }
        else{
            int tmp_cnt = 0;
            while(current<6 && board[x][current] == true){
                current++;
                tmp_cnt++;
            }
            if(tmp_cnt != row[x][current_info]){
                return false;
            }
            current_info++;
        }
    }
    if(row[x][current_info] != 0){
        return false;
    }
    return true;
}

bool satisfy_col(int x){
    int current = 0;
    int current_info = 0;
    if(col[x][0] == 0)
        return true;
    for(current=0 ; current<4 ; current++){
        if(board[current][x] == false){
            continue;
        }
        else{
            int tmp_cnt = 0;
            while(current<4 && board[current][x] == true){
                current++;
                tmp_cnt++;
            }
            if(tmp_cnt != col[x][current_info]){
                return false;
            }
            current_info++;
        }
    }
    if(col[x][current_info] != 0){
        return false;
    }
    return true;
}
bool satisfy(){
    for(int i=0 ; i<4 ; i++){
        if(!satisfy_row(i)){
            return false;
        }
    }
    for(int i=0 ; i<6 ; i++){
        if(!satisfy_col(i)){
            return false;
        }
    }
    return true;
}
void print(){
    for(int i=0 ; i<4 ; i++){
        for(int j=0 ; j<6 ; j++){
            printf("%d ", board[i][j] ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}
void count_all(int x, int y){
    cc++;
    //pritf("%d %d\n",x,y);
    if(x>=4){
        if(satisfy()){
            cnt++;
            //print();
        }
        return;
    }
    else if(y>=5){
        count_all(x+1,0);
        board[x][y]=true;
        count_all(x+1,0);
        board[x][y]=false;
        return;
    }
    else{
        count_all(x,y+1);
        board[x][y]=true;
        count_all(x,y+1);
        board[x][y]=false;
        return;
    }
}
int main(){
    count_all(0,0);
    //printf("%d\n",cc);
    printf("%d\n", cnt);
    //print();
    return 0;
}