<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <title>用户登录</title>
    <link rel="stylesheet" href="/css/main/common.css">
    <link rel="stylesheet" href="/css/main/master.css">
    <link rel="stylesheet" href="/css/account/update.css">
</head>
<?php
    include_once $_SERVER["DOCUMENT_ROOT"] . "/pages/main/init.php";
    $smarty->display("account/update.tpl");
?>
