<!DOCTYPE html>
<html>
    <head>
        <meta charset = "utf-8">
        <link rel = "stylesheet" href = "css/photo.css">
    </head>
    <body>
        <?php
            /**
             * @author ZHG <CyberZHG@gmail.com>
             */
            $albumID = $_GET["albumid"];
            $album = $api->selectAlbumById($albumID);
            $photoNum = $api->countPhoto($albumID);
            $smarty->assign("album", $album);
            $frameURL = "photo_frame.php" .
                "?username=" . $_GET["username"] .
                "&albumid=" . $albumID .
                "&photonum=" . $photoNum .
                "&photopos=" . $_GET["photopos"];
            $smarty->assign("frameURL", $frameURL);
        ?>
    </body>
</html>