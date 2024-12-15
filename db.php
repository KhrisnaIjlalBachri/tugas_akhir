<?php

//Koneksi SQL
$servername = "localhost";
$dbname = "anjungantunaiberas";
$username = "root";
$password = "";

//Menghubungkan ke SQL
$koneksi = new mysqli($servername, $username, $password, $dbname);
if ($koneksi->connect_error) {
    die("Koneksi gagal: " . $koneksi->connect_error);
} 

?>