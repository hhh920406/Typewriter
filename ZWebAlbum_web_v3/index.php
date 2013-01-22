<?php
    /**
     * The index of the website.
     * @author ZHG
     */
    include_once $_SERVER['DOCUMENT_ROOT'].'/api/account/account_user.php';

    // Try login if cookie exists.
    session_start();
    
    $userID = 0;
    $userName = "";
    $userNickname = "";
    $userType = 0;
    
    if(empty($_SESSION['User_ID']))
    {
        if(!empty($_COOKIE['name']))
        {
            $name = $_COOKIE['name'];
            $password = $_COOKIE['password'];
            if(LOGIN_SUCCESSS != Account_User::login($name, $password))
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

    require('Smarty.class.php');
    $smarty = new Smarty;
    //$smarty->force_compile = true;
    $smarty->debugging = true;
    $smarty->caching = true;
    $smarty->cache_lifetime = 120;
    // Assign values and display. 
    $smarty->assign('userID', $userID);
    $smarty->assign('userNickname', $userNickname);
    $smarty->display('index.tpl');
?>
