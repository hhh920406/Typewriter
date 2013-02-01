<!DOCTYPE html>

<html>
    <head>
        <meta charset = "utf-8">
        <link rel = "stylesheet" href = "css/photo_frame.css">
    </head>

    <body>
        <?php
            include_once "smarty_init.php";
            include_once "sdk/apiRequestService.php";
            $api = new ApiRequestService();
            $albumID = $_GET["albumid"];
            $photoNum = $_GET["photonum"];
            $photoPos = $_GET["photopos"];
            $smarty->assign("albumID", $albumID);
            $smarty->assign("photoPos", $photoPos);
            $smarty->assign("photoNum", $photoNum);

            $prevPos = $photoPos - 1;
            if($prevPos < 0) {
                $prevPos = $photoNum - 1;
            }
            $nextPos = $photoPos + 1;
            if($nextPos >= $photoNum) {
                $nextPos = 0;
            }

            function selectSingle($photos) {
                if(count($photos)) {
                    $photo = $photos[0];
                    $photo->EditDescription = "'" . $photo->Description . "'";
                    return $photos[0];
                }
                $photo = new stdClass();
                $photo->PhotoID = 0;
                $photo->PhotoPath = "Not Found";
                $photo->PhotoDescription = "Photo doesn't exist. ";
                $photo->EditDescription = "'" . $photo->EditDescription . "'";
            }

            $photo = $api->selectPhotos($albumID, $photoPos, 1);
            $photo = selectSingle($photo);
            $smarty->assign("photo", $photo);
            $smarty->assign("prevPos", $prevPos);
            $smarty->assign("nextPos", $nextPos);
            $pageURL = "http://" . $_SERVER["HTTP_HOST"] . $_SERVER["PHP_SELF"] .
                "?username=" . $_GET["username"] .
                "&photonum=" . $photoNum .
                "&albumid=" . $albumID;
            $smarty->assign("pageURL", $pageURL);
            $smarty->display("photo_frame.tpl");
        ?>
    </body>
</html>