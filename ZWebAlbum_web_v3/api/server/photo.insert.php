<?php

function getExtension($name)
{
    for($i = count($name) - 1; $i >= 0; -- $i)
    {
        if($name[$i] == ".")
        {
            return substr($name, $i, count($name) - $i);
        }
    }
    return "";
}

include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";
$albumID = $_POST["album_id"];

if($_FILES["upload"]["error"] == UPLOAD_ERR_OK)
{
    $description = $_FILES["upload"]["name"];
    $extension = getExtension($_FILES["upload"]["name"]);
    $tempPath = $_SERVER["DOCUMENT_ROOT"] . "/temp/" . $_FILES["upload"]["tmp_name"];
    $path = $_SERVER["DOCUMENT_ROOT"] . "/storage/" . $albumID . "/" . substr(md5(uniqid(mt_rand(), true)), 0, 32) . $extension;
    copy($tempPath, $path);
    $photoInfo = array(
        "AlbumID" => $albumID,
        "Description" => $description,
        "PhotoPath" => $path
    );
    echo json_encode(array("photo_id" => Album_Photo::insert($photoInfo)));
}
else
{
    echo json_encode(array("photo_id" => 0));
}

?>
