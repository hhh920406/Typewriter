/**
 * Judge and show if the symbol is valid.
 * @return boolean
 */
function judgeSymbol() {
    var symbol = Text_Symbol.value;
    setStatus("Status_Symbol", TYPE_NORMAL, "");
    setInputEnable("Button_Symbol", false);
    if(isSymbolValid(symbol)) {
        setStatus("Status_Symbol", TYPE_CORRECT, "");
        setInputEnable("Button_Symbol", true);
        return true;
    } else {
        setStatus("Status_Symbol", TYPE_ERROR, "格式不合法");
        return false;
    }
}

/**
 * Judge and show if the symbol is exist.
 * @return boolean
 */
function judgeExistSymbol() {
    var xmlhttp = getXMLHttp();
    var symbol = Text_Symbol.value;
    xmlhttp.onreadystatechange = function() {
        if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            if(xmlhttp.responseText.length > 0) {
                setStatus("Status_Exist_Symbol", TYPE_ERROR, xmlhttp.responseText)
            } else {
                setStatus("Status_Exist_Symbol", TYPE_CORRECT, "");
            }
        }
    }
    xmlhttp.open("GET", "symbol_ajax.php?symbol=" + symbol);
    xmlhttp.send();
    setStatus("Status_Exist_Symbol", TYPE_WAITING, "检测中。。。");
}

function apply() {
    $flag = true;
    $flag &= judgeSymbol();
    $flag &= judgeName();
    $flag &= judgeDescription();
    if($flag) {
        var xmlhttp = getXMLHttp();
        xmlhttp.onreadystatechange = function() {
            if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                if(xmlhttp.responseText.length > 0) {
                    setStatus("Status_Apply", TYPE_ERROR, xmlhttp.responseText)
                } else {
                    setStatus("Status_Apply", TYPE_CORRECT, "");
                    window.location.href = window.location.pathname;
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
        xmlhttp.open("POST", "apply_ajax.php");
        xmlhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
        xmlhttp.send(
            "symbol=" + symbol + "&" +
            "name=" + name + "&" +
            "description=" + description + "&" +
            "type=" + type + "&" +
            "user_basic=" + user_basic);
        setStatus("Status_Apply", TYPE_WAITING, "提交中。。。");
    }
}