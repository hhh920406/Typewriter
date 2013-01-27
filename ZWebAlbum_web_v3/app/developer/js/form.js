/**
 * Judge if the string contains only number, English characters and underscore.
 * @param value The string to be judged.
 * @return boolean
 */
function isSymbolValid(value) {
    if(value.length == 0) {
        return false;
    }
    for(var i = 0; i < value.length; ++ i) {
        if(value[i] < '0' || value[i] > '9') {
            if(value[i] < 'a' || value[i] > 'z') {
                if(value[i] < 'A' || value[i] > 'Z') {
                    if(value[i] != '_' || value[i] != '-') {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

/**
 * Judge if the string contains no space.
 * @param value The string to be judged.
 * @return boolean
 */
function isNameValid(value) {
    if(value.length == 0) {
        return false;
    }
    for(var i = 0; i < value.length; ++ i) {
        if(value[i] == ' ') {
            return false;
        }
    }
    return true;
}

var TYPE_NORMAL = 0;
var TYPE_CORRECT = 1;
var TYPE_ERROR = 2;
var TYPE_WAITING = 3;

/**
 * Show the status.
 * @param name The name of the div.
 * @param type The style type.
 * @param text The text to show.
 */
function setStatus(name, type, text) {
    var status = document.getElementById(name);
    status.innerHTML = "";
    switch(type) {
        case TYPE_NORMAL:
            status.setAttribute("class", "normalMessage");
            break;
        case TYPE_CORRECT:
            status.setAttribute("class", "correctMessage");
            status.innerHTML = "<img src = 'images/icon_correct.gif' align = 'top'></img>";
            break;
        case TYPE_ERROR:
            status.setAttribute("class", "errorMessage");
            status.innerHTML = "<img src = 'images/icon_error.gif' align = 'top'></img>";
            break;
        case TYPE_WAITING:
            status.setAttribute("class", "normalMessage");
            status.innerHTML = "<img src = 'images/icon_waiting.gif' align = 'top'></img>";
            break;
    }
    status.innerHTML += " " + text;
}

function setInputEnable(name, enable) {
    var input = document.getElementById(name);
    if(enable) {
        input.removeAttribute("disabled");
    } else {
        input.setAttribute("disabled", "disabled");
    }
}

/**
 * Judge and show if the name is valid.
 * @return boolean
 */
function judgeName() {
    var name = Text_Name.value;
    setStatus("Status_Name", TYPE_NORMAL, "");
    setInputEnable("Button_Name", false);
    if(isNameValid(name)) {
        setStatus("Status_Name", TYPE_CORRECT, "");
        setInputEnable("Button_Name", true);
        return true;
    } else {
        setStatus("Status_Name", TYPE_ERROR, "格式不合法");
        return false;
    }
}

/**
 * Judge and show if the name is exist.
 * @return boolean
 */
function judgeExistName() {
    var xmlhttp = getXMLHttp();
    var name = Text_Name.value;
    xmlhttp.onreadystatechange = function() {
        if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            if(xmlhttp.responseText.length > 0) {
                setStatus("Status_Exist_Name", TYPE_ERROR, xmlhttp.responseText)
            } else {
                setStatus("Status_Exist_Name", TYPE_CORRECT, "");
            }
        }
    }
    xmlhttp.open("GET", "name_ajax.php?name=" + name);
    xmlhttp.send();
    setStatus("Status_Exist_Name", TYPE_WAITING, "检测中。。。");
}

/**
 * Judge and show if the description is valid.
 * @return boolean
 */
function judgeDescription() {
    var description = TextArea_Description.value;
    var countString = "[" + description.length + "/240]";
    setStatus("Status_Description", TYPE_NORMAL, "");
    if(description.length < 240) {
        setStatus("Status_Description", TYPE_CORRECT, countString);
        return true;
    } else {
        setStatus("Status_Description", TYPE_ERROR, countString + "文本过长");
        return false;
    }
}