<?php
session_start();
$basic = $_SESSION["basic"];
$smarty->assign("basic", $basic);
?>
