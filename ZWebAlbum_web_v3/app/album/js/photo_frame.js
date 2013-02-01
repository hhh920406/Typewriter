document.onkeyup = function(event) {
    var keyCode =  event.keyCode ? event.keyCode : (event.which ? event.which : event.charCode);
    if(keyCode == 37) {
        Link_Prev.click();
    } else if(keyCode == 39) {
        Link_Next.click();
    }
}