<?php
require_once "ajax_clarify.php";

if (isset($_GET["photoid"]) && isset($_GET["photourl"])) {
    $result = clarify("/app/clarify/exec/Clarify_Event.exe");
    echo $result;
}
?>
