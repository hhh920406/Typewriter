<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_album.php";
if(isset($_POST["album_id"]))
{
    $albumID = $_POST["album_id"];
    echo json_encode(Album_Album::select($albumID));
}
else
{
    $userID = Application_Token::getUserID($token);
    if(isset($_POST["limit_start"]) && isset($_POST["limit_number"]))
    {
        echo json_encode(Album_Album::getAlbums($userID, $_POST["limit_start"], $_POST["limit_number"]));
    } 
    else
    {    
        echo json_encode(Album_Album::getAlbums($userID));
    }
}
?>
