
<?php
$host_name = "localhost";
$username = "root";
$password = "";
$db_name = "student_crud";

$conn = mysqli_connect($host_name, $username, $password, $db_name);

if(!$conn){
    echo "Error Found :". mysqli_connect_error();
    die();
}
