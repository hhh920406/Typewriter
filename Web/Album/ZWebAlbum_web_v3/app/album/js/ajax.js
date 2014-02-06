/**
 * Get the object for ajax.
 */
function getXMLHttp() {
    if(window.XMLHttpRequest) {
        return new XMLHttpRequest();
    } else {
        return new ActiveXObject("Microsoft.XMLHTTP");
    }
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
