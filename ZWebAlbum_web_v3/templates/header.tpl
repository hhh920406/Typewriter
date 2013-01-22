<html>
    <head>
        <meta charset="utf-8">
        <title>{$title}</title>
        <link rel="stylesheet" href="/css/main/common.css">
        <link rel="stylesheet" href="/css/main/master.css">
    </head>
    <body>
        <div id = "top">
            <div id = "topLeft">
                Z实验室2013_个人相册管理
            </div>
            <div id = "topRight">
                <ul>
                    {if $userID}
                        <li>
                            <a href = "/pages/account/update">
                                {$userNickname}
                            </a>
                        </li>
                        <li>
                            <a href = "/pages/account/logout">
                                退出
                            </a>
                        </li>
                    {else}
                        <li style = "color: gray">
                            <a href = "/pages/account/login">
                                未登录
                            </a>
                        </li>
                    {/if}
                </ul>
            </div>
        </div>
        <div id = "banner">
        </div>
        <div id = "menu">
            <div class = "menuBlock">
                <ul>
                    <li>
                        <a href = "/pages/main/index">
                            首页
                        </a>
                    </li>
                    <li>
                        <a href = "/pages/album/list">
                            个人主页
                        </a>
                    </li>
                    <li>
                        <a href = "/pages/photo/upload">
                            相册
                        </a>
                    </li>
                    <li>
                        <a href = "/pages/classify/select">
                            应用
                        </a>
                    </li>
                </ul>
            </div>
        </div>
        <div id = "pageBody">
 