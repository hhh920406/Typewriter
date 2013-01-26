<?php
include_once $_SERVER['DOCUMENT_ROOT'].'/api/account/account_user.php';
session_start($token);
$basic = array(
    "UserID" => $_SESSION["User_ID"],
    "Name" => $_SESSION["User_Name"],
    "Nickname" => $_SESSION["User_Nickname"],
    "Type" => Account_User::getTypeMessage($_SESSION["User_Type"])
);
echo json_encode($basic);
?>
