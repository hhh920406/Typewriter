<!DOCTYPE html>
<html>
    <head>
        <meta charset = "utf-8">
        <link rel = "stylesheet" href = "css/album_list.css">
    </head>
    <body>
        <?php
            /**
             * @author ZHG <CyberZHG@gmail.com>
             */
            include_once "util.php";
            $page = 1;
            $itemPerPage = 12;
            if(isset($_GET["page"])) {
                $page = $_GET["page"];
            }
            $maxPage = (int)(($api->countAlbum() - 1) / $itemPerPage) + 1;
            $pageURL = "http://" . $_SERVER["HTTP_HOST"] . $_SERVER["PHP_SELF"] .
                "?username=" . $_GET["username"];
            $smarty->assign("page", $page);
            $smarty->assign("maxPage", $maxPage);
            $smarty->assign("pageURL", $pageURL);
            $albums = $api->selectAlbums(($page - 1) * $itemPerPage, $itemPerPage);
            for($i = 0; $i < count($albums); ++ $i) {
                $albums[$i]->Name = cutStr($albums[$i]->Name, 20);
                $photos = $api->selectPhotos($albums[$i]->AlbumID, 0, 1);
            }
            $smarty->assign("albums", $albums);
        ?>
    </body>
</html>