<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";

$photos = "";
if(isset($_POST["album_id"]))
{
    $albumID = $_POST["album_id"];
    if(isset($_POST["limit_start"]) && isset($_POST["limit_number"]))
    {
        $photos = Album_Photo::getPhotos($albumID, $_POST["limit_start"], $_POST["limit_number"]);
    }
    else
    {
        $photos = Album_Photo::getPhotos($albumID);
    }
}
else
{
    if(isset($_POST["photo_id"]))
    {
        $photoID = $_POST["photo_id"];
        $photos = Album_Photo::select($photoID);
    }
}
for($i = 0; $i < count($photos); ++ $i)
{
    $photos[$i]["PhotoPath"] = "http://" . $_SERVER["HTTP_HOST"] . $photos[$i]["PhotoPath"];
}
echo json_encode($photos);
?>
