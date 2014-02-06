<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_album.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";
$albumID = $_POST["album_id"];
$photoID = $_POST["photo_id"];
$photo = Album_Photo::select($photoID);
if(count($photo) == 0)
{
    echo json_encode(array("return" => "false"));
    return;
}
$photo = $photo[0];
$albumInfo = array(
    "PhotoPath" => $photo["PhotoPath"]
);
if(Album_Album::update($albumID, $albumInfo))
{
    echo json_encode(array("return" => "true"));
}
else
{
    echo json_encode(array("return" => "false"));
}
?>
