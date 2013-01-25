<!DOCTYPE html>

<html>
    <head>
        <meta charset = "utf-8">
        <link rel = "stylesheet" href = "/css/application/application.css">
        <script src = "/js/application/application.js"></script>
    </head>
    
    <body>
        <?php
            include_once $_SERVER["DOCUMENT_ROOT"] . "/pages/main/init.php";
            browseControl(AUTHORITY_LOGIN);
            if(isset($_GET["appname"]))
            {
                $apppath = "http://" . $_SERVER["HTTP_HOST"] . "/developer/" . $_GET["appname"];
                $smarty->assign("apppath", $apppath);
            }
            else
            {
                $smarty->assign("apppath", "");
            }
            $smarty->display("application/application.tpl");
        ?>
    </body>
</html>