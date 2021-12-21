#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "component.h"
#include "cetak_teks.c"
#include "menu_barang.c"
#include "global_func.c"
#include "kasir.c"
#include "riwayat_transaksi.c"
#include "laporan_keuangan.c"

int main(){
    int menu;
    while (1)
    {
        system("cls");
        int nBarang = copyBarang(allBarang);
        printf("---------------------------------------\n");
        printf("|          TOSERBA SEMBARANG          |\n");
        printf("---------------------------------------\n");
        printf("| 1. Data Barang                      |\n");
        printf("| 2. Kasir                            |\n");
        printf("| 3. Riwayat Transaksi                |\n");
        printf("| 4. Laporan Keuangan                 |\n");
        printf("| 5. Keluar                           |\n");
        printf("---------------------------------------\n"); 
        printf("Masukkan kode menu: ");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            menuBarang();
            break;
        case 2:
            kasir(allBarang, nBarang);
            break;
        case 3:
            listTransaksi(allBarang, nBarang);
            break;
        case 4:
            laporanKeuangan();
            break;
        case 5:
            exit(0);
            break;
        default:
            getchar();
            printf("Kode menu tidak diketahui. klik enter untuk memasukkan kode menu lain.");
            getchar();
            continue;
            break;
        }
    }
}