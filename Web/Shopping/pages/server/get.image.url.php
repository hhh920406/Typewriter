<?php
/*
 * 获取临时图片的地址。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "setting.php";
if (isset($_GET["token"])) {
    echo json_encode(TEMP_URL . $_GET["token"]);
} else {
    echo json_encode("");
}
?>
