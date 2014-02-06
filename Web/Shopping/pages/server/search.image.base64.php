<?php
/*
 * 传入Base64的数据。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "search.image.php";

if (isset($_POST["image"])) {
    $s = base64_decode(str_replace('data:image/png;base64,', '', $_POST["image"]));
    $extension = ".png";
    $token = getToken();
    $token .= $extension;
    file_put_contents(TEMP_PATH . $token, $s);
    rename(TEMP_PATH . $token, TEMP_PATH . $token);
    echo json_encode(array("token" => $token));
    if (isset($_POST["redirect"])) {
        header("Location: " . getRedirectURL($token));
        return;
    }
}
if (isset($_POST["redirect"])) {
    header("Location: ../search/index2.php");
    return;
} 
?>
