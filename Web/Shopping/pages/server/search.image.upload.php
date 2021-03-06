<?php
/*
 * 通过上传的图片进行搜索。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "search.image.php";
if ($_FILES["upload"]["error"] === UPLOAD_ERR_OK) {
    $name = $_FILES["upload"]["name"];
    $extension = "";
    for ($i = strlen($name) - 1; $i >= 0; --$i) {
        $extension = $name[$i] . $extension;
        if ($name[$i] === ".") {
            break;
        }
    }
    $extension = strtolower($extension);
    if (isExtensionValid($extension)) {
        $token = getToken();
        $token .= $extension;
        move_uploaded_file($_FILES["upload"]["tmp_name"], TEMP_PATH . $token);
        echo json_encode(array("token" => $token));
        if (isset($_POST["redirect"])) {
            header("Location: " . getRedirectURL($token));
        } 
        return;
    } else {
        echo json_encode(array("错误" => "图片格式不支持。"));
    }
} else {
    echo json_encode(array("错误" => "上传文件失败"));
}
echo json_encode(array("token" => ""));
if (isset($_POST["redirect"])) {
    header("Location: ../search/index2.php");
    return;
} 
?>
