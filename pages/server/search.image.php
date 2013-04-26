<?php
/**
 * 提供用图片搜索的基本方法。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "setting.php";

/**
 * 获得一个唯一的字符串，用来进行搜索的区分。
 * @return string 32位的字符串。
 */
function getTempToken() {
    return substr(md5(uniqid(mt_rand(), true)), 0, 32);
}

/**
 * 通过图片的特征获得唯一的字符串。
 * 图片文件的地址。
 * @return string 32位的字符串。
 */
function getToken($originImagePath) {
    $feature = exec(FILE_ROOT . "exec/EHD_RGB_80.exe " . $originImagePath);
    if ($feature === "-1") {
        return "error";
    }
    return md5($feature);
}

function getRedirectURL($token) {
    $url = "../search/index.php?token=" . $token;
    if (isset($_POST["start_price"])) {
        $url .= "&start_price=" . $_POST["start_price"];
    }
    if (isset($_POST["end_price"])) {
        $url .= "&end_price=" . $_POST["end_price"];
    }
    if (isset($_POST["keyword"])) {
        $url .= "&keyword=" . $_POST["keyword"];
    }
    if (isset($_POST["type"])) {
        $url .= "&type=" . $_POST["type"];
    }
    if (isset($_POST["prefer"])) {
        $url .= "&prefer=" . $_POST["prefer"];
    }
    return $url;
}

/**
 * 下载图片到指定位置。
 * @param string $url 原位置。
 * @param string $targetPath 目的地址。
 * @return boolean 如果成功返回true，否则返回false。
 */
function downloadImage($url, $targetPath) {
    $cp = curl_init($url);
    $fp = fopen($targetPath . ".temp", "w");
    curl_setopt($cp, CURLOPT_FILE, $fp);
    curl_setopt($cp, CURLOPT_HEADER, 0);
    curl_setopt($cp, CURLOPT_TIMEOUT, 10);
    curl_exec($cp);
    fclose($fp);
    $flag = true;
    if (curl_error($cp)) {
        $flag = false;
    } else {
        rename($targetPath . ".temp", $targetPath);
    }
    curl_close($cp);
    return $flag;
}

/**
 * 判断扩展名是否合法。
 * @param string $extension 扩展名
 * @return bool 如果合法返回true。
 */
function isExtensionValid($extension) {
    if ($extension === ".jpg" || 
        $extension === ".jpeg" || 
        $extension === ".bmp" ||
        $extension === ".png" ||
        $extension === ".gif") {
        return true;
    }
    return false;
}
?>
