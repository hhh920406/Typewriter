<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";
if(isset($_POST["photo_id"]))
{
    $photoID = $_POST["photo_id"];
    if(Album_Photo::delete($photoID))
    {
        echo json_encode(array("return", "true"));
        return;
    }
}
echo json_encode(array("return", "true"));
?>
