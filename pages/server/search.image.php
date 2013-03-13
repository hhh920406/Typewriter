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

/**
 * 下载图片到指定位置。
 * @param string $url 原位置。
 * @param string $targetPath 目的地址。
 * @return boolean 如果成功返回true，否则返回false。
 */
function downloadImage($url, $targetPath) {
    $originFile = fopen($url, "rb");
    if ($originFile) {
        $targetFile = fopen($targetPath, "wb");
        if ($targetFile) {
            while (!feof($originFile)) {
                fwrite($targetFile, fread($originFile, 1024 * 4), 1024 * 4);
            }
            fclose($targetFile);
            fclose($originFile);
            return true;
        }
    }
    return false;
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
