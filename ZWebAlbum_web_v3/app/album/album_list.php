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
            include_once "sdk/apiRequestService.php";
            $api = new ApiRequestService();
            $albums = $api->selectAllAlbums();
            for($i = 0; $i < count($albums); ++ $i) {
                $albums[$i]->Name = cutStr($albums[$i]->Name, 20);
            }
            $smarty->assign("albums", $albums);
        ?>
    </body>
</html>