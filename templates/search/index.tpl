<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商品搜索</title>
        <link rel = stylesheet href = ../../styles/search/index.css>
        <script src = ../../scripts/util/jquery.js></script>
        <script src = ../../scripts/search/setting.js></script>
        <script src = ../../scripts/search/index.js></script>
    </head>
    <body>
        <input id = Result_Number type = hidden value = 0></input>
        <div class = searchDiv>
            <input type = text class = searchText disabled = disabled value = "将图片拖放于此或点击右边按钮进行搜索"></input>
            <input type = button class = searchImage></input>
            <div class = originImageDiv>
                <img id = Img_Origin></img>
            </div>
            <div class = searchConfigDiv>
                <a id = "Link_Config" href = #>
                    搜索设置
                </a>
            </div>
        </div>
        <div class = searchConfigDetailDiv>
            <div>
                商品价格范围：
            </div>
            <div>
                <span>起始价格：</span>
                <input id = Input_Price_Start type = text></input>
                <span>终止价格：</span>
                <input id = Input_Price_End type = text></input>
            </div>
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
        <div class = resultDiv>
            <div id = Div_Result_Column_1 class = resultColumnDiv></div>
            <div id = Div_Result_Column_2 class = resultColumnDiv></div>
            <div id = Div_Result_Column_3 class = resultColumnDiv></div>
            <div id = Div_Result_Column_4 class = resultColumnDiv></div>
        </div>
    </body>
</html>