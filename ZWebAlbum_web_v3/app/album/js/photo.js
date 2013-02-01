function tuneHeight() {
    var iframe = document.getElementById("Frame_Image");
    var subWeb = document.frames ? document.frames["Frame_Image"].document : iframe.contentDocument;
    if(iframe != null && subWeb != null) {
        iframe.height = subWeb.body.scrollHeight + 200;
    }
}

document.onkeyup = function(event) {
    Frame_Image.focus();
    var keyCode =  event.keyCode ? event.keyCode : (event.which ? event.which : event.charCode);
    var link = "";
    if(keyCode == 37) {
        link = "Link_Prev";
    } else if(keyCode == 39) {
        link = "Link_Next";
    }
    if(link != "") {
        var doc = document.getElementById("Frame_Image").document;
        if(doc == undefined) {
            document.getElementById("Frame_Image").contentWindow.document.getElementById(link).click();
        } else {
            document.frames["Frame_Image"].document.getElementById(link).click();
        }
    }
}
