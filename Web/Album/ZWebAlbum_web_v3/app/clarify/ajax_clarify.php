<?php
/**
 * 分类的基本函数。
 * @author ZHG <CyberZHG@gmail.com>
 */

/**
 * 下载图片到指定位置
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
                fwrite($targetFile, fread($originFile, 1024 * 8), 1024 * 8);
            }
            fclose($targetFile);
            fclose($originFile);
            return true;
        }
    }
    return false;
}

/**
 * 用指定程序进行分类。
 * @param string $exePath
 * @return string 程序返回结果。
 */
function clarify($exePath) {
    set_time_limit(300);
    $url = urldecode($_GET["photourl"]);
    $type = "";
    for ($i = strlen($url) - 1; $i >= 0; -- $i) {
        $type = $url[$i] . $type;
        if ("." == $url[$i]) {
            break;
        }
    }
    $targetPath = $_SERVER["DOCUMENT_ROOT"] . "/app/clarify/exec/tempimage" . $type;
    $result = "";
    if (downloadImage($url, $targetPath)) {
        $exePath = $_SERVER["DOCUMENT_ROOT"] . $exePath;
        $command = $exePath . " " . $targetPath;
        $result = exec($command);
    }
    return $result;
}
?>
