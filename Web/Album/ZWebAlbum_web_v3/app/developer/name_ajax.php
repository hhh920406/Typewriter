<?php
include_once "data.php";

$name = $_GET["name"];

if(isNameExist($name)) {
    echo "代号已存在";
}
?>