#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

void laporanKeuangan(){
    FILE *fBarang;
    struct Barang dataBarang = { 0, "", 0,0,0,0,0,0};
    unsigned long long modal=0,  pendapatan=0, laba = 0;
    int penanda=0, n=0;

    system("cls");
    baris(1, 1);
    judul("DATA BARANG", 1);
    baris(1, 1);

    if ( ( fBarang = fopen( "barang.dat", "rb+" ) ) == NULL ) {
        printf( "File tidak bisa dibuka.\n" );
    }

    printf( "|  %-4s|  %-14s|  %-14s|  %-14s|  %-8s|  %-14s|  %-14s|\n", "ID", "NAMA BARANG","HARGA","HARGA JUAL", "STOK","MODAL","PENDAPATAN" );
    baris(1,1);

    while ( !feof( fBarang ) ) { 
        fread( &dataBarang, sizeof( struct Barang ), 1, fBarang );
        if(dataBarang.id == penanda) continue;
        penanda = dataBarang.id;
        if ( dataBarang.id != 0 ) {
            modal      += dataBarang.modal;
            pendapatan += dataBarang.pendapatan;
            printf( "|  %-4d|  %-14s|  %-14llu|  %-14llu|  %-8d|  %-14llu|  %-14llu|\n", dataBarang.id, dataBarang.nama, dataBarang.harga, dataBarang.harga_jual, dataBarang.stok, dataBarang.modal, dataBarang.pendapatan );
            n++;
        }
    }

    if(n == 0)
        judul("DATA KOSONG", 1);

    fclose( fBarang );
    baris(1, 1);

    printf("> Modal/Pengeluaran \t: %llu\n", modal);
    printf("> Pendapatan \t\t: %llu\n", pendapatan);
    laba = pendapatan - modal;
    if(laba < 0)
        printf("> Rugi \t\t\t: %lld\n",laba);
    else
        printf("> Laba \t\t\t: %lld\n",laba);

    getchar();
    printf("Klik enter untuk keluar.");
    getchar();

}
