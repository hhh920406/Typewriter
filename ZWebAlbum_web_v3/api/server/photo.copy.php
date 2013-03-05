<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_album.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";
if (isset($_POST["album_id"]) && isset($_POST["photo_id"])) {
    $albumID = $_POST["album_id"];
    $photoID = $_POST["photo_id"];
    $photo = Album_Photo::select($photoID);
    if (count($photo) > 0) {
        $photo = $photo[0];
        $photo["AlbumID"] = $albumID;
        echo json_encode(Album_Photo::insert($photoInfo));
    }
}
?>
