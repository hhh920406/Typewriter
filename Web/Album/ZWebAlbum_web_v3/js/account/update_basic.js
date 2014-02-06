/**
 * The scripts for update basic user information.
 * @author ZHG <CyberZHG@gmail.com>
 */

/**
 * Judge if the string contains only numbers, upper and lower English characters, and underscores.
 * @param text The input string.
 * @return boolean The boolean result.
 */
function isTextSimple(text)
{
    for(var i = 0; i < text.length; ++ i)
    {
        if(text[i] < '0' || text[i] > '9')
        {
            if(text[i] < 'a' || text[i] > 'z')
            {
                if(text[i] < 'A' || text[i] > 'Z')
                {
                    if(text[i] != '_')
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

/**
 * Judge if the password is valid.
 * @return boolean Return true if valid.
 */
function basic_judgeOrigin()
{
    var password = document.getElementById("Password_Origin").value;
    clearDivText("Div_Origin");
    if(password.length < 6)
    {
        setDivText("Div_Origin", TYPE_ERROR, "密码过短");
        return false;
    }
    if(password.length > 20)
    {
        setDivText("Div_Origin", TYPE_ERROR, "密码过长");
        return false;
    }
    if(isTextSimple(password))
    {
        setDivText("Div_Origin", TYPE_CORRECT, "");
        return true;
    }
    else
    {
        setDivText("Div_Origin", TYPE_ERROR, "密码格式不合法");
        return false;
    }
}

/**
 * Judge if the password is valid.
 * @return boolean Return true if valid.
 */
function basic_judgePassword()
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
        setDivText("Div_Password", TYPE_ERROR, "密码格式不合法");
        return false;
    }
}

/**
 * Judge if the two password typed are same.
 * @return boolean Return true if valid.
 */
function basic_judgeConfirm()
{
    var password = document.getElementById("Password_Password").value;
    var confirm = document.getElementById("Password_Confirm").value;
    clearDivText("Div_Confirm");
    if(password.length > 0 && password == confirm)
    {
        setDivText("Div_Confirm", TYPE_CORRECT, "");
        return true;
    }
    else
    {
        if(password.length > 0)
        {
            setDivText("Div_Confirm", TYPE_ERROR, "两次输入密码不一致");
        }
        else
        {
            setDivText("Div_Confirm", TYPE_ERROR, "没输入密码");
        }
        return false;
    }
}

/**
 * Judge if the nickname is valid.
 * @return boolean Return true if valid.
 */
function basic_judgeNickname()
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
        setDivText("Div_Nickname", TYPE_ERROR, "");
        return false;
    }
}

function basic_update()
{
    clearDivText("Div_Update");
    var flag = true;
    flag &= basic_judgeOrigin();
    flag &= basic_judgePassword();
    flag &= basic_judgeConfirm();
    flag &= basic_judgeNickname();
    if(!flag)
    {
        return;
    }
    var origin = document.getElementById("Password_Origin").value;
    var password = document.getElementById("Password_Password").value;
    var nickname = document.getElementById("Text_Nickname").value;
    var xmlhttp = getXMLHttp();
    xmlhttp.onreadystatechange = function()
    {
        if(xmlhttp.readyState == 4 && xmlhttp.status == 200)
        {
            if(xmlhttp.responseText.length > 0)
            {
                setDivText("Div_Update", TYPE_ERROR, xmlhttp.responseText);
            }
            else
            {
                setDivText("Div_Update", TYPE_CORRECT, "更新成功");
            }
        }
    }
    xmlhttp.open("GET", "update_basic_ajax.php?origin=" + origin + "&password=" + password + "&nickname=" + nickname);
    xmlhttp.send();
    setDivText("Div_Update", TYPE_WAITING, "提交中。。。");
}