document.onkeyup = function(event) {
    var keyCode =  event.keyCode ? event.keyCode : (event.which ? event.which : event.charCode);
    if(keyCode == 37) {
        Link_Prev.click();
    } else if(keyCode == 39) {
        Link_Next.click();
    } else if(keyCode == 13) {
        Text_Description.blur();
    }
}

function deletePhoto() {
    if(confirm("确实要删除吗?")) {
        var xmlhttp = getXMLHttp();
        xmlhttp.onreadystatechange = function() {
            if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                Test_Div.innerHTML = xmlhttp.responseText;
                var photoNum = getQueryString("photonum") - 1;
                var photoPos = getQueryString("photopos");
                if(photoPos >= photoNum) {
                    photoPos = 0;
                }
                window.location.href = window.location.pathname +
                    "?username=" + getQueryString("username") +
                    "&albumid=" + getQueryString("albumid") +
                    "&photonum=" + photoNum +
                    "&photopos=" + photoPos;
            }
        }
        xmlhttp.open("GET", "photo_delete_ajax.php?photoid=" + Hidden_Photo_ID.value);
        xmlhttp.send();
    }
}

function updatePhoto() {
    var xmlhttp = getXMLHttp();
    xmlhttp.open("GET", "photo_update_ajax.php" +
        "?photoid=" + Hidden_Photo_ID.value +
        "&albumid=" + Hidden_Album_ID.value +
        "&description=" + Text_Description.value +
        "&indice=" + Hidden_Indice.value);
    xmlhttp.send();
}

function updateCover() {
    var xmlhttp = getXMLHttp();
    xmlhttp.open("GET", "album_cover_ajax.php" +
        "?photoid=" + Hidden_Photo_ID.value +
        "&albumid=" + Hidden_Album_ID.value);
    xmlhttp.send();
}