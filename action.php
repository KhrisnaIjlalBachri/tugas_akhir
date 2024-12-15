<?php
require("db.php"); 

//Call
$action = $_POST['action'];

//Profil
if($action == "profil"){
    $username = $_POST['username'];
    $password = $_POST['password'];  
    //Update
    $sql = "UPDATE admin SET password='$password' WHERE id='1' ";
    if ($koneksi->query($sql) === TRUE) { 
        echo "<script>
        alert('Berhasil! Data diperbarui.')
        window.location='page_profil.php';
        </script>";
    } else {
        echo "<script>
        alert('Gagal! Silahkan ulangi kembali.')
        window.location='page_profil.php';
        </script>";
    }
}

//Detail
if($action == "detail"){
    $id = $_POST['id'];
    $nik = $_POST['nik'];
    $nama = $_POST['nama'];  
    $gender = $_POST['gender'];
    $alamat = $_POST['alamat'];    
    //Update
    $sql = "UPDATE pengguna SET nama='$nama' , alamat='$alamat' WHERE nik='$nik' ";
    if ($koneksi->query($sql) === TRUE) { 
        echo "<script>
        alert('Berhasil! Data diperbarui.')
        window.location='page_detail.php?id=".$id."';
        </script>";
    } else {
        echo "<script>
        alert('Gagal! Silahkan ulangi kembali.')
        window.location='page_profil.php?id=".$id."';
        </script>";
    }
}

//New
if($action == "new"){
    $nik = $_POST['nik'];
    $nama = $_POST['nama'];  
    $gender = $_POST['gender'];
    $alamat = $_POST['alamat'];    
    $status = 1;
    //Add
    $sql = "INSERT INTO pengguna (nik, nama, gender, alamat, status)
    VALUES ('$nik', '$nama', '$gender', '$alamat', '$status')";

    if ($koneksi->query($sql) === TRUE) {
        echo "<script>
        alert('Berhasil! Silahkan TAP KTP')
        window.location='index.php';
        </script>";
    } else {
        echo "<script>
        alert('Gagal! Silahkan ulangi kembali')
        window.location='index.php';
        </script>";
    }
}