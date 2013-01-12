<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <title>用户登录</title>
    <link rel="stylesheet" href="/css/main/common.css">
    <link rel="stylesheet" href="/css/main/master.css">
    <link rel="stylesheet" href="/css/account/login.css">
    <script>
    // 用户登录验证
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
                        document.cookie = "name=" + escape(name);
                        document.cookie = "password=" + escape(password);
                    }
                    var cookie = document.cookie;
                    var cookieArray = cookie.split(";");
                    for(var i=0;i<cookieArray.length;++i)
                    {
                        var value = cookieArray[i].split("=");
                        if("prevPage" == value[0])
                        {
                            window.location.href = value[1];
                        }
                    }
                    window.location.href = "/pages/main/index.php";
                }
            }
        }
        xmlhttp.open("GET", "/pages/account/loginFunc.php?name=" + name + "&password=" + password , true);
        xmlhttp.send();
    }

    // 跳转到注册页面
    function userRegister()
    {
        self.location = "/pages/account/register.php";
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
                    <span id="loginState"></span>
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