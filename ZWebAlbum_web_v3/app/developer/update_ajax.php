<?php
include "data.php";
$origin = getApplicationBySymbol($_POST["symbol"]);
if(count($origin) != 1) {
    echo "应用不存在";
    return;
}
$origin = $origin[0];
if($_POST["name"] != $origin["Name"]) {
    if(isNameExist($_POST["name"])) {
        echo "应用名称已经存在";
        return;
    }
}

session_start();
$basic = $_SESSION["basic"];

if($_POST["type"] == "Core") {
    if($basic["type"] != "Admin" || $basic["type"] != "Super Admin") {
        echo "用户没有足够的权限";
        return;
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

if(!updateApplication($origin["ApplicationID"], $info, $permission)) {
    echo "提交出错";
}

?>
