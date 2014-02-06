<?php
require_once "ajax_clarify.php";

if (isset($_GET["photoid"]) && isset($_GET["photourl"])) {
    $result = clarify("/app/clarify/exec/Clarify_Color.exe");
    switch ($result) {
        case "0":
            $result = "红色";
            break;
        case "1":
            $result = "橙色";
            break;
        case "2":
            $result = "黄色";
            break;
        case "3":
            $result = "绿色";
            break;
        case "4":
            $result = "青色";
            break;
        case "5":
            $result = "蓝色";
            break;
        case "6":
            $result = "紫色";
            break;
        default:
            $result = "";
            break;
    }
    echo $result;
}
?>
