<!DOCTYPE html>

<html>
    <head>
        <meta charset = "utf-8">
        <link rel = "stylesheet" href = "/css/error/error_404.css">
    </head>
    
    <body>
        <?php
            include_once $_SERVER["DOCUMENT_ROOT"] . "/pages/main/init.php";
            $smarty->display("error/error_404.tpl");
        ?>
    </body>
</html>
