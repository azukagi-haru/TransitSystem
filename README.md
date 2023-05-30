# KRL Guide
Program ini dirancang untuk membantu pengguna menemukan rute terpendek antara dua stasiun dalam sebuah sistem transit menggunakan representasi graf dengan daftar keterhubungan.

## Peta KRL
Program ini dibuat berdasarkan peta KRL Jabodetabek berikut. 
![Peta KRL Jabodetabek](/images/peta_krl.png)

## Fitur
- **Pencarian Rute**: Program Transit memungkinkan pengguna untuk mencari rute perjalanan antara dua lokasi yang diinginkan. Pengguna dapat memasukkan lokasi asal dan tujuan, dan program akan mencari rute tercepat yang tersedia menggunakan transportasi umum.

## Cara Menjalankan
Setelah melakukan `git clone` pada repo ini, jalankan perintah berikut pada command line.
```
$ cd TransitSystem/
$ g++ transit.cpp KRL_init.cpp -o transit
$ ./transit
```

## Tim Penyusun
- Andra Dihat Putra
- Fais Fadilah Prasetyo
- Muhamad Ghifar Azka Nurhadi