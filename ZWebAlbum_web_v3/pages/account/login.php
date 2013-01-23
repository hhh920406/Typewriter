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

<?php
    include_once $_SERVER["DOCUMENT_ROOT"] . "/pages/main/init.php";
    $smarty->display("account/login.tpl");
?>