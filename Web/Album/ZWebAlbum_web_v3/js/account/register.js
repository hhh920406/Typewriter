/**
 * Deal with user register page.
 * @author ZHG <CyberZHG@gmail.com>
 */


/**
 * Judge if the string contains only numbers, upper and lower English characters, and underscores.
 * @param value The input string.
 * @return boolean The boolean result.
 */
function isTextSimple(value)
{
    for(var i = 0; i < value.length; ++ i)
    {
        if(value[i] >= '0' && value[i] <= '9')
        {
            continue;
        }
        if(value[i] >= 'a' && value[i] <= 'z')
        {
            continue;
        }
        if(value[i] >= 'A' && value[i] <= 'Z')
        {
            continue;
        }
        if(value[i] == '_')
        {
            continue;
        }
        return false;
    }
    return true;
}

/**
 * Judge if the user name is valid.
 * @return boolean Return true if valid.
 */
function judgeName()
{
    var name = document.getElementById("Text_Name").value;
    clearDivText("Div_Name");
    var button = document.getElementById("Button_Exist");
    setInputEnabled(button, false);
    if(name.length < 6)
    {
        setDivText("Div_Name", TYPE_ERROR, "用户名过短");
        return false;
    }
    if(name.length > 20)
    {
        setDivText("Div_Name", TYPE_ERROR, "用户名过长");
        return false;
    }
    if(isTextSimple(name))
    {
        setDivText("Div_Name", TYPE_CORRECT, "");
        setInputEnabled(button, true);
        return true;
    }
    else
    {
        setDivText("Div_Name", TYPE_ERROR, "用户名不合法");
        return false;
    }
}

/**
 * Judge if the user name is existed.
 * @return boolean Return true if valid.
 */
function judgeExist()
{
    var name = document.getElementById("Text_Name").value;
    clearDivText("Div_Exist");
    var xmlhttp = getXMLHttp();
    xmlhttp.onreadystatechange = function()
    {
        if(xmlhttp.readyState == 4 && xmlhttp.status == 200)
        {
            if(xmlhttp.responseText.length > 0)
            {
                setDivText("Div_Exist", TYPE_ERROR, xmlhttp.responseText);
            }
            else
            {
                setDivText("Div_Exist", TYPE_CORRECT, "");
            }
        }
    }
    xmlhttp.open("GET", "register_exist_ajax.php?name=" + name);
    xmlhttp.send();
    setDivText("Div_Exist", TYPE_WAITING, "查询中。。。");
}

/**
 * Judge if the password is valid.
 * @return boolean Return true if valid.
 */
function judgePassword()
{
    var password = document.getElementById("Password_Password").value;
    clearDivText("Div_Password");
    if(password.length < 6)
    {
        setDivText("Div_Password", TYPE_ERROR, "密码过短");
        return false;
    }
    if(password.length > 20)
    {
        setDivText("Div_Password", TYPE_ERROR, "密码过长");
        return false;
    }
    if(isTextSimple(password))
    {
        setDivText("Div_Password", TYPE_CORRECT, "");
        return true;
    }
    else
    {
        setDivText("Div_Password", TYPE_ERROR, "密码不合法");
        return false;
    }
}

/**
 * Judge if the passwords typed are same.
 * @return boolean Return true if valid.
 */
function judgeConfirm()
{
    var password = document.getElementById("Password_Password").value;
    var confirm = document.getElementById("Password_Confirm").value;
    clearDivText("Div_Confirm");
    if(confirm.length > 0 && password == confirm)
    {
        setDivText("Div_Confirm", TYPE_CORRECT, "");
        return true;
    }
    else
    {
        if(confirm.length > 0)
        {
            setDivText("Div_Confirm", TYPE_ERROR, "两次输入密码不同");
        }
        else
        {
            setDivText("Div_Confirm", TYPE_ERROR, "未输入密码");
        }
        return false;
    }
}

/**
 * Judge if the nickname is valid.
 * @return boolean Return true if valid.
 */
function judgeNickname()
{
    var nickname = document.getElementById("Text_Nickname").value;
    clearDivText("Div_Nickname");
    if(nickname.length > 0)
    {
        setDivText("Div_Nickname", TYPE_CORRECT, "");
        return true;
    }
    else
    {
        setDivText("Div_Nickname", TYPE_ERROR, "昵称不能为空");
        return false;
    }
}

/**
 * Register user. 
 */
function register()
{
    clearDivText("Div_Register");
    var flag = true;
    flag &= judgeName();
    flag &= judgePassword();
    flag &= judgeConfirm();
    flag &= judgeNickname();
    if(!flag)
    {
        return;
    }
    var name = document.getElementById("Text_Name").value;
    var password = document.getElementById("Password_Password").value;
    var nickname = document.getElementById("Text_Nickname").value;
    var xmlhttp = getXMLHttp();
    xmlhttp.onreadystatechange = function()
    {
        if(xmlhttp.readyState == 4 && xmlhttp.status == 200)
        {
            if(xmlhttp.responseText.length > 0)
            {
                setDivText("Div_Register", TYPE_ERROR, xmlhttp.responseText);
            }
            else
            {
                setDivText("Div_Register", TYPE_CORRECT, "注册成功");
                window.location.href = "/pages/account/login.php";
            }
        }
    }
    xmlhttp.open("GET", "register_ajax.php?name=" + name + "&password=" + password + "&nickname=" + nickname);
    xmlhttp.send();
    setDivText("Div_Register", TYPE_WAITING, "提交中。。。");
}

// Register on pressing enter.
document.onkeyup = function(event)
{
    var keyCode =  event.keyCode ? event.keyCode : (event.which ? event.which : event.charCode);
    if(keyCode == 13)
    {
        register();
    }
}