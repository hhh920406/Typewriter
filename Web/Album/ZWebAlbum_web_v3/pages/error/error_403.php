<!DOCTYPE html>

<html>
    <head>
        <meta charset = "utf-8">
        <title>403错误</title>
    </head>
    
    <body>
        <?php
            include_once $_SERVER["DOCUMENT_ROOT"] . "/pages/main/init.php";
            $smarty->display("error/error_403.tpl");
        ?>
    </body>
</html>
