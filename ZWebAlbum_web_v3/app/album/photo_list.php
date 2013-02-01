<!DOCTYPE html>
<html>
    <head>
        <meta charset = "utf-8">
        <link rel = "stylesheet" href = "css/photo_list.css">
    </head>
    <body>
        <?php
            /**
             * @author ZHG <CyberZHG@gmail.com>
             */
            include_once "sdk/apiRequestService.php";
            include_once "util.php";
            $api = new ApiRequestService();
            $albumID = $_GET["albumid"];
            $page = 1;
            $itemPerPage = 12;
            if(isset($_GET["page"])) {
                $page = $_GET["page"];
            }
            $maxPage = (int)(($api->countPhoto($albumID) - 1) / $itemPerPage) + 1;
            $pageURL = "http://" . $_SERVER["HTTP_HOST"] . $_SERVER["PHP_SELF"] .
                "?username=" . $_GET["username"] .
                "&albumid=" . $_GET["albumid"];
            $smarty->assign("page", $page);
            $smarty->assign("maxPage", $maxPage);
            $smarty->assign("pageURL", $pageURL);
            $album = $api->selectAlbumById($albumID);
            $photos = $api->selectPhotos($albumID, ($page - 1) * $itemPerPage, $itemPerPage);
            for($i = 0; $i < count($photos); ++ $i) {
                $photos[$i]->Description = cutStr($photos[$i]->Description, 20);
            }
            $smarty->assign("album", $album);
            $smarty->assign("photos", $photos);
        ?>
    </body>
</html>