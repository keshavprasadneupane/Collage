<?php
include("db.php");

if (isset($_GET["id"])) {
    $id = (int) $_GET["id"];
    $sql_query = "DELETE FROM students WHERE id = $id";
    mysqli_query($conn, $sql_query);

    header("Location: index.php");
    exit();
}