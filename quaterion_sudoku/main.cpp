#include<stdio.h>
#define SIZE 4
using namespace std;
struct quaternion {
	int a, b, c, d;
    //represents quaternion a+bi+cj+dk
    quaternion(){
        a=b=c=d=0;
    }
	quaternion(int x, int y, int z, int w){
		a = x;
		b = y;
        c = z;
        d = w;
	}
	quaternion operator+(quaternion q1){
		int qa = a + q1.a;
		int qb = b + q1.b;
        int qc = c + q1.c;
        int qd = d + q1.d;
		quaternion q = quaternion(qa,qb,qc,qd);
		return q;
	}
	quaternion operator-(quaternion q1){
		int qa = a - q1.a;
		int qb = b - q1.b;
        int qc = c - q1.c;
        int qd = d - q1.d;
		quaternion q = quaternion(qa,qb,qc,qd);
		return q;
	}
	quaternion operator*(quaternion q1){
		int qa = a*q1.a - b*q1.b - c*q1.c - d*q1.d;
		int qb = a*q1.b + b*q1.a + c*q1.d - d*q1.c;
        int qc = a*q1.c - b*q1.d + c*q1.a + d*q1.b;
        int qd = a*q1.d + b*q1.c - c*q1.b + d*q1.a;
		quaternion q = quaternion(qa,qb,qc,qd);
		return q;
	}
	bool operator&&(quaternion q1){
		if(a == q1.a && b == q1.b && c == q1.c && d == q1.d)
			return true;
		else
			return false;
	}
    bool operator||(quaternion q1){
		if(a == q1.a || b == q1.b || c == q1.c || d == q1.d)
			return true;
		else
			return false;
	}
    bool check_quaternion(){
        if(a!=b && a!=c && a!=d && b!=c && b!=d && c!=d)
            return true;
        else
            return false;
    }
    int norm_sq(){
        return (a*a+b*b+c*c+d*d);
    }
	void print(){
        printf("(%d, %d, %d, %d) ", a, b, c, d);
	}
};

quaternion sudoku[SIZE][SIZE];
quaternion zero = quaternion(0,0,0,0);
quaternion permutation[24];
int cnt, per_cnt;

bool check_x(int x, int y){
    for (int i = 0; i < SIZE ; i++)
    {
        if(i != x && !(sudoku[i][y] && zero) && (sudoku[i][y] || sudoku[x][y])){
            return false;
        }
    }
    return true;
}
bool check_y(int x, int y){
    for (int i = 0; i < SIZE ; i++)
    {
        if(i != y && !(sudoku[x][i] && zero) && (sudoku[x][i] || sudoku[x][y])){
            return false;
        }
    }
    return true;
}
bool check_box(int x, int y){
    int box_x = (x/2)*2;
    int box_y = (y/2)*2;
    for(int i=0 ; i<2 ; i++){
        for(int j=0 ; j<2 ; j++){
            int xx = box_x + i;
            int yy = box_y + j;
            if(!(x == xx && y == yy) && !(sudoku[xx][yy] && zero) && (sudoku[xx][yy] || sudoku[x][y]))
                return false;
        }
    }
    return true;
}
bool check(int x, int y){
    // printf("checking...\n");
    // printf("x: %d", check_x(z, x, y));
    // printf("y: %d", check_y(z, x, y));
    // printf("z: %d", check_z(z, x, y));
    // printf("diag: %d\n", check_diagonal(z, x, y));
    
    return check_x(x,y) & check_y(x,y) & check_box(x,y);
}
void print(){
    int cnt_quaternions[24] = {0};
    int diif_quaternions = 0;
    for(int j=0 ; j<SIZE ; j++){
        for(int k=0 ; k<SIZE ; k++){
            for(int i=0 ; i<24 ; i++){
                if(permutation[i] && sudoku[j][k]){
                    cnt_quaternions[i] = 1;
                }
            }
        }
    }
    for(int i=0 ; i<24 ; i++){
        diif_quaternions += cnt_quaternions[i];
    }
    if(diif_quaternions < 16){
        return;
    }
    printf("-----solution %d-----\n", cnt);
    printf("%d different quaternions\n", diif_quaternions);
    // Tried to find solution with most different quaternions.
    for(int j=0 ; j<SIZE ; j++){
        for(int k=0 ; k<SIZE ; k++){
            sudoku[j][k].print();
        }
        printf("\n");
    }
}
void solve(int x, int y){
    if(x>=SIZE){
        // if((sudoku[0][1]+sudoku[0][2]).norm_sq() == 102){
        //     if((sudoku[3][1]+sudoku[3][2]).norm_sq() == 102){
        //         if((sudoku[1][3]*sudoku[2][3]) && quaternion(-12,20,10,16)){
        //             if((sudoku[1][1]+sudoku[1][2]+sudoku[2][1]+sudoku[2][2]) && quaternion(9,10,10,11)){
        //                 cnt++;
        //                 print();
        //             }
        //         }
        //     }
        // }
        cnt++;
        print();
        return;
        
    }
    if(!(sudoku[x][y] && zero)){
        int next_y = y+1;
        int next_x = x;
        if(next_y >= SIZE){
            next_x++;
            next_y = 0;
        }
        solve(next_x, next_y);
        return;
    }
    for(int i=0 ; i<24 ; i++){
        sudoku[x][y] = permutation[i];
        if(!check(x,y)){
            sudoku[x][y] = zero;
            continue;
        }
        else{
            int next_y = y+1;
            int next_x = x;
            if(next_y >= SIZE){
                next_x++;
                next_y = 0;
            }
            solve(next_x, next_y);
            sudoku[x][y] = zero;
        }
    }
}
void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}
void make_permutation(int nums[], int depth){
    if(depth==SIZE){
        permutation[per_cnt++] = quaternion(nums[0], nums[1], nums[2], nums[3]);
        return;
    }
    for(int i=depth ; i<SIZE ; i++){
        swap(nums[depth], nums[i]);
        make_permutation(nums, depth+1);
        swap(nums[depth], nums[i]);
    }
}
void init(){
    for(int i=0 ; i<SIZE ; i++){
        for(int j=0 ; j<SIZE ; j++){
            sudoku[i][j] = quaternion(0,0,0,0);
        }
    }
    sudoku[0][0] = quaternion(3,1,4,2); //순서바꾸기 4!가지 해결
    int nums[4] = {1,2,3,4};
    make_permutation(nums, 0);
    for(int i=0 ; i<24 ; i++){
        permutation[i].print();
        printf("\n");
    }
}
int main(){
    init();
    solve(0,0);
    printf("%d solutions\n", cnt);
    return 0;
}