// Login authentication.
function userLogin()
{
    var xmlhttp = getXMLHttp();
    var name = Text_UserName.value;
    var password = Password_Password.value;
    xmlhttp.onreadystatechange = function()
    {
        if(xmlhttp.readyState == 4 && xmlhttp.status == 200)
        {
            if(xmlhttp.responseText.length > 0)
            {
                setDivText("Div_Login", TYPE_ERROR, xmlhttp.responseText)
            }
            else
            {
                setDivText("Div_Login", TYPE_CORRECT, "登录成功");
                if(Checkbox_Remember.checked)
                {
                    setCookie("name", name);
                    setCookie("password", password);
                }
                var prevPage = getCookie("prevPage");
                if(prevPage != "")
                {
                    window.locaiton.href = prevPage;
                }
                window.location.href = "/pages/main/index.php";
            }
        }
    }
    xmlhttp.open("GET", "/pages/account/login_ajax.php?name=" + name + "&password=" + password);
    xmlhttp.send();
    setDivText("Div_Login", TYPE_WAITING, "登录中。。。");
}

// Jump to register page.
function userRegister()
{
    self.location = "/pages/account/register.php";
}

// Login on pressing enter.
document.onkeyup = function(event)
{
    var keyCode =  event.keyCode ? event.keyCode : (event.which ? event.which : event.charCode);
    if(keyCode == 13)
    {
        userLogin();
    }
}