<!DOCTYPE html>
<html>

<head>
    <meta charset = "utf-8">
    <link rel = "stylesheet" href = "/css/account/login.css">
    <script src = "/js/main/cookie.js"></script>
    <script src = "/js/main/ajax.js"></script>
    <script src = "/js/account/login.js"></script>
</head>

<?php
    include_once $_SERVER["DOCUMENT_ROOT"] . "/pages/main/init.php";
    $smarty->display("account/login.tpl");
?>