<?php
include_once "sql.php";

function isSymbolExist($symbol) {
    $sql = new SQL();
    $sql->query("SELECT * FROM D_Application WHERE Symbol = '" . $symbol . "';");
    $result = $sql->getAllResult();
    return count($result) > 0;
}

function isNameExist($name) {
    $sql = new SQL();
    $sql->query("SELECT * FROM D_Application WHERE Name = '" . $name . "';");
}
?>
