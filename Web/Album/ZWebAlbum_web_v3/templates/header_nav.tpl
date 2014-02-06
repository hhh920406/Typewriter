<html>
    <head>
        <meta charset="utf-8">
        <title>{%$title%}</title>
        <link rel="stylesheet" href="/css/main/common.css">
        <link rel="stylesheet" href="/css/main/master.css">
    </head>
    <body>
        <div id = "navBar">
            <div id = "navBarLogo">
                Z实验室2013_个人相册管理
            </div>
            <div id = "navBarLinks">
                <ul>
                    {%if $userID%}
                        <li>
                            <a href = "/pages/account/update.php">
                                {%$userNickname%}
                            </a>
                        </li>
                        <li>
                            <a href = "/pages/account/logout.php">
                                退出
                            </a>
                        </li>
                    {%else%}
                        <li style = "color: gray">
                            <a href = "/pages/account/login.php">
                                未登录
                            </a>
                        </li>
                    {%/if%}
                </ul>
            </div>
        </div>