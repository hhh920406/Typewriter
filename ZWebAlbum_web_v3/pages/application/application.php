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
                $apppath = "http://" . $_SERVER["HTTP_HOST"] . "/app/" . $_GET["appname"] . "/index.php?username=" . $_SESSION["User_Name"];
                $smarty->assign("apppath", $apppath);
                include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_application.php";
                $info = Application_Application::getApplicationBySymbol($_GET["appname"]);
                if(count($info) > 0)
                {
                    foreach($info as $row)
                    {
                        $smarty->assign("title", $row["name"]);
                        break;
                    }
                }
            }
            else
            {
                $smarty->assign("apppath", "");
                $smarty->assign("title", "应用");
            }
            $smarty->display("application/application.tpl");
        ?>
    </body>
</html>