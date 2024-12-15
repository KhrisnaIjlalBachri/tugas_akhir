<?php 
include 'db.php';
// sql to delete a record
$id = $_GET['id'];
$sql = "DELETE FROM pengguna where id='$id'";

if ($koneksi->query($sql) === TRUE) {
    echo "<script>
    alert('Berhasil! Data dihapus.')
    window.location='index.php';
    </script>";
} else {
    echo "<script>
    alert('Gagal! Silahkan coba kembali.')
    window.location='index.php';
    </script>";
}

?>