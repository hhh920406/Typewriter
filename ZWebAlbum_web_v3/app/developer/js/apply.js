/**
 * Judge and show if the symbol is valid.
 * @return boolean
 */
function judgeSymbol() {
    var symbol = document.getElementById("Text_Symbol").value;
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

function judgeExistSymbol() {
    var xmlhttp = getXMLHttp();
    var symbol = Text_Symbol.value;
    xmlhttp.onreadystatechange = function()
    {
        if(xmlhttp.readyState == 4 && xmlhttp.status == 200)
        {
            if(xmlhttp.responseText.length > 0)
            {
                setStatus("Status_Exist_Symbol", TYPE_ERROR, xmlhttp.responseText)
            }
            else
            {
                setStatus("Status_Exist_Symbol", TYPE_CORRECT, "");
            }
        }
    }
    xmlhttp.open("GET", "symbol_ajax.php?symbol=" + symbol);
    xmlhttp.send();
    setStatus("Status_Exist_Symbol", TYPE_WAITING, "检测中。。。");
}