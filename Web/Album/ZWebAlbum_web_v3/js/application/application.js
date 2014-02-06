function tuneHeight() 
{
    var iframe = document.getElementById("appFrame");
    var subWeb = document.frames ? document.frames["appFrame"].document : iframe.contentDocument;
    if(iframe != null && subWeb != null)
    {
        iframe.height = subWeb.body.scrollHeight;
    }
}