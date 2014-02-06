<div id= "updateDiv">
    <div class = "rowInput">
        <div class = "columnText">
            用户名：
        </div>
        <div class = "columnInput">
            <input id = "Text_Name" disabled = "diabled" type = "text" class = "inputLarge" value = {%$userName%} />
        </div>
        <div class = "columnStatus">
            <div id = "Div_Name"></div>
        </div>
    </div>
        
    <div class = "rowInput">
        <div class = "columnText">
            原始密码：
        </div>
        <div class = "columnInput">
            <input id = "Password_Origin" name = "password" type = "password" class = "inputLarge" onkeyup = "basic_judgeOrigin()" />
        </div>
        <div class = "columnStatus">
            <div id = "Div_Origin"></div>
        </div>
    </div>
    
    <div class = "rowInput">
        <div class = "columnText">
            新密码：
        </div>
        <div class = "columnInput">
            <input id = "Password_Password" name = "password" type = "password" class = "inputLarge" onkeyup = "basic_judgePassword()" />
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
            <input id = "Password_Confirm" type = "password" class = "inputLarge" onkeyup = "basic_judgeConfirm()" />
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
            <input id = "Text_Nickname" type = "text" class = "inputLarge" value = {%$userNickname%} onkeyup = "basic_judgeNickname()" />
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
            <input id = "Button_Update" type = "button" class = "buttonBlue" value = "更新信息" onclick="basic_update()" />
        </div>
        <div class = "columnStatus">
            <div id = "Div_Update"></div>
        </div>
    </div>
</div>