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
switch($result)
{
    case REGISTER_ERROR_NAME:
        echo "用户名格式不合法";
        break;
    case REGISTER_ERROR_PASSWORD:
        echo "密码格式不合法";
        break;
    case REGISTER_ERROR_NICKNAME:
        echo "用户昵称不合法";
        break;
    case REGISTER_ERROR_EXIST:
        echo "用户名已经存在";
        break;
    case REGISTER_ERROR_UNKNOWN:
        echo "注册失败，原因未知";
        break;
}
?>
