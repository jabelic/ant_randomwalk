

#include <stdio.h>
#include <glsc.h>
#include <stdlib.h>
#define N 70
#define IMAX 15
#define JMAX 15
#define M 10
double dice();

int main(void){
    int i,j,S,cmax;
    int c[IMAX+1][JMAX+1]={};
    double d[IMAX+1][JMAX+1]={};
    printf("シード値(自然数)を入力:");
    scanf("%d",&S);
    //乱数
    srand(S);
    //初期化
    g_init("GRAPH", 200.0, 100.0);
    g_device(G_DISP);
    //仮想座標系
    g_def_scale(1, -0.5, 2*(IMAX+0.5)+5.0, -0.5, JMAX+0.5, 10.0, 10.0, 180.0, 80.0);
    g_sel_scale(1);
    
    g_box(-0.5, IMAX+0.5, -0.5, JMAX+0.5, G_YES, G_NO);
    //縦線の描画
    for(i=0;i<IMAX+1;i++){
        g_move(i-0.5,-0.5);
        g_plot(i-0.5,JMAX+0.5);
    }
    //横線の描画
    for(j=0;j<JMAX+1;j++){
        g_move(-0.5,j-0.5);
        g_plot(IMAX+0.5,j-0.5);   
    }
    //i,jの初期値の設定
    i=IMAX/2;
    j=JMAX/2;
    for(int m=1; m<M; m++){
        for(int k=0;k<N;k++){
            g_marker_type(-1);
            g_marker_color(G_RED);
            g_marker_size(3);
            g_marker(i,j);
            g_sleep(0.01);
            g_marker_color(G_WHITE);
            g_marker(i,j);
            c[i][j] += 1;
            //ここで乱数(0~4)を生成
            int r = dice();
            //乱数を判定して次の座標を決定
            if(r==0){
                i++;
            }else if(r==1){
                i--;
            }else if(r==2){
                j++;
            }else if(r==3){
                j--;
            }
            //lec9,課題3の条件のはみ出した時の対処
            if(i<0){
                i=IMAX;
            }else if(IMAX<i){
                i=0;
            }
            else if(j<0){
                j=JMAX;
            }else if(JMAX<j){
                j=0;
            }
            g_sleep(0.001);
        }
    }
    for(i = 0; i <= JMAX; i++){
        for(j = 0; j<=IMAX ; j++){
            if(i==0 && j==0){
                cmax = c[i][j];
            }
            else if(cmax<c[i][j]){
                cmax = c[i][j];
            }
        }
    }
    for(i = 0; i <= JMAX; i++){
        for(j = 0; j <= IMAX; j++){
            d[i][j] = c[i][j]/(double)cmax;
        }
    }
    for(i = 0; i <= JMAX; i++){
        for(j = 0; j <= IMAX; j++){
            printf("%3.1f ", d[i][j]);
        }printf("\n");
    }
    //正規化された値をz軸方向で表現
    g_hidden(100.0, 100.0, 50.0, 0.0, 1.0, 500.0, 60.0, 45.0, 95.0, 0.0, 100.0, 100.0, (double *)d, IMAX+1, JMAX+1, 1, 0, 1, 1);
    g_sleep(G_STOP);
    g_term();
    return 0;
}

//サイコロ関数 0~4までの値をランダムに返す.
double dice(){
  int r;
  double R;
  r = rand();
  R = (double)(r % 5);
  return (int)R;
}
