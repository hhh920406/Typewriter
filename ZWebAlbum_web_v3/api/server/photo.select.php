<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";
if(isset($_POST["album_id"]))
{
    $albumID = $_POST["album_id"];
    if(isset($_POST["limit_start"]) && isset($_POST["limit_number"]))
    {
        echo json_encode(Album_Photo::getPhotos($albumID, $_POST["limit_start"], $_POST["limit_number"]));
    }
    else
    {
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
