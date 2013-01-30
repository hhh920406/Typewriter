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
            include_once "sdk/apiRequestService.php";
            $api = new ApiRequestService();
            $albumID = $_GET["albumid"];
            $album = $api->selectAlbumById($albumID);
            $photoPos = $_GET["photopos"];
        ?>
    </body>
</html>