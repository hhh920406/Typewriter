<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_album.php";
$userID = Application_Token::getUserID($token);
$name = $_POST["album_name"];
$description = $_POST["album_description"];
$type = $_POST["album_type"];
$albumInfo = array(
    "UserID" => $userID,
    "Name" => $name,
    "Description" => $description,
    "Type" => $type
);
$albumID = Album_Album::insert($albumInfo);
if($albumID != 0) {
    if(!file_exists($_SERVER["DOCUMENT_ROOT"] . "/storage")) {
        mkdir($_SERVER["DOCUMENT_ROOT"] . "/storage");
    }
    if(!file_exists($_SERVER["DOCUMENT_ROOT"] . "/storage/" . $albumID)) {
        mkdir($_SERVER["DOCUMENT_ROOT"] . "/storage/" . $albumID);
    }
}
echo json_encode(array("album_id" => $albumID));
?>
