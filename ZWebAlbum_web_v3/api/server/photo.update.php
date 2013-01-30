<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";
$photoID = $_POST["photo_id"];
$albumID = $_POST["album_id"];
$description = $_POST["photo_description"];
$indice = $_POST["photo_indice"];
$photoInfo = array(
    "AlbumID" => $albumID,
    "Description" => $description,
    "Indice" => $indice
);
if(Album_Photo::update($photoID, $photoInfo))
{
    echo json_encode(array("return" => "true"));
}
else
{
    echo json_encode(array("return" => "false"));
}
?>
