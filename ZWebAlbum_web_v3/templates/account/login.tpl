{%include file="header.tpl" title="用户登录"%}
<table class = "loginTable">
    <tr class = "rowInput">
        <td class = "columnText">
            用户名：
        </td>
        <td class = "columnInput">
            <input id = "Text_UserName" type = "text" class = "inputLarge" />
        </td>
        <td class = "columnDescription">
        </td>
    </tr>
    <tr class = "rowInput">
        <td class = "columnText">
            密码：
        </td>
        <td>
            <input id = "Password_Password" type = "password" class = "inputLarge" />
        </td>
        <td></td>
    </tr>
    <tr class = "rowInput">
        <td></td>
        <td>
            <input id = "Checkbox_Remember" type = "checkbox" />
            下次自动登录
        </td>
        <td></td>
    </tr>
    <tr>
        <td></td>
        <td>
            <span id = "loginState" class = "errorMessage"></span>
        </td>
        <td></td>
    </tr>
    <tr class = "rowInput">
        <td></td>
        <td>
            <input name = "Button_Submit" type = "submit" value = "登　录" class = "buttonBlue" onclick = "userLogin()" />
        </td>
        <td></td>
    </tr>
    <tr class = "rowInput">
        <td></td>
        <td>
            <input name = "Button_Register" type = "button" value = "注　册" class = "buttonGreen" onclick = "userRegister()" />
        </td>
        <td></td>
    </tr>
</table>
{%include file="footer.tpl"%}
