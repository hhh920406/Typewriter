<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <link rel="stylesheet" href="/css/account/register.css">
        <script src="/js/main/ajax.js"></script>
        <script src="/js/account/register.js"></script>
    </head>

    <body>
        <?php
            include_once $_SERVER["DOCUMENT_ROOT"] . "/pages/main/init.php";
            $smarty->display("account/register.tpl");
        ?>
    </body>
</html>