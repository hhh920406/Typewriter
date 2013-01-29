<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>相册</title>
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
                    break;
                case "new":
                    break;
                case "upload":
                    break;
            }
            $url = "http://" . $_SERVER["HTTP_HOST"] . $_SERVER["PHP_SELF"] . "?username=" . $username;
            $smarty->assign("url", $url);
            $smarty->display("index.tpl");
        ?>
    </body>
</html>
