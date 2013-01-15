<?php
    include_once("regex.php");
    include $_SERVER['DOCUMENT_ROOT'].'/pages/data/sql_user.php';

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

    $sql_user = new SQL_User();
    $result = $sql_user->selectByPassword($name, $password);
    if(count($result) != 1)
    {
        echo "用户名或密码不正确";
    }
    else
    {
        session_start();
        $row = $result[0];
        $_SESSION['User_ID'] = $row['UserID'];
        $_SESSION['User_Name'] = $row['Name'];
        $_SESSION['User_Nickname'] = $row['Nickname'];
        $_SESSION['User_Type'] = $row['Type'];
        echo "登录成功";
    }
?>
