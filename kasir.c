#include <stdio.h>

void kasir(){
    char out;
	do {
        system("cls");
        struct Barang allBarang[]={};
        int nBarang = copyBarang(allBarang);
        tampilBarang(0);
        printf("Masukkan ID 0 jika sudah tidak ada barang yang dibeli!\n");
        long long int total = 0;
        while(1){
            int ID, nBelanja;
            printf("Masukkan ID barang     : ");
            scanf("%d", &ID);
            if(ID==0){
                break;
            }
            int index;
            index=cariBarang(allBarang,ID,nBarang);
            if(!index){
                printf("ID barang tidak ditemukan.\n");
                continue;
            }
            printf("Masukkan banyak barang : ");
            scanf("%d",&nBelanja);
            allBarang[index].nBelanja += nBelanja;
            if(allBarang[index].nBelanja>allBarang[index].stok){
                printf("Barang Tidak Mencukupi.\n");
                allBarang[index].nBelanja = 0;
                continue;
            }
            total= total + (allBarang[index].harga_jual * allBarang[index].nBelanja);
        }
        baris(1, 0);
        printf("Total Belanja     : %llu\n",total);
        if(total > 0){
            unsigned long long uang;
            while (1)
            {
                printf("Uang yang Dibayar : ");
                scanf("%llu",&uang);
                if(uang < total){
                    printf("Uang tidak mencukupi.\n");
                    uang = 0;
                    continue;
                }else{
                    break;
                }
            }
            long long int kembali;
            kembali=uang-total;
            printf("Kembalian         : %lld\n",kembali);
            getchar();
            cetakStruk(allBarang,nBarang,total,uang,kembali);
            riwayatTransaksi(allBarang, nBarang);
            kalkulasiPendapatan(allBarang, nBarang);
        }
        
        printf("Transaksi lain (Y/N) ? ");
        scanf("%c", &out);
        getchar();
	} while ( out=='y' || out =='Y' );
}