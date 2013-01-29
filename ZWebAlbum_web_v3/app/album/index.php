<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>相册</title>
    </head>
    <body>
        <?php
            /**
             * @author ZHG <CyberZHG@gmail.com>
             */
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
            $tabsub = "";
            switch($tab) {
                case "":
                    if(isset($_GET["photoid"])) {
                        include_once "photo_list.php";
                        $tabsub = "photo_list";
                    } else if(isset($_GET["albumid"])) {
                        include_once "photo.php";
                        $tabsub = "photo";
                    } else {
                        include_once "album_list.php";
                        $tabsub = "album_list";
                    }
                    break;
                case "new":
                    include_once "new.php";
                    break;
                case "upload":
                    include_once "upload.php";
                    break;
            }
            $smarty->assign("tabsub", $tabsub);
            $url = "http://" . $_SERVER["HTTP_HOST"] . $_SERVER["PHP_SELF"] . "?username=" . $username;
            $smarty->assign("url", $url);
            $smarty->display("index.tpl");
        ?>
    </body>
</html>
