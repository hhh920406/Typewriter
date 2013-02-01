<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_album.php";
$userID = Application_Token::getUserID($token);
echo json_encode(array("number" => Album_Album::getAlbumNumber($userID)));
?>
