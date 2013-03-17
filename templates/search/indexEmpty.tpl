<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商品搜索</title>
        <link rel = stylesheet href = ../../styles/search/indexEmpty.css />
        <script src = ../../scripts/util/jquery.js ></script>
        <script src = ../../scripts/search/setting.js ></script>
        <script src = ../../scripts/search/index.js ></script>
        <script src = ../../scripts/search/indexCanvas.js></script>
    </head>
    <body>
        <input id = Result_Number type = hidden value = 0></input>
        <div class = searchDiv>
            <div class = searchLogo>
                <img src = ../../images/logo.png></img>
            </div>
            <div id = dropbox type = text class = searchText ondragover= "dropOver(event);" ondrop = "dropImage(event);">
                将图片拖放于此或利用右边按钮进行搜索
                <input type = button class = searchImage></input>
            </div>
            <div class = originImageDiv>
                <img id = Img_Origin></img>
            </div>
            <div class = uploadImageDiv>
                <a id = Link_Url href = #>粘贴图片网址</a> | 
                <a id = Link_Upload href = #>上传图片</a>
                <div id = Div_Url>
                    <form action = ../server/server.php id = Form_Url name = Form_Url encType = "multipart/form-data" method = "post">
                        <input name = method type = hidden value = search.image.website></input>
                        <input name = redirect type = hidden value = ZHG></input>
                        <input id = Sync_Start_Price_1 name = start_price type = hidden></input>
                        <input id = Sync_End_Price_1 name = end_price type = hidden></input>
                        <input id = Sync_Keyword_1 name = keyword type = hidden></input>
                        <input id = Sync_Type_1 name = type type = hidden></input>
                        <input id = Sync_Prefer_1 name = prefer type = hidden></input>
                        <input id = Text_Url name = website type = text></input>
                        <input id = Button_Url type = submit value = 搜索></input>
                    </form>
                </div>
                <div id = Div_Upload style = display:none>
                    <form action = ../server/server.php id = Form_Upload name = Form_Upload encType = "multipart/form-data" method = "post">
                        <input name = method type = hidden value = search.image.upload></input>
                        <input name = redirect type = hidden value = ZHG></input>
                        <input id = Sync_Start_Price_2 name = start_price type = hidden></input>
                        <input id = Sync_End_Price_2 name = end_price type = hidden></input>
                        <input id = Sync_Keyword_2 name = keyword type = hidden></input>
                        <input id = Sync_Type_2 name = type type = hidden></input>
                        <input id = Sync_Prefer_2 name = prefer type = hidden></input>
                        <input id = File_Upload name = upload type = file onchange = Form_Upload.submit()></input>
                    </form>
                    <ifame id = Hidden_Frame name = Hidden_Frame style = display:none></ifame>
                </div>
            </div>
            <div class = searchConfigDiv>
                <a id = "Link_Config" href = #>
                    搜索设置
                </a>
            </div>
            <div class = searchConfigDetailDiv>
                <div>
                    <div>
                        <span>价格范围：</span>
                        <input id = Input_Price_Start type = text></input>
                        -
                        <input id = Input_Price_End type = text></input>
                        <span>元</span>
                    </div>
                    <div>
                        <span>关键字：</span>
                        <input id = Input_Keyword type = text></input>
                        <span>（多个关键字用空格分隔）</span>
                    </div>
                    <div>
                        <span>类别：</span>
                        <select id = Select_Type>
                            <option value = null>不限制</option>
                        </select>
                    </div>
                    <div>
                        <div>
                            关注内容：
                        </div>
                        <input id = CheckBox_Shape type = checkbox>形状</input>
                        <input id = CheckBox_Color type = checkbox>颜色</input>
                        <input id = CheckBox_Stripe type = checkbox disabled = disabled>纹理</input>
                    </div>
                </div>
            </div>
        </div>
    </body>
</html>