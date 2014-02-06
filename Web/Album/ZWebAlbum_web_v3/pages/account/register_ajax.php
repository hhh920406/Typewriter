<?php
/**
 * The ajax page for user register.
 * @author ZHG <CyberZHG@gmail.com>
 */
include_once $_SERVER['DOCUMENT_ROOT'] . '/api/account/account_user.php';

$name = $_GET["name"];
$password = $_GET["password"];
$nickname = $_GET["nickname"];

$user = array("name" => $name, "password" => $password, "nickname" => $nickname);

$result = Account_User::register($user);
if($result != REGISTER_SUCCESS)
{
    echo Account_User::getRegisterMessage($result);
}
?>
