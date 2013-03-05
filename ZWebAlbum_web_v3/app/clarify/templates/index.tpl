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
                <div>
                    {foreach item = album from = $albums}
                        <div class = "albumBlockItem">
                            <input type = checkbox value = {$album->AlbumID}>
                                <span>
                                    {$album->Name}
                                </span>
                            </input>
                        </div>
                    {/foreach}
                </div>
                <div>
                    <input type = button id = "Select_All" value = "全选"></input>
                    <input type = button id = "Select_None" value = "取消全选"></input>
                    <input type = button id = "Select_Reverse" value = "反选"></input>
                </div>
            </div>
            <div class = "selectBlock">
                选择分类方式：
                <div>
                    <div id = "Link_Color" class = "selectBlockItem" class = "selectBlockItemColor">
                        <img src = "images/c_color.png" alt = "基于颜色的分类">
                        </img>
                    </div>
                    <div id = "Link_Time" class = "selectBlockItem" class = "selectBlockItemTime">
                        <img src = "images/c_time.png" alt = "基于时间的分类">
                        </img>
                    </div>
                    <div id = "Link_Event" class = "selectBlockItem" class = "selectBlockItemEvent">
                        <img src = "images/c_event.png" alt = "基于事件的分类">
                        </img>
                    </div>
                </div>
            </div>
            <div class = "processBlock">
                正在进行处理
                <div id = "Div_Process"></div>
            </div>
            <div class = "resultBlock">
                分类结果
                <div id = "Div_Result"></div>
                <input type = button id = "Button_Save" value = "保存结果" style = "display: none"></input>
                <input type = button id = "Button_Cancel" value = "取消"></input>
            </div>
            <div class = "textBlock">
                说明：本应用提供对相册图片的分类处理。由于要处理的数据量可能较大，第一次分类时请耐心等待。请确保你的浏览器允许javascript的执行和cookie的记录。
            </div>
            <div class = "cookieBlock">
            </div>
        </div>
    </body>
</html>