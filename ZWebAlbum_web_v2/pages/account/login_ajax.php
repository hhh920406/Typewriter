<?php
include_once("regex.php");
include_once("login_func.php");

$name = $_GET["name"];
$password = $_GET["password"];

if(!isTextSimple($name))
{
    echo "用户名格式不合法";
    return;
}

if(!isTextSimple($password))
{
    echo "密码格式不合法";
    return;
}

$result = login($name, $password);
switch($result)
{
    case SUCCESS:
        echo "登录成功";
        break;
    case ERROR_EXIST:
        echo "用户名不存在";
        break;
    case ERROR_WRONG:
        echo "用户名或密码错误";
        break;
}
?>
