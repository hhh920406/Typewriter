{%include file="header.tpl" title="用户登录"%}
<div id = "loginDiv">
    <div class = "rowInput">
        <div class = "columnText">
            用户名：
        </div>
        <div class = "columnInput">
            <input id = "Text_UserName" type = "text" class = "inputLarge" />
        </div>
    </div>
    
    <div class = "rowInput">
        <div class = "columnText">
            密码：
        </div>
        <div class = "columnInput">
            <input id = "Password_Password" type = "password" class = "inputLarge" />
        </div>
    </div>
    
    <div class = "rowStatus">
        <div class = "columnStatus">
            <input id = "Checkbox_Remember" type = "checkbox" />
            下次自动登录
        </div>
    </div>
    
    <div class = "rowStatus">
        <div class = "columnStatus">
            <div id = "Div_Login"></div>
        </div>
    </div>
    
    <div class = "rowStatus">
        <div class = "columnStatus">
            <input name = "Button_Submit" type = "submit" value = "登　录" class = "buttonBlue" onclick = "userLogin()" />
        </div>
    </div>
    
    <div class = "rowStatus">
        <div class = "columnStatus">
            <input name = "Button_Register" type = "button" value = "注　册" class = "buttonGreen" onclick = "userRegister()" />
        </div>
    </div>
</div>
{%include file="footer.tpl"%}
