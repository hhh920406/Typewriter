<?php

function getExtension($name)
{
    for($i = strlen($name) - 1; $i >= 0; -- $i)
    {
        if($name[$i] == ".")
        {
            return substr($name, $i, strlen($name) - $i);
        }
    }
    return "";
}

include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/album/album_photo.php";
$albumID = $_POST["album_id"];
$result = array();

for($i = 0; $i < count($_FILES["upload"]["name"]); ++ $i) {
    if($_FILES["upload"]["error"][$i] == UPLOAD_ERR_OK) {
        $name = $_FILES["upload"]["name"][$i];
        $description = $name;
        $extension = getExtension($name);
        $path = "/storage/" . $albumID . "/" . substr(md5(uniqid(mt_rand(), true)), 0, 32) . $extension;
        move_uploaded_file($_FILES["upload"]["tmp_name"][$i], $_SERVER["DOCUMENT_ROOT"] . $path);
        $photoInfo = array(
            "AlbumID" => $albumID,
            "Description" => $description,
            "PhotoPath" => $path
        );
        $result[$name] = Album_Photo::insert($photoInfo);
    } else {
        $result[$name] = 0;
    }
}

echo json_encode($result);
?>
