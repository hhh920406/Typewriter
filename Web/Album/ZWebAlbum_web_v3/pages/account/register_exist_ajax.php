<?php
/**
 * The ajax page for judging if the user name is exist.
 * @author ZHG <CyberZHG@gmail.com>
 */
include_once $_SERVER['DOCUMENT_ROOT'] . '/api/account/account_user.php';

$name = $_GET["name"];
$result = Account_User::isUserNameExist($name);
if($result)
{
    echo "用户名已经存在";
}
?>
