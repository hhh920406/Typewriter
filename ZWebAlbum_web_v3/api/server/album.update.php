<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_album.php";
$albumID = $_POST["album_id"];
$userID = Application_Token::getUserID($token);
$name = $_POST["album_name"];
$descrption = $_POST["album_description"];
$type = $_POST["album_type"];
$indice = $_POST["album_indice"];
$albumInfo = array(
    "Name" => $name,
    "Description" => $description,
    "Type" => $type,
    "Indice" => $indice
);
if(Album_Album::update($albumID, $albumInfo))
{
    echo json_encode(array("return", "true"));
}
else
{
    echo json_encode(array("return", "false"));
}
?>
