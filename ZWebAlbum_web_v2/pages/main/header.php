<?php
    include_once $_SERVER['DOCUMENT_ROOT'].'/pages/account/login_func.php';

    // Try login if cookie exists.
    session_start();
    if(empty($_SESSION['User_ID']))
    {
        if(!empty($_COOKIE['name']))
        {
            $name = $_COOKIE['name'];
            $password = $_COOKIE['password'];
            if(SUCCESSS != login($name, $password))
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

    // Show user nickname, link to update information page.
    function echoUserNickname()
    {
        global $userNickname;
        echo "<li>";
        echo "<a href='/pages/account/update'>";
        echo $userNickname;
        echo "</a>";
        echo "</li>";
    }

    // TODO Judge the user identity.
    function echoManagementTools()
    {
        // @TODO
    }

    // The link to loggout page.
    function echoLogout()
    {
        echo "<li>";
        echo "<a href='/pages/account/logout'>退出</a>";
        echo "</li>";
    }

    // Show unlogin status, link to login page.
    function echoLogin()
    {
        echo "<li style='color: gray'>";
        echo "<a href='/pages/account/login'>未登录</a>";
        echo "</li>";
    }
?>
<div id="top">
<div id="topLeft">Z实验室2013_个人相册管理</div>
<div id="topRight">
    <ul>
        <?php
            if(isset($userID))
            {
                echoUserNickname();
                echoManagementTools();
                echoLogout();
            }
            else
            {
                echoLogin();
            }
        ?>
    </ul>
</div>
</div>
<div id="banner_small"></div>
<div id="menu">
    <div class="menuBlock">
        <ul>
            <li>
                <a href="/pages/main/index">首页</a>
            </li>
            <li>
                <a href="/pages/album/list">个人主页</a>
            </li>
            <li>
                <a href="/pages/photo/upload">相册</a>
            </li>
            <li>
                <a href="/pages/classify/select">应用</a>
            </li>
        </ul>
    </div>
</div>
