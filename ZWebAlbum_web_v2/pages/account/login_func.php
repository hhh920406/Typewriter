<?php
include_once $_SERVER['DOCUMENT_ROOT'].'/api/data/sql_user.php';

define("SUCCESS", 0);
define("ERROR_EXIST", 1);
define("ERROR_WRONG", 2);

function login($name, $password)
{
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
