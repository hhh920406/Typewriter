<?php
/**
 * The ajax page for login.
 * @author ZHG <CyberZHG@gmail.com>
 */
include_once $_SERVER['DOCUMENT_ROOT'] . '/api/account/account_user.php';

$name = $_GET["name"];
$password = $_GET["password"];

$result = Account_User::login($name, $password);
switch($result)
{
    case LOGIN_SUCCESS:
        echo "登录成功";
        break;
    case LOGIN_ERROR_NAME:
        echo "用户名格式不合法";
        break;
    case LOGIN_ERROR_PASSWORD:
        echo "密码格式不合法";
        break;
    case LOGIN_ERROR_EXIST:
        echo "用户名不存在";
        break;
    case LOGIN_ERROR_WRONG:
        echo "用户名或密码错误";
        break;
}
?>
