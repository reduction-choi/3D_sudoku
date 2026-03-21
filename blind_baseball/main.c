#include <stdio.h>
#include <string.h>
 
// guess와 target을 비교해서 strikes, balls, outs를 계산
void evaluate(int guess[], int target[], int *strikes, int *balls, int *outs) {
    *strikes = 0;
    *balls = 0;
    *outs = 0;
 
    // target에서 각 숫자의 남은 개수 추적 (스트라이크로 소비된 것 제외)
    int target_remaining[10] = {0};
 
    // 1패스: 스트라이크 계산
    for (int i = 0; i < 5; i++) {
        if (guess[i] == target[i]) {
            (*strikes)++;
        } else {
            target_remaining[target[i]]++;
        }
    }
 
    // 2패스: 볼/아웃 계산 (스트라이크가 아닌 자리만)
    for (int i = 0; i < 5; i++) {
        if (guess[i] != target[i]) {
            if (target_remaining[guess[i]] > 0) {
                (*balls)++;
                target_remaining[guess[i]]--;
            } else {
                (*outs)++;
            }
        }
    }
}
 
int main() {
    // 조건 정의: {guess 숫자, 기대 strikes, 기대 balls, 기대 outs}
    int clues[4][5][1]; // [clue_idx][digit_idx]
    int exp_s[4], exp_b[4], exp_o[4];
 
    // 86427: 2B 2O 1S
    int g0[] = {8, 6, 4, 2, 7};
    exp_s[0] = 1; exp_b[0] = 2; exp_o[0] = 2;
 
    // 45789: 3B 1O 1S
    int g1[] = {4, 5, 7, 8, 9};
    exp_s[1] = 1; exp_b[1] = 3; exp_o[1] = 1;
 
    // 17777: 3O 2S
    int g2[] = {1, 7, 7, 7, 7};
    exp_s[2] = 2; exp_b[2] = 0; exp_o[2] = 3;
 
    // 17777: 3O 2S
    int g3[] = {6, 7, 0, 5, 7};
    exp_s[3] = 3; exp_b[3] = 0; exp_o[3] = 2;
    int *guesses[4] = {g0, g1, g2, g3};
 
    int count = 0;
 
    for (int n = 0; n <= 99999; n++) {
        int target[5];
        target[0] = n / 10000 % 10;
        target[1] = n / 1000  % 10;
        target[2] = n / 100   % 10;
        target[3] = n / 10    % 10;
        target[4] = n         % 10;
 
        int ok = 1;
        for (int c = 0; c < 4; c++) {
            int s, b, o;
            evaluate(guesses[c], target, &s, &b, &o);
            if (s != exp_s[c] || b != exp_b[c] || o != exp_o[c]) {
                ok = 0;
                break;
            }
        }
 
        if (ok) {
            printf("%05d\n", n);
            count++;
        }
    }
 
    printf("\n총 %d개의 해를 찾았습니다.\n", count);
    return 0;
}