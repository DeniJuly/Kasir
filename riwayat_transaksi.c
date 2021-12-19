#include <stdio.h>

void listTransaksi(struct Barang allBarang[], int nBarang){
    int tgl_mulai   =   0,
        tgl_selesai =   32,
        bln_mulai   =   0,
        bln_selesai =   13,
        th_mulai    =   2000,
        th_selesai  =   2050;
	while (1){
        int n=0;
        system("cls");
        baris(1, 0);
        judul("TOSERBA SEMBARANG", 0);
        baris(1, 0);
        int i;
        for(i=1;i<nBarang;i++){
            allBarang[i].nBelanja=0;
        }
        unsigned long long modal = 0, pendapatan = 0, laba = 0;
        FILE *fTransaksi;
        struct Riwayat dataTransaksi = { 0, "", 0,"",0,0,0};

        if ( ( fTransaksi = fopen( "transaksi.dat", "rb" ) ) == NULL ) {
            printf( "File tidak bisa dibuka.\n" );
        }
        printf( "|  %-4s| %-19s| %-9s| %-16s| %-24s|\n", "ID", "NAMA BARANG","JUMLAH", "KEUNTUNGAN" , "WAKTU");
        baris(1, 0);
        int penanda=0;
        while ( !feof( fTransaksi ) ) { 
            fread( &dataTransaksi, sizeof( struct Riwayat ), 1, fTransaksi );
            if( dataTransaksi.id == penanda ) continue;
            penanda = dataTransaksi.id;
            if ( dataTransaksi.id != 0 ) {
                if( dataTransaksi.tanggal <= tgl_selesai && 
                    dataTransaksi.tanggal >= tgl_mulai && 
                    dataTransaksi.bulan <= bln_selesai && 
                    dataTransaksi.bulan >= bln_mulai && 
                    dataTransaksi.tahun <= th_selesai && 
                    dataTransaksi.tahun >= th_mulai
                ){
                    int index = cariBarang(allBarang, dataTransaksi.id, nBarang);
                    if(index){
                        modal       += allBarang[index].modal;
                        pendapatan  += allBarang[index].pendapatan;
                        laba        += allBarang[index].pendapatan - allBarang[index].modal;
                    }
                    printf( "|  %-4d| %-19s| %-9d| %-16d| %-24s", dataTransaksi.id, dataTransaksi.nama, dataTransaksi.nBelanja, dataTransaksi.keuntungan, dataTransaksi.time);
                    n++;
                }
            }
        }

        if(n == 0)
            judul("DATA KOSONG",0);
            
        baris(1, 0);
        fclose( fTransaksi );
        printf("> Modal              : %llu\n", modal);
        printf("> Pendapatan         : %llu\n", pendapatan);
        printf("> Laba               : %lli\n", laba);
        baris(1, 0);
        printf("Apa yang ingin anda lakukan (cari/keluar)? ");
        char command[7];
        scanf( "%s",command);
        if(strcmp(command,"keluar")==0){
            break;
        } else if(strcmp(command,"cari")==0){
            printf("Tanggal mulai (dd mm yyyy)    : ");
            scanf("%d %d %d",&tgl_mulai,&bln_mulai,&th_mulai);
            printf("Tanggal selesai  (dd mm yyyy) : ");
            scanf("%d %d %d",&tgl_selesai,&bln_selesai,&th_selesai);
        }
	}
}