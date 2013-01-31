function upload() {
    for(var i = 0; i < File_Upload.files.length; ++ i) {
        var file = File_Upload.files[i];
        xmlhttp.onreadystatechange = function() {
            if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                if(xmlhttp.responseText.length == "0") {
                    //Error
                } else {
                    //Correct
                }
            }
        }
        xmlhttp.open("GET", "upload_ajax.php?albumid=" + Text_Name.value + "&photopath=" + file.path);
        xmlhttp.send();
    }
}
