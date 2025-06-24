# Sisop-FP-2025-IT-C02

## Peraturan
1. Waktu pengerjaan dimulai hari Kamis (19 Juni 2025) setelah soal dibagikan hingga hari Rabu (25 Juni 2025) pukul 23.59 WIB.
2. Praktikan diharapkan membuat laporan penjelasan dan penyelesaian soal dalam bentuk Readme(github).
3. Format nama repository github “Sisop-FP-2025-IT-[Kelas][Kelompok]” (contoh:Sisop-FP-2025-IT-A01).
4. Setelah pengerjaan selesai, seluruh source code dan semua script bash, awk, dan file yang berisi cron job ditaruh di github masing - masing kelompok, dan link github dikumpulkan pada form yang disediakan. Pastikan github di setting ke publik.
5. Commit terakhir maksimal 10 menit setelah waktu pengerjaan berakhir. Jika melewati maka akan dinilai berdasarkan commit terakhir.
6. Jika tidak ada pengumuman perubahan soal oleh asisten, maka soal dianggap dapat diselesaikan.
7. Jika ditemukan soal yang tidak dapat diselesaikan, harap menuliskannya pada Readme beserta permasalahan yang ditemukan.
8. Praktikan tidak diperbolehkan menanyakan jawaban dari soal yang diberikan kepada asisten maupun praktikan dari kelompok lainnya.
9. Jika ditemukan indikasi kecurangan dalam bentuk apapun di pengerjaan soal final project, maka nilai dianggap 0.
10. Pengerjaan soal final project sesuai dengan modul yang telah diajarkan.

## Kelompok C02

Nama | NRP
--- | ---
Nabilah Anindya Paramesti | 5027241006
Danuja Prasasta Bastu | 5027241037
Ananda Widi Alrafi | 5027241067
Muhammad Huda Rabbani | 5027241098

## Deskripsi Soal (Test Case 6)

Buat program dimana menerima input user untuk diproses dengan system dan fork+exec sekaligus, untuk diketahui perbedaan kecepatan eksekusi mereka.

### Catatan

> Insert catatan dari pengerjaan kalian... (contoh dibawah) // hapus line ini

Struktur repository:
```
.
..
```

## Pengerjaan



**Teori**
Fungsi-fungsi seperti **`system()`**, **`fork()`**, dan **`exec()`** adalah bagian penting dalam manajemen proses di sistem operasi berbasis Unix dan sistem operasi modern lainnya. Teori mengenai ketiga fungsi ini biasanya berfokus pada pengelolaan proses, efisiensi memori, serta overhead yang dihasilkan oleh penggunaan masing-masing panggilan sistem.

## **Fork dan Exec**

### 1. **Fungsi `fork()`**
Fungsi **`fork()`** adalah panggilan sistem yang digunakan untuk menduplikasi proses yang sedang berjalan. Ketika **`fork()`** dipanggil, sistem operasi membuat salinan baru dari proses induk. Proses anak yang baru ini hampir identik dengan proses induk, meskipun terdapat beberapa perbedaan minor, seperti ID proses yang berbeda. Proses anak kemudian dijadwalkan untuk dieksekusi oleh kernel.

- **Tanenbaum (2014)** menjelaskan bahwa **`fork()`** menciptakan proses baru yang hampir identik dengan induknya. Proses baru ini ditempatkan dalam antrian siap untuk dijalankan dan diatur oleh kernel. Proses induk dan anak kemudian dapat berjalan secara bersamaan, tetapi dengan kontrol yang terpisah.

   **Kelebihan `fork()`**: 
   - Memungkinkan pembuatan proses baru yang hampir identik dengan induknya.
   - Memberikan kemampuan untuk menjalankan beberapa proses secara paralel.

   **Kekurangan `fork()`**:
   - Menghasilkan overhead memori karena setiap proses baru membutuhkan ruang memori untuk menyimpan salinan data dari proses induk.
   - Meskipun proses anaknya identik, banyak data yang mungkin tidak diperlukan, menyebabkan pemborosan memori.

