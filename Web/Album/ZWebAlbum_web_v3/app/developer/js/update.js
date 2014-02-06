function judgeExistName_Update() {
    setStatus("Status_Exist_Name", TYPE_NORMAL, "");
    if(Text_Name.value == Text_Origin_Name.value) {
        setStatus("Status_Exist_Name", TYPE_CORRECT, "");
        return true;
    } else {
        return judgeExistName();
    }
}


function update() {
    $flag = true;
    $flag &= judgeName();
    $flag &= judgeDescription();
    if($flag) {
        var xmlhttp = getXMLHttp();
        xmlhttp.onreadystatechange = function() {
            if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                if(xmlhttp.responseText.length > 0) {
                    setStatus("Status_Update", TYPE_ERROR, xmlhttp.responseText)
                } else {
                    setStatus("Status_Update", TYPE_CORRECT, "");
                    var username = getQueryStringByName("username");
                    window.location.href = window.location.pathname + "?username=" + username;
                }
            }
        }
        var symbol = Text_Symbol.value;
        var name = Text_Name.value;
        var description = TextArea_Description.value;
        var type = 0;
        switch(Select_Type.value) {
            case "Inside":
                type = 1;
                break;
            case "Outside":
                type = 2;
                break;
            case "Desktop":
                type = 3;
                break;
            case "Core":
                type = 4;
                break;
        }
        var user_basic = Checkbox_user_basic.checked;
        xmlhttp.open("POST", "update_ajax.php");
        xmlhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
        xmlhttp.send(
            "symbol=" + symbol + "&" +
            "name=" + name + "&" +
            "description=" + description + "&" +
            "type=" + type + "&" +
            "user_basic=" + user_basic);
        setStatus("Status_Update", TYPE_WAITING, "提交中。。。");
    }
}