<?php
include_once "data.php";

$symbol = $_POST["symbol"];
if(isSymbolExist($symbol)) {
    echo "标识已经存在";
    return;
}

$name = $_POST["name"];
if(isNameExist($name)) {
    echo "名称已经存在";
    return;
}

session_start();
$basic = $_SESSION["basic"];

if($_POST["type"] == "Core") {
    if($basic["type"] != "Admin" || $basic["type"] != "Super Admin") {
        echo "用户没有足够的权限";
    }
}

$info = array(
    "id" => $basic["id"],
    "username" => $basic["name"],
    "nickname" => $basic["nickname"],
    "usertype" => $basic["type"],
    "symbol" => $_POST["symbol"],
    "name" => $_POST["name"],
    "description" => $_POST["description"],
    "type" => $_POST["type"]
);

$permission = array();
if($_POST["user_basic"]) {
    $permission[] = 0;
}

if(!applyApplication($info, $permission)) {
    echo "提交出错";
}
?>
