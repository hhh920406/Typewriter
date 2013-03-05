<?php
include_once "sdk/apiRequestService.php";
$api = new ApiRequestService();
$photoID = $_GET["photoid"];
$albumID = $_GET["albumid"];
$description = $_GET["description"];
$indice = $_GET["indice"];
$api->updatePhoto($photoID, $albumID, $description, $indice);
?>
