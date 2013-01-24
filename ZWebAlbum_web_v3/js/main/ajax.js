/**
 * Get the object for ajax.
 */
function getXMLHttp()
{
    if(window.XMLHttpRequest)
    {
        return new XMLHttpRequest();
    }
    else
    {
        return new ActiveXObject("Microsoft.XMLHTTP");
    }
}

/**
 * Set the enabled property of input.
 * @param input The input.
 * @param value A boolean value.
 */
function setInputEnabled(input, value)
{
    if(value)
    {
        if(input.getAttribute("disabled"))
        {
            input.removeAttribute("disabled");
        }
    }
    else
    {
        input.setAttribute("disabled", "disabled");
    }
}

function clearDivText(divName)
{
    var div = document.getElementById(divName);
    div.innerHTML = "";
}

var TYPE_NULL = 0;
var TYPE_CORRECT = 1;
var TYPE_ERROR = 2;
var TYPE_WAITING = 3;

/**
 * Show text with correct status.
 * @param divName The name of the div.
 * @param type The status of the text， a integer const likes TYPE_?;
 * @param text The text string to show.
 */
function setDivText(divName, type, text)
{
    var div = document.getElementById(divName);
    switch(type)
    {
        case TYPE_CORRECT:
            div.setAttribute("class", "correctMessage");
            div.innerHTML = "<img src = '/images/icon_correct.gif' alt = 'Correct' align = 'top'></img>";
            break;
        case TYPE_ERROR:
            div.setAttribute("class", "errorMessage");
            div.innerHTML = "<img src = '/images/icon_error.gif' alt = 'Error' align = 'top'></img>";
            break;
        case TYPE_WAITING:
            div.setAttribute("class", "normalMessage");
            div.innerHTML = "<img src = '/images/icon_waiting.gif' alt = 'Waiting' align = 'top'></img>";
            break;
        default:
            div.setAttribute("class", "normalMessage");
            div.innerHTML = "";
            break;
    }
    div.innerHTML += "  " + text;
}
