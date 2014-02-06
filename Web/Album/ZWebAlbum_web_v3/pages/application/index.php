<!DOCTYPE html>

<html>
    <head>
        <meta charset = "utf-8">
    </head>
    
    <body>
        <?php
            include_once $_SERVER["DOCUMENT_ROOT"] . "/pages/main/init.php";
            browseControl(AUTHORITY_LOGIN);
            if(isset($_GET["tab"]))
            {
                $tab = $_GET["tab"];
            }
            else
            {
                $tab = "basic";
            }
            $smarty->assign("tab", $tab);
            $smarty->display("application/index.tpl");
        ?>
    </body>
</html>