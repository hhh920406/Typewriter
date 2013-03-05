<!DOCTYPE html>
<html>
    <head>
        <meta charset = "utf-8">
        <link rel = "stylesheet" href = "css/upload.css">
    </head>
    <body>
        <?php
            /**
             * @author ZHG <CyberZHG@gmail.com>
             */
            $albums = $api->selectAlbums();
            $smarty->assign("albums", $albums);
            $token = $api->getUserTokenWithoutRequest();
            $smarty->assign("token", $token);
            $url = $api->getPostURL();
            $smarty->assign("postUrl", $url);
        ?>
    </body>
</html>