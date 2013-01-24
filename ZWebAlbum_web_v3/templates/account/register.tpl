{%include file="header.tpl" title="新用户注册"%}
<div id= "registerDiv">
    <div class = "rowInput">
        <div class = "columnText">
            用户名：
        </div>
        <div class = "columnInput">
            <input id = "Text_Name" name = "name" type = "text" class = "inputLarge" onkeyup = "judgeName()"/>
        </div>
        <div class = "columnStatus">
            <div id = "Div_Name"></div>
        </div>
    </div>
    <div class = "rowDescription">
        <div class = "columnDescription">
            用户名的长度为6到20位，只能包含大小写英文字母、数字和下划线。用户名区分大小写。
        </div>
    </div>
        
    <div class = "rowInput">
        <div class = "columnText"></div>
        <div class = "columnInput">
            <input id = "Button_Exist" type = "button" class = "buttonGreen" value = "检测用户名是否存在" disabled = "disabled" onclick = "judgeExist()" />
        </div>
        <div class = "columnStatus">
            <div id = "Div_Exist"></div>
        </div>
    </div>
    
    <div class = "rowInput">
        <div class = "columnText">
            输入密码：
        </div>
        <div class = "columnInput">
            <input id = "Password_Password" name = "password" type = "password" class = "inputLarge" onkeyup = "judgePassword()" />
        </div>
        <div class = "columnStatus">
            <div id = "Div_Password"></div>
        </div>
    </div>
    
    <div class = "rowDescription">
        <div class = "columnDescription">
            密码的长度为6到20位，只能包含大小写英文字母、数字和下划线。密码区分大小写。
        </div>
    </div>
    
    <div class = "rowInput">
        <div class = "columnText">
            确认密码：
        </div>
        <div class = "columnInput">
            <input id = "Password_Confirm" type = "password" class = "inputLarge" onkeyup = "judgeConfirm()" />
        </div>
        <div class = "columnStatus">
            <div id = "Div_Confirm"></div>
        </div>
    </div>
    
    <div class = "rowDescription">
        <div class = "columnDescription">
            两次输入密码必须完全相同。
        </div>
    </div>
    
    <div class = "rowInput">
        <div class = "columnText">
            昵称：
        </div>
        <div class = "columnInput">
            <input id = "Text_Nickname" type = "text" class = "inputLarge" onkeyup = "judgeNickname()" />
        </div>
        <div class = "columnStatus">
            <div id = "Div_Nickname"></div>
        </div>
    </div>
    
    <div class = "rowDescription">
        <div class = "columnDescription">
            昵称可以输入中文，不能为空。
        </div>
    </div>
    
    <div class = "rowInput">
        <div class = "columnText"></div>
        <div class = "columnInput">
            <input id = "Button_Register" type = "button" class = "buttonBlue" value = "注册新用户" onclick="register()" />
        </div>
        <div class = "columnStatus">
            <div id = "Div_Register"></div>
        </div>
    </div>
</div>
{%include file="footer.tpl"%}
