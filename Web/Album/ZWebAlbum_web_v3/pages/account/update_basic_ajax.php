<?php
/**
 * The ajax page for basic user information update.
 * @author ZHG <CyberZHG@gmail.com>
 */
include_once $_SERVER['DOCUMENT_ROOT'] . '/api/account/account_user.php';

session_start();
$id = $_SESSION["User_ID"];
$name = $_SESSION["User_Name"];
$origin = $_GET["origin"];
$password = $_GET["password"];
$nickname = $_GET["nickname"];

if(0 == Account_User::isPasswordCorrect($name, $origin))
{
    echo "原始密码不正确";
    return;
}

$user = array("password" => $password, "nickname" => $nickname);

$result = Account_User::update($id, $user);
if($result == UPDATE_SUCCESS)
{
    $_SESSION["User_Nickname"] = $nickname;
}
else
{
    echo Account_User::getUpdateMessage($result);
}
?>
