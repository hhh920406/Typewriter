<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";
$albumID = $_POST["album_id"];
$description = $_POST["photo_description"];
$path = $_POST["photo_path"];
// TODO Upload the photo.
$photoInfo = array(
    "AlbumID" => $albumID,
    "Description" => $description,
    "PhotoPath" => $path
);
Album_Photo::insert($photoInfo);
echo json_decode(array("album_photo", Album_Photo::getAutoIncrementID()));
?>
