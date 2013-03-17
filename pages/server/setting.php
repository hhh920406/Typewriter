<?php
/*
 * 基本的配置信息。
 * @author ZHG <CyberZHG@gmail.com>
 */

/**
 * 以逗号或空格分割字符串。
 * @param string $str 要分割的字符串。
 * @return string 分割后的结果。
 */
function strSplit($str) {
    $result = array();
    $len = strlen($str);
    $temp = "";
    for ($i = 0; $i < $len; ++$i) {
        if ($str[$i] == "," || $str[$i] == " ") {
            if ($temp) {
                $result[] = $temp;
                $temp = "";
            }
        } else {
            $temp .= $str[$i];
        }
    }
    if ($temp) {
        $result[] = $temp;
    }
    return $result;
}

define("TEMP_URL", "http://localhost/ZShopping_web/temp/search/");
define("TEMP_PATH", "D:/Apache2.2/htdocs/ZShopping_web/temp/search/");
?>
