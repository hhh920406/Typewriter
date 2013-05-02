<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商品搜索</title>
        <link rel = stylesheet href = ../../styles/search/indexwap.css />
        <!-- wPaint -->
        <script src = ./wpaint/inc/jquery.1.8.2.min.js ></script>
        <script src = ./wpaint/inc/jquery.ui.core.min.js ></script>
        <script src = ./wpaint/inc/jquery.ui.widget.min.js ></script>
        <script src = ./wpaint/inc/jquery.ui.mouse.min.js ></script>
        <script src = ./wpaint/inc/jquery.ui.draggable.min.js ></script>
        <script src = ./wpaint/inc/wColorPicker.js ></script>
        <script src = ./wpaint/wPaint.js ></script>
        <link rel = stylesheet href = ./wpaint/inc/wColorPicker.css />
        <link rel = stylesheet href = ./wpaint/wPaint.css />
        <!-- wPaint -->
        <script src = ../../scripts/search/setting.js ></script>
        <script src = ../../scripts/search/index2.js ></script>
        <script src = ../../scripts/search/indexwap1.js></script>
    </head>
    <body>
        <input id = Result_Number type = hidden value = 0></input>
        <div class = searchLogo>
            <img src = ../../images/logo.png></img>
        </div>
        <input type = button id = Button_Wap_Image class = lineButton value = 添加图片></input>
        <div class = searchDiv >
            <div class = uploadImageDiv>
                <a id = Link_Url href = #>粘贴图片网址</a> | 
                <a id = Link_Upload href = #>上传图片</a> |
                <a id = Link_Sketch href = #>绘制轮廓</a>
                <div id = Div_Url>
                    <input id = Text_Url name = website type = text></input>
                    <input id = Button_Url type = submit value = 搜索></input>
                </div>
                <div id = Div_Upload style = display:none>
                    <input id = File_Upload name = upload type = file></input>
                    <ifame id = Hidden_Frame name = Hidden_Frame style = display:none></ifame>
                </div>
                <div id = Div_Sketch style = display:none>
                    <table>
                        <tr>
                            <td>
                                <div id = wPaint style = "position:relative; width:700px; height:500px; background:#CACACA; border:solid black 1px;"></div>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <input type = button value = 清除画布 onclick = wPaint_clear(); />
                                <input type = button value = 上传图像 onclick = wPaint_upload(); />
                            </td>
                        </tr>
                    </table>
                    <script src = ../../scripts/search/index2sketch.js></script>
                </div>
            </div>
        </div>
        <input type = button id = Button_Wap_Setting class = lineButton value = 搜索设置 ></input>
        <div id = settingDiv >
            <div>
                <div>
                    <span>价格范围：</span>
                    <input id = Input_Price_Start type = text></input>
                    -
                    <input id = Input_Price_End type = text></input>
                    <span>元</span>
                </div>
                <div>
                    <span>商家：</span>
                    <select id = Select_Seller style = max-width:200px>
                        <option value = null>不限制</option>
                    </select>
                </div>
                <div>
                    <span>类别：</span>
                    <select id = Select_Category style = max-width:200px>
                        <option value = null>不限制</option>
                    </select>
                </div>
                <div>
                    <div>
                        关注内容：
                    </div>
                    <input id = CheckBox_Shape type = checkbox>形状</input>
                    <input id = CheckBox_Color type = checkbox>颜色</input>
                    <input id = CheckBox_Stripe type = checkbox>轮廓</input>
                </div>
            </div>
            <input id = Button_Search type = button value = 搜索></input>
        </div>
        <input type = button id = Button_Wap_Result class = lineButton value = 搜索结果></input>
        <div class = resultDiv >
            <div id = Div_Result_Column_0 class = resultColumnDiv></div>
        </div>
        <div id = Div_Show_Back></div>
        <div id = Div_Show_Image>
            <img id = Img_Show></img>
        </div>
    </body>
</html>