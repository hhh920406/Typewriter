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

function showDialog(content) {
    dialogBox.style.display = "block";
    Dialog.innerHTML = content;
}

function hideDialog() {
    dialogBox.style.display = "none";
}
