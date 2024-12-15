<?php
//Import file config
require 'db.php';

//Cek uid
$uid = $_GET['uid'];
$tampil = mysqli_query($koneksi, "SELECT * FROM pengguna WHERE uid='$uid'");
$hasilku = mysqli_fetch_array($tampil);
if(empty($hasilku['status'])){
    echo "0";
} else {
    $status = $hasilku['status'];
    echo $status;
    //Belum ambil
    if($hasilku['status'] == "1"){
        //Update
        $sql = "UPDATE pengguna SET status='2' WHERE uid='$uid' ";
        if ($koneksi->query($sql) === TRUE) {
        } else {
        }
    }
}
?>