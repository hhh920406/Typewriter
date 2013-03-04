<!DOCTYPE html>

<html>
    <head>
        <meta charset = UTF-8>
        <title>图像分类</title>
        <script src = "scripts/jquery.js"></script>
        <script src = "scripts/jquery.cookie.js"></script>
        <script src = "scripts/index.js"></script>
        <link rel = stylesheet href = "styles/index.css">
    </head>
    <body>
        <div class = "mainBlock">
            <div class = "albumBlock">
                选择要进行分类的相册：
                <ul>
                    <li>
                        <input type = button id = "Select_All" value = "全选"></input>
                        <input type = button id = "Select_None" value = "取消全选"></input>
                    </li>
                    <li>
                        <input type = button id = "Select_Reverse" value = "反选"></input>
                    </li>
                </ul>
                <ul>
                    {foreach item = album from = $albums}
                        <li>
                            <input type = checkbox value = {$album->AlbumID}>
                                <span>
                                    {$album->Name}
                                </span>
                            </input>
                        </li>
                    {/foreach}
                </ul>
            </div>
            <div class = "selectBlock">
                选择分类方式：
                <ul>
                    <li id = "Link_Color" class = "color">
                        <img src = "images/c_color.png" alt = "基于颜色的分类">
                        </img>
                    </li>
                    <li id = "Link_Time" class = "time">
                        <img src = "images/c_time.png" alt = "基于时间的分类">
                        </img>
                    </li>
                    <li id = "Link_Event" class = "event">
                        <img src = "images/c_event.png" alt = "基于事件的分类">
                        </img>
                    </li>
                </ul>
            </div>
            <div class = "processBlock">
                正在进行处理
                <ul id = "UL_Process"></ul>
            </div>
            <div class = "textBlock">
                说明：本应用提供对相册图片的分类处理。由于要处理的数据量可能较大，第一次分类时请耐心等待。请确保你的浏览器允许javascript的执行和cookie的记录。
            </div>
    </div>
    </body>
</html>