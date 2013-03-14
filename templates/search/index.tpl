<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商品搜索</title>
        {if $empty === true}
        <link rel = stylesheet href = ../../styles/search/indexEmpty.css />
        {else}
         <link rel = stylesheet href = ../../styles/search/index.css />
        {/if}
        <script src = ../../scripts/util/jquery.js ></script>
        <scirpt src = ../../scripts/util/jquery.filedrop.js ></scirpt>
        <script src = ../../scripts/search/setting.js ></script>
        <script src = ../../scripts/search/index.js ></script>
    </head>
    <body>
        <input id = Result_Number type = hidden value = 0></input>
        <div class = searchDiv>
            <div class = searchLogo>
                <img src = ../../images/logo.png></img>
            </div>
            <div id = dropbox type = text class = searchText ondragover= "dropOver(event);" ondrop = "dropImage(event);">
                将图片拖放于此或点击右边按钮进行搜索
                <input type = button class = searchImage></input>
            </div>
            <div class = originImageDiv>
                <img id = Img_Origin></img>
            </div>
            <div class = searchConfigDiv>
                <a id = "Link_Config" href = #>
                    搜索设置
                </a>
            </div>
            <div class = uploadImageDiv>
                <a id = Link_Url href = #>粘贴图片网址</a> | 
                <a id = Link_Upload href = #>上传图片</a>
                <div id = Div_Url>
                    <form action = ../server/server.php id = Form_Url name = Form_Url encType = "multipart/form-data" method = "post">
                        <input name = method type = hidden value = search.image.website></input>
                        <input name = redirect type = hidden value = ZHG></input>
                        <input id = Text_Url name = website type = text></input>
                        <input id = Button_Url type = submit value = 搜索></input>
                    </form>
                </div>
                <div id = Div_Upload style = display:none>
                    <form action = ../server/server.php id = Form_Upload name = Form_Upload encType = "multipart/form-data" method = "post">
                        <input name = method type = hidden value = search.image.upload></input>
                        <input name = redirect type = hidden value = ZHG></input>
                        <input id = File_Upload name = upload type = file onchange = Form_Upload.submit()></input>
                    </form>
                    <ifame id = Hidden_Frame name = Hidden_Frame style = display:none></ifame>
                </div>
            </div>
            <div class = searchConfigDetailDiv>
                <div>
                    商品价格范围：
                </div>
                <div>
                    <div>
                        <span>起始价格：</span>
                        <input id = Input_Price_Start type = text></input>
                        <span>元</span>
                    </div>
                    <div>
                        <span>终止价格：</span>
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
                            <option value = 女装>女装</option>
                            <option value = 男装>男装</option>
                            <option value = 女鞋>女鞋</option>
                            <option value = 男鞋>男鞋</option>
                            <option value = 内衣>内衣</option>
                            <option value = 箱包>箱包</option>
                            <option value = 数码>数码</option>
                            <option value = 厨房>厨房</option>
                            <option value = 家电>家电</option>
                            <option value = 手机>手机</option>
                            <option value = 台式机>台式机</option>
                            <option value = 笔记本>笔记本</option>
                            <option value = 电脑>电脑</option>
                            <option value = 家具>家具</option>
                            <option value = 厨房>厨房</option>
                            <option value = 运动>运动</option>
                            <option value = 钟表>钟表</option>
                            <option value = 玩具>玩具</option>
                            <option value = 汽车>汽车</option>
                            <option value = 宠物>宠物</option>
                            <option value = 网络>网络</option>
                            <option value = 书籍>书籍</option>
                        </select> 
                    </div>
                    <div>
                        <span>自定义类别描述：</span>
                        <input id = Input_Type type = text></input>
                    </div>
                    {if $empty === false}
                    <input id = Button_Search type = button value = 搜索></input>
                    {/if}
                </div>
            </div>
        </div>
        <div class = resultDiv>
            <div id = Div_Result_Column_1 class = resultColumnDiv></div>
            <div id = Div_Result_Column_2 class = resultColumnDiv></div>
            <div id = Div_Result_Column_3 class = resultColumnDiv></div>
            <div id = Div_Result_Column_4 class = resultColumnDiv></div>
        </div>
        <div id = Div_Show_Back></div>
        <div id = Div_Show_Image>
            <img id = Img_Show></img>
        </div>
    </body>
</html>