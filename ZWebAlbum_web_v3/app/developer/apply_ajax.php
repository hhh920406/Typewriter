<?php
include_once "data.php";

$symbol = $_GET["symbol"];
if(isSymbolExist($symbol)) {
    echo "标识已经存在";
    return;
}

$name = $_GET["name"];
if(isNameExist($name)) {
    echo "名称已经存在";
    return;
}

$info = array(
    "id" => $_GET["id"],
    "symbol" => $_GET["symbol"],
    "name" => $_GET["name"],
    "description" => $_GET["description"],
    "type" => $_GET["type"]
);

$permission = array();
if($_GET["user_basic"]) {
    $permission[] = "user_basic";
}

if(!applyApplication($info, $permission)) {
    echo "提交出错";
}
?>
