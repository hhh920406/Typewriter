<!DOCTYPE html>
<html>

<head>
    <meta charset = "utf-8">
    <link rel = "stylesheet" href = "/css/account/update.css">
    <script src="/js/main/ajax.js"></script>
    <script src="/js/account/update_basic.js"></script>
</head>
<?php
    include_once $_SERVER["DOCUMENT_ROOT"] . "/pages/main/init.php";
    if(isset($_GET["tab"]))
    {
        $tab = $_GET["tab"];
    }
    else
    {
        $tab = "basic";
    }
    $smarty->assign("tab", $tab);
    $smarty->assign("userName", $userName);
    $smarty->display("account/update.tpl");
?>
