<?php
require("db.php"); 
                if(isset($_POST['submit'])) {
                        $username = $_POST['username'];
                        $password = $_POST['password'];
                        $tampil = mysqli_query($koneksi, "SELECT * FROM admin WHERE username='$username'");
                        $jumlah = mysqli_num_rows($tampil);     
                        $hasilku = mysqli_fetch_array($tampil);
                        if (empty($jumlah)) {
                            echo "<script>
                            alert('Username tidak terdaftar.')
                            </script>";
                        } else {
                          if($password == $hasilku['password']){
                            session_start();
                            $_SESSION['username'] = $_POST['username']; 
                            echo "<script>
                            alert('Sukses! Selamat datang kembali.')
                            window.location='index.php';
                            </script>";
                          } else {
                            echo "<script>
                            alert('Password salah.')
                            </script>";
                          }                         
                        }
                }
            ?>

<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <link rel="apple-touch-icon" sizes="76x76" href="assets/img/Logo_PENS.png">
  <link rel="icon" type="image/png" href="assets/img/Logo_PENS.png">
  <title>
    Sistem Monitoring Mesin Anjungan Tunai Beras
  </title>
  <!--     Fonts and icons     -->
  <link href="https://fonts.googleapis.com/css?family=Open+Sans:300,400,600,700" rel="stylesheet" />
  <!-- Nucleo Icons -->
  <link href="assets/css/nucleo-icons.css" rel="stylesheet" />
  <link href="assets/css/nucleo-svg.css" rel="stylesheet" />
  <!-- Font Awesome Icons -->
  <script src="https://kit.fontawesome.com/42d5adcbca.js" crossorigin="anonymous"></script>
  <link href="assets/css/nucleo-svg.css" rel="stylesheet" />
  <!-- CSS Files -->
  <link id="pagestyle" href="assets/css/argon-dashboard.css?v=2.0.4" rel="stylesheet" />
</head>

<body class="">
  <main class="main-content  mt-0">
    <section>
      <div class="page-header min-vh-100">
        <div class="container">
          <div class="row">
            <div class="col-xl-4 col-lg-5 col-md-7 d-flex flex-column mx-lg-0 mx-auto">
              <div class="card card-plain">
                <div class="card-header pb-0 text-start">
                  <h4 class="font-weight-bolder">Masuk</h4>
                  <p class="mb-0">Silahkan masuk untuk melanjutkan</p>
                </div>
                <div class="card-body">
                <form method="post" action="login.php">
                    <div class="mb-3">
                      <input type="text" id="username" name="username"class="form-control form-control-lg" placeholder="Username" required>
                    </div>
                    <div class="mb-3">
                      <input type="password" id="password" name="password"class="form-control form-control-lg" placeholder="Password" required>
                    </div>
                    <div class="text-center">
                    <input type="submit" style="color:white" class="btn btn-lg btn-primary btn-lg w-100 mt-4 mb-0" name="submit" value="Masuk">
                    </div>
                  </form>
                </div>
              </div>
            </div>
            <div class="col-6 d-lg-flex d-none h-100 my-auto pe-0 position-absolute top-0 end-0 text-center justify-content-center flex-column">
              <div class="position-relative bg-gradient-primary h-100 m-3 px-7 border-radius-lg d-flex flex-column justify-content-center overflow-hidden" style="background-image: url('backgroundlogin.png');
          background-size: cover;">
                <span class="mask bg-gradient-primary opacity-6"></span>
                <h4 class="mt-5 text-white font-weight-bolder position-relative">"Pembagian Beras Menggunakan Mesin Anjungan Tunai Beras"</h4>
                <p class="text-white position-relative">Sistem monitoring transaksi beras pada Mesin Anjungan Tunai Beras menggunakan website dilengkapi dengan record data dan register.</p>
              </div>
            </div>
          </div>
        </div>
      </div>
    </section>
  </main>
  <!--   Core JS Files   -->
  <script src="assets/js/core/popper.min.js"></script>
  <script src="assets/js/core/bootstrap.min.js"></script>
  <script src="assets/js/plugins/perfect-scrollbar.min.js"></script>
  <script src="assets/js/plugins/smooth-scrollbar.min.js"></script>
  <script>
    var win = navigator.platform.indexOf('Win') > -1;
    if (win && document.querySelector('#sidenav-scrollbar')) {
      var options = {
        damping: '0.5'
      }
      Scrollbar.init(document.querySelector('#sidenav-scrollbar'), options);
    }
  </script>
  <!-- Github buttons -->
  <script async defer src="https://buttons.github.io/buttons.js"></script>
  <!-- Control Center for Soft Dashboard: parallax effects, scripts for the example pages etc -->
  <script src="assets/js/argon-dashboard.min.js?v=2.0.4"></script>
</body>

</html>