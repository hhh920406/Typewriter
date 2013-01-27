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
    //
}