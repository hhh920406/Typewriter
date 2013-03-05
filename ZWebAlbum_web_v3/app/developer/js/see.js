function appEdit(appID) {
    window.location.href = window.location.href + "&appid=" + appID;
}

function appDelete(appID) {
    showDialog("确定要删除应用吗？");
    Button_Dialog_Confirm.onclick = function() {
        xmlhttp = getXMLHttp();
        xmlhttp.onreadystatechange = function() {
            if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                var div = document.getElementById("Div_App_" + appID);
                if(div) {
                    div.parentNode.removeChild(div);
                }
            }
        }
        xmlhttp.open("GET", "delete_ajax.php?appid=" + appID);
        xmlhttp.send();
        hideDialog();
    };
}