### 2. **Fungsi `exec()`**
Setelah **`fork()`** menciptakan proses anak, **`exec()`** digunakan untuk mengganti citra proses yang ada dengan program yang baru. Fungsi ini memuat program baru ke dalam ruang memori proses anak dan memulai eksekusinya. Dengan menggunakan **`exec()`**, proses induk dan anak tetap dapat menjalankan program yang berbeda tanpa perlu membuat salinan baru dari memori proses.

- **Bach (1986)** mengemukakan bahwa **`exec()`** memungkinkan program baru dimuat ke dalam ruang alamat proses yang telah ada, menggantikan program yang sedang berjalan. Eksekusi kemudian dimulai dari program baru tersebut.

   **Kelebihan `exec()`**:
   - Memungkinkan penggantian program dalam proses yang sama, sehingga lebih efisien daripada menciptakan proses baru dengan **`fork()`**.
   - Mengurangi pemborosan memori karena tidak ada duplikasi data proses.

   **Kekurangan `exec()`**:
   - Proses yang menggunakan **`exec()`** harus menghentikan eksekusi program lama dan memulai eksekusi program baru dari awal, sehingga tidak dapat melakukan pekerjaan lain sebelum eksekusi program baru dimulai.

### 3. **Penggunaan Bersama `fork()` dan `exec()`**
Ketika **`fork()`** dan **`exec()`** digunakan bersama-sama, mereka menawarkan cara yang lebih efisien untuk membuat dan menjalankan proses baru. Dengan **`fork()`**, proses anak diciptakan, dan kemudian dengan **`exec()`**, proses tersebut menggantikan citra program yang ada dengan program yang baru.

- **Silberschatz et al. (2018)** menjelaskan bahwa kombinasi **`fork()`** dan **`exec()`** adalah cara yang efisien untuk menjalankan program baru karena tidak memerlukan shell. Proses yang dihasilkan lebih cepat dan lebih hemat memori, karena tidak ada overhead untuk memulai shell.

   **Kelebihan gabungan `fork()` dan `exec()`**:
   - Memungkinkan eksekusi program baru tanpa membutuhkan shell tambahan.
   - Lebih efisien dalam hal pengelolaan memori dan kecepatan eksekusi.

   **Kekurangan gabungan `fork()` dan `exec()`**:
   - Melibatkan overhead dalam penciptaan proses anak, meskipun lebih kecil dibandingkan dengan **`system()`**.

## **System Call (system())**

### Fungsi **`system()`**
Fungsi **`system()`** digunakan untuk mengeksekusi perintah dalam shell. Perbedaannya dengan **`fork()`** dan **`exec()`** adalah bahwa **`system()`** memulai shell terlebih dahulu untuk menjalankan perintah. Karena ini melibatkan pembuatan proses shell tambahan, **`system()`** membawa overhead yang lebih besar dibandingkan dengan penggunaan langsung **`fork()`** dan **`exec()`**.

- **Tanenbaum (2014)** mengkritik penggunaan **`system()`** karena memerlukan pengelolaan shell yang mengarah pada overhead yang lebih besar dibandingkan dengan **`fork()`** dan **`exec()`**, yang tidak memerlukan shell untuk mengeksekusi perintah.

   **Kelebihan `system()`**:
   - Mudah digunakan dalam skrip untuk menjalankan perintah shell tanpa memerlukan kontrol proses yang lebih rumit.
   - Dapat digunakan dengan cepat untuk eksekusi perintah yang sederhana.

   **Kekurangan `system()`**:
   - Memulai shell baru yang menyebabkan overhead memori dan waktu eksekusi.
   - Kurang efisien untuk aplikasi yang memerlukan eksekusi perintah yang lebih kompleks atau berulang.


## **Solusi**

Dalam buku Operating Systems: Internals and Design Principles edisi ke-9 oleh William Stallings, terdapat penjelasan mengenai perbandingan antara penggunaan fungsi system() dan kombinasi fork() + exec() dalam konteks pembuatan dan eksekusi proses baru di sistem operasi berbasis Unix/Linux.

