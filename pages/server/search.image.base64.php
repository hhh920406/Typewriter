<?php
/*
 * 传入Base64的数据。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "search.image.php";

if (isset($_POST["image"])) {
    $s = base64_decode(str_replace('data:image/png;base64,', '', $_POST["image"]));
    $extension = ".png";
    $token = getTempToken();
    $token .= $extension;
    file_put_contents(TEMP_PATH . $token, $s);
    $trueToken = getToken(TEMP_PATH . $token) . $extension;
    rename(TEMP_PATH . $token, TEMP_PATH . $trueToken);
    echo json_encode(array("token" => $trueToken));
    if (isset($_POST["redirect"])) {
        header("Location: " . getRedirectURL($trueToken));
        return;
    }
}
if (isset($_POST["redirect"])) {
    header("Location: ../search/index2.php");
    return;
} 
?>
