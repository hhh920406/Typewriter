<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_album.php";
if(isset($_POST["album_id"]))
{
    $albumID = $_POST["album_id"];
    echo json_encode(Album_Album::select($albumID));
}
else if(isset($_POST["album_name"]))
{
    $userID = Application_Token::getUserID($token);
    $name = $_POST["album_name"];
    echo json_encode(Album_Album::getAlbumByName($userID, $name));
}
else
{
    if(isset($_POST["limit_start"]) && isset($_POST["limit_number"]))
    {
        //TODO
    } 
    else
    {
        $userID = Application_Token::getUserID($token);
        echo json_encode(Album_Album::getAllAlbums($userID));
    }
}
?>
