<?php
//Import file config
require 'db.php';

$uid = $_GET['uid'];

//Ambil id
$tampil = mysqli_query($koneksi, "SELECT * FROM pengguna ORDER BY id DESC LIMIT 1");
$hasilku = mysqli_fetch_array($tampil);
$id = $hasilku['id'];

//Input ke id terakhir jika uid kosong
if(empty($hasilku['uid'])){
    $sql = "UPDATE pengguna SET uid='$uid' WHERE id='$id' ";
    if ($koneksi->query($sql) === TRUE) {
        echo "1";
    } else {
        echo "0";
    }
} else {
    echo "2";
}
?>