1. Fork dan Exec
Stallings menjelaskan bahwa dalam sistem Unix/Linux, untuk memulai program baru, proses induk biasanya membuat salinan dirinya sendiri menggunakan sistem panggilan fork(). Setelah itu, proses anak menggantikan dirinya dengan program baru menggunakan exec(). Proses ini memungkinkan pembuatan proses baru yang efisien dan terkontrol.

2. Penggunaan System Call
Fungsi system() adalah pembungkus dari fork() dan exec(). Ketika system() dipanggil, ia membuat proses anak, yang kemudian menjalankan shell untuk mengeksekusi perintah yang diberikan. Meskipun lebih mudah digunakan, pendekatan ini memiliki overhead tambahan karena melibatkan pembuatan shell baru.

3. Perbandingan Kinerja
Stallings menekankan bahwa setiap panggilan sistem memiliki overhead waktu karena peralihan dari konteks pengguna ke konteks kernel. Oleh karena itu, menghindari panggilan sistem dapat meningkatkan kinerja program dengan mengurangi overhead. Dalam konteks ini, penggunaan system() mungkin kurang efisien dibandingkan dengan langsung menggunakan fork() dan exec().

Kesimpulan
Berdasarkan penjelasan Stallings, untuk aplikasi yang memerlukan pembuatan proses baru secara efisien, menggunakan kombinasi fork() dan exec() lebih disarankan dibandingkan dengan menggunakan system(). Pendekatan ini memberikan kontrol lebih besar dan mengurangi overhead, sehingga meningkatkan kinerja sistem secara keseluruhan.

Kemudian, salam buku Modern Operating Systems edisi ke-5 oleh Andrew S. Tanenbaum dan Herbert Bos, terdapat penjelasan mengenai perbandingan antara penggunaan system() dan kombinasi fork() + exec() dalam konteks pembuatan proses baru di sistem operasi berbasis Unix/Linux.([openlibrary.org][1])

### 1. *Fork dan Exec*

Tanenbaum menjelaskan bahwa dalam sistem Unix/Linux, untuk memulai program baru, proses induk biasanya membuat salinan dirinya sendiri menggunakan sistem panggilan fork(). Setelah itu, proses anak menggantikan dirinya dengan program baru menggunakan exec(). Proses ini memungkinkan pembuatan proses baru yang efisien dan terkontrol.

### 2. *Penggunaan System Call*

Fungsi system() adalah pembungkus dari fork() dan exec(). Ketika system() dipanggil, ia membuat proses anak, yang kemudian menjalankan shell untuk mengeksekusi perintah yang diberikan. Meskipun lebih mudah digunakan, pendekatan ini memiliki overhead tambahan karena melibatkan pembuatan shell baru.&#x20;

### 3. *Perbandingan Kinerja*

Tanenbaum menekankan bahwa setiap panggilan sistem memiliki overhead waktu karena peralihan dari konteks pengguna ke konteks kernel. Oleh karena itu, menghindari panggilan sistem dapat meningkatkan kinerja program dengan mengurangi overhead. Dalam konteks ini, penggunaan system() mungkin kurang efisien dibandingkan dengan langsung menggunakan fork() dan exec().

### Kesimpulan

Berdasarkan penjelasan Tanenbaum, untuk aplikasi yang memerlukan pembuatan proses baru secara efisien, menggunakan kombinasi fork() dan exec() lebih disarankan dibandingkan dengan menggunakan system(). Pendekatan ini memberikan kontrol lebih besar dan mengurangi overhead, sehingga meningkatkan kinerja sistem secara keseluruhan.

**Video Menjalankan Program**

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/cdf44602-1e07-4c8b-a981-cafb20600226

## Daftar Pustaka

- Tanenbaum, A.S. 2014. Modern Operating Systems. Edisi ke-4. Pearson. Boston.
- Silberschatz, A., Galvin, P.B., dan Gagne, G. 2018. Operating System Concepts. Edisi ke-10. Wiley. Hoboken.
- Bach, M.J. 1986. The Design of the UNIX Operating System. Prentice Hall. Englewood Cliffs.
- Stallings, W. 2018. Operating Systems: Internals and Design Principles. Edisi ke-9. Pearson. Boston.
