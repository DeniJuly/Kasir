#include <stdio.h>

void listTransaksi(struct Barang allBarang[], int nBarang){
    int tgl1=0,
        tgl2=32,
        bln1=0,
        bln2=13,
        thn1=1990,
        thn2=3000;
	while (1){
        int n=0;
        system("cls");
        baris(2, 0);
        judul("TOKO HASAN", 0);
        baris(2, 0);
        int i;
        for(i=1;i<nBarang;i++){
            allBarang[i].nBelanja=0;
        }
        unsigned long long modal      = 0;
        unsigned long long pendapatan = 0;
        long long int laba;
        FILE *fTransaksi;
        struct Riwayat dataTransaksi = { 0, "", 0,"",0,0,0};

        if ( ( fTransaksi = fopen( "transaksi.dat", "rb" ) ) == NULL ) {
            printf( "File tidak bisa dibuka.\n" );
        }
        printf( "|  %-4s| %-19s| %-9s| %-24s|\n", "ID", "NAMA BARANG","JUMLAH", "WAKTU");
        baris(2, 0);
        int penanda=0;
        while ( !feof( fTransaksi ) ) { 
            fread( &dataTransaksi, sizeof( struct Riwayat ), 1, fTransaksi );
            if( dataTransaksi.id == penanda )continue;
                penanda = dataTransaksi.id;
                if ( dataTransaksi.id != 0 ) {
                    if(dataTransaksi.tanggal<=tgl2&&dataTransaksi.tanggal>=tgl1&&dataTransaksi.bulan<=bln2&&dataTransaksi.bulan>=bln1&&dataTransaksi.tahun<=thn2&&dataTransaksi.tahun>=thn1){
                    int i;
                    for(i=1;i<nBarang;i++){
                        if(dataTransaksi.id==allBarang[i].id){
                            allBarang[i].nBelanja+=dataTransaksi.nBelanja;
                            break;
                        }
                    }
                    printf( "|  %-4d| %-19s| %-9d| %-24s", dataTransaksi.id, dataTransaksi.nama, dataTransaksi.nBelanja, dataTransaksi.time);
                    n++;
                }
            }
        }

        if(n == 0)
            judul("DATA KOSONG",0);
            
        baris(2, 0);
        fclose( fTransaksi );
        printf("Apa yang ingin anda lakukan (cari/keluar)? ");
        char command[7];
        scanf( "%s",command);
        if(strcmp(command,"keluar")==0){
            break;
        }
        else if(strcmp(command,"cari")==0){
            printf("Input awal (dd mm yyyy)  : ");
            scanf("%d %d %d",&tgl1,&bln1,&thn1);
            printf("Input akhir (dd mm yyyy) : ");
            scanf("%d %d %d",&tgl2,&bln2,&thn2);
        }
        else{
            printf("Nai");
        }
	}
}