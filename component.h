#include <stdio.h>

struct Barang
{
    int id;
    char nama[50];
    int stok;
    unsigned long long harga;
    unsigned long long modal;
    unsigned long long pendapatan;
    int nBelanja;
};

struct Riwayat 
{
	int id;
	char nama[20];
	int nBelanja;
	char time[30];
	int tanggal;
	int bulan;
	int tahun;
};

void tampilBarang(int showAll);
int copyBarang(struct Barang allBarang[]);
void laporanKeuangan();