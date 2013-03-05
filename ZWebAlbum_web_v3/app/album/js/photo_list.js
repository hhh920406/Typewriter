function deleteAlbum() {
    if(confirm("确实要删除吗?")) {
        var xmlhttp = getXMLHttp();
        xmlhttp.onreadystatechange = function() {
            if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                window.location.href = window.location.pathname +
                    "?username=" + getQueryString("username");
            }
        }
        xmlhttp.open("GET", "album_delete_ajax.php?albumid=" + Hidden_ID.value);
        xmlhttp.send();
    }
}

function updateAlbum() {
    var xmlhttp = getXMLHttp();
    xmlhttp.open("GET", "album_update_ajax.php" +
        "?albumid=" + Hidden_ID.value +
        "&name=" + Text_Name.value +
        "&description=" + Text_Description.value +
        "&type=" + Hidden_Type.value +
        "&indice=" + Hidden_Indice.value);
    xmlhttp.send();
}

document.onkeyup = function(event) {
    var keyCode =  event.keyCode ? event.keyCode : (event.which ? event.which : event.charCode);
    if(keyCode == 13) {
        updateAlbum();
    }
}