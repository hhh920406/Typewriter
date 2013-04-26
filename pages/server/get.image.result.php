<?php
/**
 * 返回查询的结果。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "setting.php";
/**
 * 获取搜索的条件。
 * @return stdClass 搜索条件。
 */
function getCondition() {
    $condition = new stdClass();
    if (isset($_GET["start_price"])) {
        $condition->startPrice = $_GET["start_price"];
    } else {
        $condition->startPrice = "0";
    }
    if (isset($_GET["end_price"])) {
        $condition->endPrice = $_GET["end_price"];
    } else {
        $condition->endPrice = "2000000000";
    }
    if (isset($_GET["seller"])) {
        $condition->seller = $_GET["seller"];
        if ($condition->seller === "null") {
            $condition->seller = "0";
        }
    } else {
        $condition->seller = "0";
    }
    if (isset($_GET["category"])) {
        $condition->category = $_GET["category"];
        if ($condition->category === "null") {
            $condition->category = "0";
        }
    } else {
        $condition->category = "0";
    }
    if (isset($_GET["prefer"])) {
        switch ($_GET["prefer"]) {
        case "100":
            $condition->type = "1";
            break;
        case "010":
            $condition->type = "2";
            break;
        case "001":
            $condition->type = "3";
            break;
        }
    } else {
        $condition->type = "1";
    }
    return $condition;
}

/**
 * 获取缓存文件的名称。
 * @param stdClass 当前的条件。
 * @return type
 */
function getCacheName($condition) {
    $name = json_encode($condition);
    if (isset($_GET["token"])) {
        $name .= $_GET["token"];
    }
    return md5($name) . ".cache";
}

require_once "setting.php";
require_once "../database/SQLQuery.class.php";
if (isset($_GET["token"]) && isset($_GET["index"]) && isset($_GET["number"])) {
    $condition = getCondition();
    $cacheName = getCacheName($condition);
    $cachePath = TEMP_PATH . $cacheName;
    if (!file_exists($cachePath)) {
        $originImagePath = TEMP_PATH . $_GET["token"];
        $command = "{$condition->type},{$condition->startPrice},{$condition->endPrice},{$condition->seller},{$condition->category},{$originImagePath},{$cachePath}";
        exec(FILE_ROOT . "exec/RecordSearch_client.exe " . $command);
    }
    $result = array();
    $file = fopen($cachePath, "r");
    if ($file) {
        $ids = "";
        while (!feof($file)) {
            $ids .= fread($file, 1024);
        }
        $ids = json_decode($ids);
        fclose($file);
        $index = $_GET["index"];
        $number = $_GET["number"];
        for ($i = 0; $i < $number; ++ $i) {
            if ($i + $index >= count($ids)) {
                break;
            }
            $result[] = $ids[$i + $index];
        }
    }
    echo json_encode($result);
    return;
}
echo json_encode(array());
?>
