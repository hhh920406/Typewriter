<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_album.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";
if(isset($_POST["album_id"]))
{
    $albumID = $_POST["album_id"];
    if(Album_Photo::deleteAllPhotos($albumID))
    {
        if(Album_Album::delete($albumID))
        {
            echo json_encode(array("return" => "true"));
            return;
        }
    }
}
echo json_encode(array("return" => "false"));
?>
