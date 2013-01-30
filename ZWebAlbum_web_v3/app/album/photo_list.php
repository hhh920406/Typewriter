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
            $album = $api->selectAlbumById($albumID);
            $photos = $api->selectAllPhotos($albumID);
            for($i = 0; $i < count($photos); ++ $i) {
                $photos[$i]->Description = cutStr($photos[$i]->Description, 20);
            }
            $smarty->assign("album", $album);
            $smarty->assign("photos", $photos);
        ?>
    </body>
</html>