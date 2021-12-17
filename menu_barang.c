#include <stdio.h>

FILE *fBarang;
struct Barang dataBarang =  {0,"",0,0,0,0,0};

void addBarang();
void restok();
void delBarang();
void updBarang();


void menuBarang(){
    while (1)
    {
        int n;
        char command[10];
        system("cls");
        tampilBarang(0);
        printf("Apa yang ingin anda lakukan (tambah/stok/hapus/edit/keluar) ? ");
        scanf( "%s", command);
        if(strcmp(command, "tambah") == 0){
            addBarang();
        } else if(strcmp(command, "stok") == 0){
        	restok();
        } else if(strcmp(command, "hapus") == 0){
        	delBarang();
        } else if(strcmp(command, "edit") == 0){
        	updBarang();
        } else if(strcmp(command, "keluar") == 0) {
            break;
        }else {
            printf("Perinatah tidak ditemukan.");
            getch();
        }
    }
    fclose(fBarang);
}

void addBarang(){
    char out;
    fBarang = fopen("barang.dat", "rb+");
    if(fBarang == NULL){
        printf("file tidak bisa dibuka");
        return;
    }
    while(1)
    {
        printf("Masukkan ID Barang    : ");
        scanf( "%d", &dataBarang.id);
        printf("Masukkan Nama Barang  : ");
        scanf("%s", dataBarang.nama);
        printf( "Masukkan Harga Barang : ");
        scanf( "%llu", &dataBarang.harga);
        printf("Masukkan Stok Barang  : ");
        scanf( "%d", &dataBarang.stok);
        dataBarang.modal      = dataBarang.stok * dataBarang.harga;
        dataBarang.pendapatan = 0;
        dataBarang.nBelanja = 0;
        fseek( fBarang, ( dataBarang.id - 1 ) * sizeof( struct Barang ), SEEK_SET );
        fwrite( &dataBarang, sizeof( struct Barang ), 1, fBarang );
        if(fwrite != 0)
            printf( "berhasil menyimpan perubahan !\n");
        else
            printf( "gagal menyimpan perubahan !\n");
        printf("Apakah anda ingin keluar (Y/N) ? ");
        scanf( " %c", &out);
        if(out == 'y' || out == 'Y')
            break;
    }
    fclose(fBarang);
}

void restok(){
    char out;
    int ID, stok, i, nBarang;
    fBarang = fopen("barang.dat", "rb+");
    if(fBarang == NULL){
        printf("file tidak bisa dibuka");
        return;
    }
    while (1)
    {
        struct Barang allBarang[]={};
        nBarang = copyBarang(allBarang);
        printf( "Masukkan ID Barang          : " );
        scanf( "%d", &dataBarang.id );
        
        printf("Tambah Berapa Stok Barang   : ");
        scanf( "%d", &dataBarang.stok );
        for(i=1;i<nBarang;i++){
            if(dataBarang.id==allBarang[i].id){
                strcpy(dataBarang.nama, allBarang[i].nama);
                dataBarang.harga        = allBarang[i].harga;
                dataBarang.modal        = allBarang[i].modal + (dataBarang.stok * dataBarang.harga);
                dataBarang.stok        += allBarang[i].stok;
                dataBarang.pendapatan   = allBarang[i].pendapatan;
                dataBarang.nBelanja     = allBarang[i].nBelanja;
                break;
            }
        }

        fseek( fBarang, ( dataBarang.id - 1 ) * sizeof( struct Barang ), SEEK_SET ); 
        fwrite( &dataBarang, sizeof( struct Barang ), 1, fBarang );

        if(fwrite != 0)
            printf( "berhasil menyimpan perubahan !\n");
        else
            printf( "gagal menyimpan perubahan !\n");

        printf("Apakah anda ingin keluar (Y/N) ? ");
        scanf( " %c", &out);
        if(out == 'y' || out == 'Y')
            break;
    }
    fclose(fBarang);
}

void delBarang(){
    fBarang = fopen("barang.dat", "rb+");
    if(fBarang == NULL){
        printf("file tidak bisa dibuka");
        return;
    }
    char out;
    while(1)
    {
        printf("Masukkan ID Barang yang ingin dihapus : ");
        scanf("%d",&dataBarang.id);
        fseek( fBarang, ( dataBarang.id - 1 ) * sizeof( struct Barang ), SEEK_SET );         
        dataBarang.id           = 0;
        dataBarang.harga        = 0;
        dataBarang.modal        = 0;
        dataBarang.pendapatan   = 0;
        dataBarang.stok         = 0;
        dataBarang.nBelanja     = 0;
        strcpy(dataBarang.nama,"");
        fwrite( &dataBarang, sizeof( struct Barang ), 1, fBarang );
        if(fwrite != 0)
            printf( "berhasil menyimpan perubahan !\n");
        else
            printf( "gagal menyimpan perubahan !\n");
        printf("Apakah anda ingin keluar (Y/N) ? ");
        scanf( " %c", &out);
        if(out == 'y' || out == 'Y')
            break;
    }
    fclose(fBarang);
}

void updBarang(){
    fBarang = fopen("barang.dat", "rb+");
    if(fBarang == NULL){
        printf("file tidak bisa dibuka");
        return;
    }
    char out, command[6];
    int ID, nBarang;
    while(1)
    {
        struct Barang allBarang[]={};
        nBarang = copyBarang(allBarang);
        printf("Masukkan ID Barang yang ingin diedit : ");
        scanf("%d",&dataBarang.id);
        int i;
        for(i=1;i<nBarang;i++){ 
            if(dataBarang.id==allBarang[i].id){
                dataBarang.stok         =allBarang[i].stok; 
                strcpy(dataBarang.nama,allBarang[i].nama);
                dataBarang.harga        =allBarang[i].harga;
                dataBarang.modal        =allBarang[i].modal;
                dataBarang.pendapatan   =allBarang[i].pendapatan;
                dataBarang.nBelanja     =allBarang[i].nBelanja;
                break;
            }
        }
        printf("What do you want to edit (nama/harga)? ");
        scanf("%s", command);
        if(strcmp(command,"nama")==0){
            printf( "Masukkan Nama Barang baru : " );
            scanf( "%s", dataBarang.nama );
        } else {
            printf( "Masukkan Harga Barang baru : " );
            scanf( "%llu", &dataBarang.harga );
        }

        fseek( fBarang, ( dataBarang.id - 1 ) * sizeof( struct Barang ), SEEK_SET );
        fwrite( &dataBarang, sizeof( struct Barang ), 1, fBarang );

        if(fwrite != 0)
            printf( "berhasil menyimpan perubahan !\n");
        else
            printf( "gagal menyimpan perubahan !\n");

        printf("Apakah anda ingin keluar (Y/N) ? ");
        scanf( " %c", &out);
        if(out == 'y' || out == 'Y')
            break;
    }
    fclose(fBarang);
}