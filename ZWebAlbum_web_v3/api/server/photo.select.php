<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";
if(isset($_POST["album_id"]))
{
    if(isset($_POST["limit_start"]) && isset($_POST["limit_end"]))
    {
        //TODO
    }
    else
    {
        $albumID = $_POST["album_id"];
        echo json_encode(Album_Photo::getPhotos($albumID));
    }
}
else
{
    if(isset($_POST["photo_id"]))
    {
        $photoID = $_POST["photo_id"];
        echo json_encode(Album_Photo::select($photoID));
    }
}
?>
