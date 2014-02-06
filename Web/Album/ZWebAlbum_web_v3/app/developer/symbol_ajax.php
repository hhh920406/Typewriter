<?php
include_once "data.php";

$symbol = $_GET["symbol"];

if(isSymbolExist($symbol)) {
    echo "代号已存在";
}
?>
