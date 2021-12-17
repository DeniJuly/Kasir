#include <stdio.h>

void baris(int tipe, int showAll){
    if(tipe == 1){
        if(showAll == 1)
            printf( "---------------------------------------------------------------------------------------\n");
        else
            printf( "------------------------------------------------------------------\n");
    } else {
        if(showAll == 1)
            printf( "=======================================================================================\n");
        else
            printf( "==================================================================\n");
    }
}

void judul(char teks[10], int showAll){
    if(showAll == 1)
        printf( "|                                     %-48s|\n",teks);
    else
        printf( "|                           %-37s|\n",teks);
}