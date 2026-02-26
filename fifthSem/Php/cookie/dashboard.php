<?php
session_start();

if (!isset($_SESSION['user'])) {
    header("Location: index.php");
    exit;
}
?>

<!DOCTYPE html>
<html>

<body>
    <h2>Dashboard</h2>
    <p>Welcome, <b>
            <?php echo $_SESSION['user']; ?>
        </b>!</p>

    <p>Your session ID is:
        <?php echo session_id(); ?>
    </p>
    <a href="logout.php">Click here to Logout</a>
</body>

</html>