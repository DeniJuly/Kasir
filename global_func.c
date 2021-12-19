#include <stdio.h>

int copyBarang(struct Barang allBarang[]){
    int n=1;
    FILE *fp;
    struct Barang dataBarang = {0,"",0,0,0,0,0,0};

    if ( ( fp = fopen( "barang.dat", "rb" ) ) == NULL ) {
        printf( "File could not be opened.\n" );
        return 0;
    }
    int penanda=0;
    while ( !feof( fp ) ) { 
        fread( &dataBarang, sizeof( struct Barang ), 1, fp );
        if(dataBarang.id==penanda)continue;
            penanda=dataBarang.id;
            if ( dataBarang.id != 0 ) {
                allBarang[n].id=dataBarang.id;
                strcpy(allBarang[n].nama,dataBarang.nama);
                allBarang[n].harga      = dataBarang.harga;
                allBarang[n].harga_jual      = dataBarang.harga_jual;
                allBarang[n].stok       = dataBarang.stok;
                allBarang[n].modal      = dataBarang.modal;
                allBarang[n].pendapatan = dataBarang.pendapatan;
                allBarang[n].nBelanja   = dataBarang.nBelanja;
                n++;
            }
    }
    fclose( fp );
    return n;
}

void tampilBarang(int showAll){
    int n = 0;
    fBarang = fopen("barang.dat", "r");
    if(fBarang == NULL){
        printf( "file tidak bisa dibuka");
        return;
    }
    baris(2, showAll);
    judul("DATA BARANG", showAll);
    baris(2, showAll);
    if(showAll == 1)
        printf( "|  %-4s|  %-24s|  %-15s|  %-16s|  %-10s|  %-7s|  %-7s|\n", "ID", "NAMA BARANG", "HARGA", "HARGA JUAL", "STOK", "MODAL", "PENDAPATAN" );
    else
        printf( "|  %-4s|  %-24s|  %-15s|  %-16s|  %-10s|\n", "ID", "NAMA BARANG","HARGA", "HARGA JUAL", "STOK" );
    baris(2, showAll);
    while(fread(&dataBarang, sizeof(struct Barang), 1, fBarang))
        if ( dataBarang.id != 0 ){
            if(showAll == 1)
                printf( "|  %-4d|  %-24s|  %-15llu|  %-16llu|  %-10d|  %-5llu|  %-5llu|\n", dataBarang.id, dataBarang.nama, dataBarang.harga, dataBarang.harga_jual, dataBarang.stok, dataBarang.modal, dataBarang.pendapatan);
            else
                printf( "|  %-4d|  %-24s|  %-15llu|  %-16llu|  %-10d|\n", dataBarang.id, dataBarang.nama, dataBarang.harga, dataBarang.harga_jual, dataBarang.stok);
            n++;
        }
    if(n==0)
        judul("DATA KOSONG", showAll);
    baris(2, showAll);
    fclose(fBarang);
}

int cariBarang(struct Barang allBarang[],int id,int nBarang){
    int i;
    for(i=1;i<nBarang;i++){
        if(allBarang[i].id==id){
            return i;
        }
    }
    return 0;
}

void kalkulasiPendapatan(struct Barang allBarang[], int nBarang){
    FILE *fBarang;
    struct Barang dataBarang = {0,"",0,0,0,0,0,0};

    if ( ( fBarang = fopen( "barang.dat", "rb+" ) ) == NULL ) {
        printf( "File tidak bisa dibuka.\n" );
    }
    int i;
	for(i=1;i < nBarang;i++){
        if(allBarang[i].nBelanja==0)continue;
        int penanda=0;
        while ( !feof( fBarang ) ) { 

            fread( &dataBarang, sizeof( struct Barang ), 1, fBarang );
            if(dataBarang.id == penanda) continue;
            penanda = dataBarang.id;

            if(allBarang[i].id == dataBarang.id){
                dataBarang.stok         -= allBarang[i].nBelanja;
                dataBarang.pendapatan   += (allBarang[i].nBelanja*dataBarang.harga_jual);
                allBarang[i].nBelanja   = 0;
                fseek( fBarang, ( dataBarang.id - 1 ) * sizeof( struct Barang ), SEEK_SET );         
                fwrite( &dataBarang, sizeof( struct Barang ), 1, fBarang );
                break;
            }
        }
    }
    fclose( fBarang );
}

void riwayatTransaksi(struct Barang allBarang[],int nBarang){
	time_t t; 
    time(&t);
    int day, month, year;
    struct tm *local = localtime(&t);
    day   = local->tm_mday;  
    month = local->tm_mon + 1;     
    year  = local->tm_year + 1900;
	FILE *fBarang;
    struct Riwayat dataRiwayat;

    if ( ( fBarang = fopen( "transaksi.dat", "ab+" ) ) == NULL ) {
        printf( "File could not be opened.\n" );
    }
    int i;
	for(i=1;i < nBarang;i++){
        if( allBarang[i].nBelanja == 0) continue;

        strcpy(dataRiwayat.nama,allBarang[i].nama);
        strcpy(dataRiwayat.time,ctime(&t));
        dataRiwayat.id          = allBarang[i].id;
        dataRiwayat.nBelanja    = allBarang[i].nBelanja;
        dataRiwayat.keuntungan  = (allBarang[i].harga_jual * allBarang[i].nBelanja) - (allBarang[i].harga * allBarang[i].nBelanja);
        dataRiwayat.tanggal     = day;
        dataRiwayat.bulan       = month;
        dataRiwayat.tahun       = year;
        fwrite(&dataRiwayat,sizeof(dataRiwayat),1,fBarang);
    }
    fclose( fBarang );
}

void cetakStruk(struct Barang allBarang[], int bnykdata, unsigned long long total, unsigned long long uang, unsigned long long kembali){
    time_t t; 
    time(&t);
	FILE *struk;
    struk = fopen("struk.txt", "w");
    int i;
    fprintf(struk,"=========================================================\n");
    fprintf(struk,"|                      TOKO HASAN                       |\n");
    fprintf(struk,"=========================================================\n");
    fprintf(struk, "| %-20s | %-10s | %-18s|\n", "Nama", "Jumlah", "Harga");
    fprintf(struk,"=========================================================\n");
    for(i=1;i < bnykdata;i++){
        if(allBarang[i].nBelanja == 0)continue;
        fprintf(struk, "| %-20s | %-10llu | %-18llu|\n", allBarang[i].nama, allBarang[i].nBelanja, allBarang[i].harga_jual * allBarang[i].nBelanja);
    }
    fprintf(struk,"=========================================================\n");
    fprintf(struk,"| Total   : %llu\n",total);
    fprintf(struk,"| Uang    : %llu\n",uang);
    fprintf(struk,"| Kembali : %llu\n",kembali);
    fprintf(struk,"=========================================================\n");
    fprintf(struk,"Terima Kasih , %s",ctime(&t));
    fclose(struk);
}