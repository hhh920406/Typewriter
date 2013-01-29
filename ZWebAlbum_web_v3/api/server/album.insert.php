<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_album.php";
$userID = Application_Token::getUserID($token);
$name = $_POST["album_name"];
$descrption = $_POST["album_description"];
$type = $_POST["album_type"];
//TODO Create the folder
$albumInfo = array(
    "UserID" => $userID,
    "Name" => $name,
    "Description" => $description,
    "Type" => $type
);
Album_Album::insert($albumInfo);
echo json_decode(array("album_id", Album_Album::getAutoIncrementID()));
?>
