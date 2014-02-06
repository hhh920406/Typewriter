<?php
include_once "sdk/apiRequestService.php";
$api = new ApiRequestService();
$albumID = $_GET["albumid"];
$name = $_GET["name"];
$description = $_GET["description"];
$type = $_GET["type"];
$indice = $_GET["indice"];
$api->updateAlbum($albumID, $name, $description, $type, $indice);
?>
