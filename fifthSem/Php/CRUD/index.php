<?php
include("db.php");
if (isset($_POST["save"])) {
    $name = $_POST["name"];
    $age = (int) $_POST["age"];
    $dept = $_POST["dept"];

    $sql_query = "INSERT INTO students(name, age, department)
                    VALUES ('$name', $age, '$dept')";
    $result = mysqli_query($conn, $sql_query) ? 1 : 0;
    header("Location: index.php?success=$result");
    exit();
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width ,initial-scaling=1.0">
    <title>PHP CRUD</title>
    <link rel="stylesheet" href="style.css">
</head>

<body>
    <!-- For the form part -->
    <h2>Form</h2>
    <div>
        <form method="post" class="container">
            <div class="element"> Name: <input type="text" name="name" required></div>
            <div class="element">Age: <input type="text" name="age" required></div>
            <div class="element"> Department: <input type="text" name="dept" required></div>
            <input type="submit" name="save">
        </form>
    </div>
    <!-- Table part -->
    <h2>Table</h2>
    <div>
        <table>
            <tr>
                <th>id</th>
                <th>name</th>
                <th>age</th>
                <th>department</th>
                <th>Actions</th>
            </tr>
            <?php
            $query = "SELECT * FROM students";
            $result = mysqli_query($conn, $query);
            while ($row = mysqli_fetch_assoc($result)) {
                $id = htmlspecialchars($row["id"]);
                $name = htmlspecialchars($row["name"]);
                $age =htmlspecialchars($row["age"]);
                $dept = htmlspecialchars($row["department"]);
                echo "<tr>
                    <td>$id</td>
                    <td>{$name}</td>
                    <td>{$age}</td> 
                    <td>{$dept}</td>
                    <td><a href='edit.php?id={$id}'>Edit</a> <a href='delete.php?id={$id}'>Delete</a></td>
                    </tr>";
            }
            ?>
        </table>
    </div>
</body>

</html>