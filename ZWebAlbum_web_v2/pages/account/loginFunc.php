<?php
    include $_SERVER['DOCUMENT_ROOT'].'/pages/account/regex.php';
    include $_SERVER['DOCUMENT_ROOT'].'/pages/data/sqlQuery.php';
    
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
    
    $database = new Database();
    
    $queryString =     "SELECT * " .
                       "FROM D_User " .
                       "WHERE Name='" . $name . "' AND Password='" . $password . "'";
    $database->query($queryString);
    if($database->getRowNumber() == 0)
    {
        echo "用户名或密码不正确";
    }
    else
    {
        $row = $database->getSingle();
        session_start();
        $_SESSION['User_ID'] = $row['ID'];
        $_SESSION['User_Name'] = $row['Name'];
        $_SESSION['User_Nickname'] = $row['Nickname'];
        $_SESSION['User_Type'] = $row['Type'];
        echo "登录成功";
    }
?>
