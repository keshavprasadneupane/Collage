<?php
session_start();
if (isset($_SESSION['user'])) {
    header("Location: dashboard.php");
    exit;
}

$error = "";

if (isset($_POST["save"])) {
    $username = $_POST['username'];
    $password = $_POST['password'];

    if ($username === 'admin' && $password === '1234') {
        $_SESSION['user'] = $username;

        if (isset($_POST['remember'])) {
            setcookie("user_login", $username, time() + (86400), "/");
        }

        header("Location: dashboard.php");
        exit;
    } else {
        $error = "Invalid username or password!";
    }
}
?>

<!DOCTYPE html>
<html>

<body>
    <h2>Login</h2>
    <?php if ($error)
        echo "<p style='color:red'>$error</p>"; ?>

    <form method="POST">
        Username: <input type="text" name="username" required><br><br>
        Password: <input type="password" name="password" required><br><br>
        <label><input type="checkbox" name="remember"> Remember Me</label><br><br>
        <button type="submit" name="save">Login</button>
    </form>
</body>

</html>