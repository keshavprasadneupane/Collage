<?php
session_start();

// 1. Clear Session
session_unset();
session_destroy();

// 2. Expire the Cookie (set time to the past)
if (isset($_COOKIE['user_login'])) {
    setcookie("user_login", "", time() - 3600, "/");
}

header("Location: index.php");
exit;