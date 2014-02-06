<?php
include_once "sdk/apiRequestService.php";
$name = $_GET["name"];
$description = $_GET["description"];
$api = new ApiRequestService();
echo $api->insertAlbum($name, $description, 0);
?>
