<?php
include_once "sdk/apiRequestService.php";
$albumID = $_GET["albumid"];
$photoID = $_GET["photoid"];
$api = new ApiRequestService();
$api->setAlbumCover($albumID, $photoID);
?>
