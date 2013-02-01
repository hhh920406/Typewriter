<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";
if(isset($_POST["album_id"]))
{
    $albumID = $_POST["album_id"];
    echo json_encode(array("number" => Album_Photo::getPhotoNumber($albumID)));
}
?>
