<?php
/**
 * The ajax page for login.
 * @author ZHG <CyberZHG@gmail.com>
 */
include_once $_SERVER['DOCUMENT_ROOT'] . '/api/account/account_user.php';

$name = $_GET["name"];
$password = $_GET["password"];

$result = Account_User::login($name, $password);
if($result != LOGIN_SUCCESS)
{
    echo Account_User::getLoginMessage($result);
}
?>
