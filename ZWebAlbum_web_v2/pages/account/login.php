<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <title>用户登录</title>
    <link rel="stylesheet" href="/css/main/common.css">
    <link rel="stylesheet" href="/css/main/master.css">
    <link rel="stylesheet" href="/css/account/login.css">
    <script src="/js/main/cookie.js"></script>
    <script>
    // Login authentication.
    function userLogin()
    {
        var xmlhttp;
        if(window.XMLHttpRequest)
        {
            xmlhttp = new XMLHttpRequest();
        }
        else
        {
            xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        var name = Text_UserName.value;
        var password = Password_Password.value;
        xmlhttp.onreadystatechange = function()
        {
            if(xmlhttp.readyState == 4 && xmlhttp.status == 200)
            {
                document.getElementById("loginState").innerHTML = xmlhttp.responseText;
                if(xmlhttp.responseText == "登录成功")
                {
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
        xmlhttp.open("GET", "/pages/account/login_ajax.php?name=" + name + "&password=" + password , true);
        xmlhttp.send();
    }

    // Jump to register page.
    function userRegister()
    {
        self.location = "/pages/account/register.php";
    }
    
    // Login on press enter.
    document.onkeyup = function(event)
    {
        var keyCode =  event.keyCode ? event.keyCode : (event.which ? event.which : event.charCode);
        if(keyCode == 13)
        {
            userLogin();
        }
    }
    </script>
</head>

<body>
    <?php include $_SERVER['DOCUMENT_ROOT'].'/pages/main/header.php';?>
    <div id="pageBody">
        <table style="width: 600px; margin: 0 auto;">
            <tr style="height: 40px">
                <td style="width: 100px; text-align: right;">
                    用户名：
                </td>
                <td style="width: 300px;">
                    <input id="Text_UserName" type="text" class="inputLarge" />
                </td>
                <td style="width: 200px;"></td>
            </tr>
            <tr style="height: 40px">
                <td style="text-align: right;">
                    密码：
                </td>
                <td>
                    <input id="Password_Password" type="password" class="inputLarge" />
                </td>
                <td></td>
            </tr>
            <tr style="height: 40px">
                <td></td>
                <td>
                    <input id="Checkbox_Remember" type="checkbox" /> 下次自动登录
                </td>
                <td></td>
            </tr>
            <tr>
                <td></td>
                <td>
                    <span id="loginState" class="errorMessage"></span>
                </td>
                <td></td>
            </tr>
            <tr style="height: 40px">
                <td></td>
                <td>
                    <input name="Button_Submit" type="submit" value="登　录" class="buttonBlue" onclick="userLogin()" />
                </td>
                <td></td>
            </tr>
            <tr style="height: 10px">
            </tr>
            <tr style="height: 40px">
                <td></td>
                <td>
                    <input name="Button_Register" type="button" value="注　册" class="buttonGreen" onclick="userRegister()" />
                </td>
                <td></td>
            </tr>
        </table>
    </div>
    <?php include $_SERVER['DOCUMENT_ROOT'].'/pages/main/footer.php';?>
</body>

</html>
