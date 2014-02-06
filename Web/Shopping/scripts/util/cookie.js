/**
* 对于cookie的操作，都是全局的。
*/

function setCookie(name, value) {
    var date = new Date();
    date.setMonth(date.getMonth() + 1);
    document.cookie = name + "=" + escape(value) + ";expires=" + date.toGMTString() + ";path=/;";
}

function getCookie(name) {
    var cookies = document.cookie.split("; ");
    for(var i = 0; i < cookies.length; ++ i) {
        var values = cookies[i].split("=");
        if(values[0] === name) {
            return unescape(values[1]);
        }
    }
    return "";
}

function deleteCookie(name) {
    var date = new Date(0);
    document.cookie = name + "= ;expires=" + date.toGMTString() + ";path=/;";
}

function deleteAllCookies() {
    var date = new Date(0);
    var cookies = document.cookie.split("; ");
    for(var i = 0; i < cookies.length; ++ i) {
        var values = cookies[i].split("=");
        if(values[0] !== "PHPSESSID") {
            deleteCookie(values[0]);
        }
    }
}

function printAllCookies() {
    document.write("<table border='1'><tr><td>" + document.cookie + "</td></tr></table>");
    document.write("<table border='1'>");
    document.write("<tr><th>Name</th><th>Value</th></tr>");
    var cookies = document.cookie.split(";");
    for(var i = 0; i < cookies.length; ++ i) {
        var values = cookies[i].split("=");
        document.writeln("<tr><td>" + values[0] + "</td><td>" + unescape(values[1]) + "</td></tr>");
    }
    document.write("</table>");
}