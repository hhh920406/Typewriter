<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <title>用户退出</title>
<head>

<body>
    <?php
        session_start();
        session_destroy();
        setcookie('name', null, time() - 1);
        setcookie('password', null, time() - 1);
        header("Location: /pages/main");
    ?>
</body>

</html>


