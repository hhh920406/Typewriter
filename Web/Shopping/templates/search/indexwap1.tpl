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
        <script src = ../../scripts/util/cookie.js></script>
        <script src = ../../scripts/search/setting.js ></script>
        <script src = ../../scripts/search/indexwap1.js></script>
    </head>
    <body>
        <input id = Result_Number type = hidden value = 0></input>
        <div class = menuLineBack>
            <div class = menuLine>
                <a>
                    <img src = ../../images/logo.png class = logo />
                </a>
                <a href = "#" id = Button_Wap_Image class = selected>
                    <img src = ../../images/wap_upload_white.png class = small />
                    上传
                </a>
                <a href = "#" id = Button_Wap_Paint>
                    <img src = ../../images/wap_paint_white.png class = small />
                    绘制
                </a>
                <a href = "#" id = Button_Wap_Setting >
                    <img src = ../../images/wap_setting_white.png />
                    设置
                </a>
                <a href = "#" id = Button_Wap_Result >
                    <img src = ../../images/wap_result_white.png />
                    结果
                </a>
                <a href = "#" id = Button_Wap_History >
                    <img src = ../../images/wap_history_white.png />
                    历史
                </a>
            </div>
        </div>
        
        <div class = searchDiv >
            <div id = Div_Upload_Click >
                <img src = ../../images/wap_upload_sub.png />
                点击上传图片
            </div>
            <input id = File_Upload name = upload type = file></input>
            <ifame id = Hidden_Frame name = Hidden_Frame style = display:none></ifame>
        </div>
        
        <div class = paintDiv >
            <table>
                <tr>
                    <td>
                        <div class = buttonDiv onclick = wPaint_clear(); >
                            <img src = ../../images/wap_clear_white.png />
                            清除图像
                        </div>
                        <div class = buttonDiv onclick = wPaint_upload(); >
                            <img src = ../../images/wap_upload_sub.png />
                            上传图像
                        </div>
                    </td>
                </tr>
                <tr>
                    <td>
                        <div id = wPaint style = "position:relative; width:550px; height:340px; background:#CACACA; border:solid black 1px;"></div>
                    </td>
                </tr>
            </table>
            <script>
                $("#wPaint").width($(window).width() - 20);
                $("#wPaint").height($(window).height() - 220);
            </script>
            <script src = ../../scripts/search/index2sketch.js></script>
        </div>
        
        <div class = settingDiv >
            <div>
                <span>价格范围：</span>
                <br/>
                <input id = Input_Price_Start type = text></input>
                -
                <input id = Input_Price_End type = text></input>
                <span>元</span>
            </div>
            <div>
                <span>商家：</span>
                <br/>
                <select id = Select_Seller>
                    <option value = 0>不限制</option>
                </select>
            </div>
            <div>
                <span>类别：</span>
                <br/>
                <select id = Select_Category>
                    <option value = 0>不限制</option>
                </select>
                <br/>
                <select id = Select_Category_Sub>
                    <option value = 0>不限制</option>
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
            <div class = buttonDiv id = Button_Search>
                <img src = ../../images/wap_search_white.png />
                搜索
            </div>
        </div>
        
        <div class = resultDiv >
            <div id = Div_Result_Column_0 class = resultColumnDiv></div>
        </div>
        
        <div class = historyDiv >
        </div>
        
        <div id = Div_Show_Back></div>
        <div id = Div_Show_Image>
            <img id = Img_Show></img>
        </div>
    </body>
</html>