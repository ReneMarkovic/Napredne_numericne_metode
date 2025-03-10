#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include <sstream>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <limits>

using namespace std;

const int N = 4*4*4;
double r[N][3];
double v[N][3];
double a[N][3];

// Parametri sistema
double rho = 0.4;
double T_default = 0.8;
double L = pow(N/rho, 1.0/3.0);
double vMax = 0.1;
double dt = 0.01;
int STOP = 5000;
int EINLAUF = int(0.1*STOP);

#include "utils.h"

int main(int argc, char* argv[]){
    double T;
    if(argc>1){
        T = atof(argv[1]);
        printf("Uporabljen je T = %.4f\n",T);
    }else{
        T = T_default;
        printf("Uporabljen je privzet T = %.4f\n",T);
    }
    string pisi_T = ustvari_filename(argc, argv, T, "temperatura");
    string pisi_Lege = ustvari_filename(argc, argv, T, "pozicije");
    string pisi_min_dist = ustvari_filename(argc, argv, T, "min_dist");

    FILE *pisi;

    initialize();
    
    for(int time = 0;time<STOP;time++){
        
        velocityVerlet(dt);

        skaliranje_hitrosti(T);

        
        if(time%10==0){
            T = instantaneousTemperature();
            printf("Izračunanih je %d od %d korakov | T = %.4f\n",time,STOP,T);
        }
        
        if(time>EINLAUF && time%100==0){
            pisi = fopen(pisi_T.c_str(),"a");
            fprintf(pisi,"%d\t%.4f\t%f\n",time,T,T*(3 * (N - 1)));
            fclose(pisi);

            double r_min_avg = avrage_min_nn_distance(r,6);
            pisi = fopen(pisi_min_dist.c_str(),"a");
            fprintf(pisi,"%d\t%.4f\n",time,r_min_avg);
            fclose(pisi);

            pisi = fopen(pisi_Lege.c_str(),"a");
            for(int i=0;i<N;i++){
                fprintf(pisi,"%d\t%.4f\t%.4f\t%.4f\n",time,r[i][0],r[i][1],r[i][2]);
            }
            fclose(pisi);
        }
    }

    final_position();
    return 0;
}