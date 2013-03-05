function addWaitingDiv(id, name) {
    Div_Status.innerHTML +=
        "<div id = 'Photo_" + id + "' class = 'photoDiv'>" +
        "   <div id = 'Name_" + id + "' class = 'nameDiv'>" + name + "</div>" +
        "   <div id = 'Status_" + id + "' class = 'statusDiv'>" + "上传中" + "</div>" +
        "</div>";
}

function setStatusDiv(id, text) {
    var status = document.getElementById("Status_" + id);
    status.innerHTML = text;
}

function setStatusCorrect(id) {
    setStatusDiv(id, "<div style = 'color: darkgreen'>上传成功</div>");
}

function setStatusError(id) {
    setStatusDiv(id, "<div style = 'color: red'>上传失败</div>");
}

function showResult() {
    var result = Hidden_Frame.document.body.innerHTML;
    if(result) {
        var xmlhttp = getXMLHttp();
        xmlhttp.onreadystatechange = function() {
            if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                Div_Status.innerHTML += xmlhttp.responseText;
            }
        }
        xmlhttp.open("POST", "upload_result_ajax.php");
        xmlhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
        xmlhttp.send("result=" + result);
    }
}
