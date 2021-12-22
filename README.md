# Program Kasir

## Fitur

-   Management Barang
-   Kasir
-   Riwayat Transaksi
-   Laporan Keuangan

## Penjelasan Setiap File

### cetak_teks.txt

di file ini terdapat 2 global function yaitu baris untuk menampilkan baris dan judul untuk menampilkan judul

### component.h

ini merupakan file header dimana terdapat inisialisasi dari structure Barang dan Riwayat dan beberapa inisialisasi function

### global_func.c

file ini merupakan file yang menampung global function, berikut nama function dan fungsinya:

-   **copyBarang** berfungsi untuk mendapatkan semua data barang yang ada di file barang.dat untuk di copy ke sebuah variabel, selain itu function ini juga mereturn jumlah barang
-   **tampilBarang** berfungsi untuk menampilkan data barang
-   **cariBarang** berfungsi untuk mencari sebuah index dari sebuah id di data Barang
-   **kalkulasiPendapatan** berfungsi untuk mengkalkulasi semua pendapatan saat transaksi selesai dilakukan
-   **riwayatTransaksi** berfungi untuk menyimpan data transaksi ke file riwayat.dat
-   **cetakStruk** berfungsi untuk menyetak struk di file struk.txt setelah transaksi selesai

### kasir.c

di file ini terdapat fungsi yang untuk menerima pembelian, seperti namanya kasir

### laporan_keuangan.c

file ini yang menangani menu laporan keuangan, menampilkan data-data barang beserta modal dan pendapatan serta laba

### main.c

ini merupakan file main dari program kasi ini, file ini yang menyatukan semua file dan semua fungsi

### menu_barang.c

file ini merupakan file yang menangani menu manajemen barang, di file ini terdapat beberapa fungsi diantaranya

-   **menuBarang** ini merupakan fungsi yang pertama kali di akses saat user ke menu manajemen data barang
-   **addBarang** ini merupakan fungsi untuk menghandle tambah data barang
-   **restok** ini merupakan fungsi untuk menghandle tambah stok data Barang
-   **delBarang** ini merupakan fungsi untuk menghandle hapus data Barang
-   **updBarang** ini merupakan fungsi untuk menghandle update data Barang

### riwayat_transaksi.c

ini merupakan file yang menangani menu riwayat transaksi, dimana disini menampilkan riwayat transaksi yang selama ini terjadi
