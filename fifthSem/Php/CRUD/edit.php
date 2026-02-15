<?php
include("db.php");

// Fetch the student if ID is in URL
if (isset($_GET["id"])) {
    $id = (int) $_GET["id"]; // cast to int for safety
    $query = "SELECT * FROM students WHERE id = $id";
    $result = mysqli_query($conn, $query);

    if ($result && mysqli_num_rows($result) > 0) {
        $row = mysqli_fetch_assoc($result);
        $name = $row["name"];
        $age = $row["age"];
        $dept = $row["department"];
    } else {
        echo "Student not found!";
        exit();
    }
}
if (isset($_POST["save"])) {
    $name = $_POST["name"];
    $age = (int) $_POST["age"];
    $dept = $_POST["dept"];

    $update_query = "UPDATE students SET name='$name', age=$age, department='$dept' WHERE id=$id";
    mysqli_query($conn, $update_query);

    header("Location: index.php?success=1");
    exit();
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Edit Student</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h2>Edit Student</h2>
    <h3>With id = <?php echo htmlspecialchars($id) ?></h3>
    <form method="post" class="container">
        <div class="element">
            Name: <input type="text" name="name" required value="<?php echo htmlspecialchars($name); ?>">
        </div class="element">
        <div class="element">
            Age: <input type="text" name="age" required value="<?php echo htmlspecialchars($age); ?>">
        </div>
        <div class="element">
            Department: <input type="text" name="dept" required value="<?php echo htmlspecialchars($dept); ?>">
        </div>
        <input type="submit" name="save" value="Update">
    </form>
</body>
</html>
