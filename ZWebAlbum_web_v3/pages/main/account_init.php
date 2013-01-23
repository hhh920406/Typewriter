<?php
    /**
     * Initial the account information.
     * @author ZHG
     */
    include_once $_SERVER['DOCUMENT_ROOT'].'/api/account/account_user.php';
    
    define("AUTHORITY_ALL", 0);
    define("AUTHORITY_LOGIN", 1);

    $userID = 0;
    $userName = "";
    $userNickname = "";
    $userType = 0;
    
    // Try login if cookie exists.
    if(empty($_SESSION['User_ID']))
    {
        if(!empty($_COOKIE['name']))
        {
            $name = $_COOKIE['name'];
            $password = $_COOKIE['password'];
            if(LOGIN_SUCCESS != Account_User::login($name, $password))
            {
                setcookie('name', null, time() - 1, "/");
                setcookie('password', null, time() - 1, "/");
            }
        }
    }

    // Record user information if the user has login.
    if(!empty($_SESSION['User_ID']))
    {
        $userID = $_SESSION['User_ID'];
        $userName = $_SESSION['User_Name'];
        $userNickname = $_SESSION['User_Nickname'];
        $userType = $_SESSION['User_Type'];
    }
    
    /**
     * Judge if the user has the right authority to browse the page.
     * @param int $authority The authority of the current page.
     */
    function browseControl($authority)
    {
        $_COOKIE["prevPage"] = 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'].'?'.$_SERVER['QUERY_STRING'];
        switch($authority)
        {
            case AUTHORITY_LOGIN:
                header("Location: " . $_SERVER['DOCUMENT_ROOT'] . "/pages/account/login.php");
                break;
        }
    }
?>
