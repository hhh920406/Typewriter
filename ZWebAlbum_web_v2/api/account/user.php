<?php
include_once "regex.php";
include_once $_SERVER['DOCUMENT_ROOT'].'/api/data/sql_user.php';

define("LOGIN_SUCCESS", 0);
define("LOGIN_ERROR_NAME", 1);
define("LOGIN_ERROR_PASSWORD", 2);
define("LOGIN_ERROR_EXIST", 3);
define("LOGIN_ERROR_WRONG", 4);

function login($name, $password)
{
    if(!isTextSimple($name))
    {
        return LOGIN_ERROR_NAME;
    }
    if(!isTextSimple($password))
    {
        return LOGIN_ERROR_PASSWORD;
    }
    $sql_user = new SQL_User();
    $result = $sql_user->selectByPassword($name, $password);
    if(count($result) != 1)
    {
        $result = $sql_user->selectByName($name);
        if(count($result) == 1)
        {
            return ERROR_WRONG;
        }
        return ERROR_EXIST;
    }
    else
    {
        session_start();
        $row = $result[0];
        $_SESSION['User_ID'] = $row['UserID'];
        $_SESSION['User_Name'] = $row['Name'];
        $_SESSION['User_Nickname'] = $row['Nickname'];
        $_SESSION['User_Type'] = $row['Type'];
        return SUCCESS;
    }
}

?>
