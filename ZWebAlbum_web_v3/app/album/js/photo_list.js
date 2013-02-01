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