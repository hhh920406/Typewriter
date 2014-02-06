<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_album.php";

$albums = "";
if(isset($_POST["album_id"]))
{
    $albumID = $_POST["album_id"];
    $albums = Album_Album::select($albumID);
}
else
{
    $userID = Application_Token::getUserID($token);
    if(isset($_POST["limit_start"]) && isset($_POST["limit_number"]))
    {
        $albums = Album_Album::getAlbums($userID, $_POST["limit_start"], $_POST["limit_number"]);
    } 
    else
    {    
        $albums = Album_Album::getAlbums($userID);
    }
}
for($i = 0; $i < count($albums); ++ $i)
{
    $albums[$i]["PhotoPath"] = "http://" . $_SERVER["HTTP_HOST"] . $albums[$i]["PhotoPath"];
}
echo json_encode($albums);
?>
