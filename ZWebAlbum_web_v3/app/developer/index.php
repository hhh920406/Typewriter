<!DOCTYPE html>

<html>
    <head>
        <meta charset = "utf-8">
        <title>应用开发</title>
    </head>
    <body>
        <?php
        session_start();
        $username = "";
        if(isset($_GET["username"])) {
            $username = $_GET["username"];
            if(!isset($_SESSION["basic"])) {
                include_once "sdk/apiRequestService.php";
                $api = new ApiRequestService();
                $api->getUserToken($username);
                $basic = $api->getUserBasic();
                $_SESSION["basic"] = $basic;
            }
        }
        include_once "smarty_init.php";
        $tab = "";
        if(isset($_GET["tab"])) {
            $tab = $_GET["tab"];
        }
        $smarty->assign("tab", $tab);
        switch($tab) {
            case "":
                if(isset($_GET["appid"])) {
                    include_once "update.php";
                    $smarty->assign("appid", $_GET["appid"]);
                } else {
                    include_once "see.php";
                    $smarty->assign("appid", 0);
                }
                break;
            case "apply":
                include_once "apply.php";
                break;
            case "doc":
                include_once "doc.php";
                break;
            case "download":
                include_once "download.php";
                break;
        }
        $url = "http://" . $_SERVER["HTTP_HOST"] . $_SERVER["PHP_SELF"] . "?username=" . $username;
        $smarty->assign("url", $url);
        $smarty->display("index.tpl");
        ?>
    </body>
</html>