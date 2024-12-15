-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Waktu pembuatan: 15 Des 2024 pada 03.41
-- Versi server: 10.4.25-MariaDB
-- Versi PHP: 8.1.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `anjungantunaiberas`
--

-- --------------------------------------------------------

--
-- Struktur dari tabel `admin`
--

CREATE TABLE `admin` (
  `id` int(11) NOT NULL,
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `admin`
--

INSERT INTO `admin` (`id`, `username`, `password`) VALUES
(1, 'admin', 'admin123');

-- --------------------------------------------------------

--
-- Struktur dari tabel `pengguna`
--

CREATE TABLE `pengguna` (
  `id` int(11) NOT NULL,
  `nama` varchar(255) NOT NULL,
  `nik` varchar(255) NOT NULL,
  `uid` varchar(255) NOT NULL,
  `gender` varchar(255) NOT NULL,
  `alamat` varchar(255) NOT NULL,
  `status` int(11) NOT NULL,
  `tanggal_pengambilan` timestamp NOT NULL DEFAULT current_timestamp(),
  `beras_terambil` int(11) NOT NULL,
  `sisa_beras` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `pengguna`
--

INSERT INTO `pengguna` (`id`, `nama`, `nik`, `uid`, `gender`, `alamat`, `status`, `tanggal_pengambilan`, `beras_terambil`, `sisa_beras`) VALUES
(1, 'Fajar', '352315190', 'A12', 'L', 'Sukolilo', 2, '2024-12-12 14:37:24', 500, 2000),
(2, 'Alkan', '35768494048', 'C26', 'L', 'Sidoarjo', 2, '2024-12-12 14:17:40', 1500, 2000),
(35, 'Pak Taufiq', '35780609870', '04505882052580', 'L', 'Surabaya', 1, '2024-07-26 06:49:55', 2000, 500),
(37, 'meldi', '35768494048', '0484298A4D6080', 'L', 'Bangka', 2, '2024-12-12 14:17:07', 1000, 1500),
(38, 'Khrisna', '35780628675646', '040C43F2F45780', 'L', 'Surabaya', 2, '2024-12-12 15:08:08', 2500, 0),
(39, 'Samsul', '3578640908', '04 86 54 92 CE 28 80', '1', 'Pagesangan Asri X', 0, '2024-12-12 14:21:25', 0, 2500),
(40, 'Kiki', '778787878', 'CFEFC924', 'L', 'Sukolilo', 2, '2024-12-12 23:36:13', 0, 0);

--
-- Trigger `pengguna`
--
DELIMITER $$
CREATE TRIGGER `set_timestamp_before_insert` BEFORE INSERT ON `pengguna` FOR EACH ROW BEGIN
    IF NEW.status = 2 THEN
        SET NEW.tanggal_pengambilan = CURRENT_TIMESTAMP;
    END IF;
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `set_timestamp_before_update` BEFORE UPDATE ON `pengguna` FOR EACH ROW BEGIN
    IF NEW.status = 2 THEN
        SET NEW.tanggal_pengambilan = CURRENT_TIMESTAMP;
    END IF;
END
$$
DELIMITER ;

--
-- Indexes for dumped tables
--

--
-- Indeks untuk tabel `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `pengguna`
--
ALTER TABLE `pengguna`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT untuk tabel yang dibuang
--

--
-- AUTO_INCREMENT untuk tabel `admin`
--
ALTER TABLE `admin`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT untuk tabel `pengguna`
--
ALTER TABLE `pengguna`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=41;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
