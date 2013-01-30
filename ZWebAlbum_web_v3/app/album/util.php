<?php
function cutStr($str, $len) {
    $curLen = 0;
    $totalLen = strlen($str);
    for($i = 0; $i < $totalLen; ++ $i) {
        $ch = ord($str[$i]);
        if($ch < 128) {
            $curLen += 1;
        } else if($ch < 224) {
            $i += 1;
            $curLen += 2;
        } else {
            $i += 2;
            $curLen += 2;
        }
        if($curLen > $len) {
            return substr($str, 0, $i + 1) . "...";
        }
    }
    return $str;
}
?>
