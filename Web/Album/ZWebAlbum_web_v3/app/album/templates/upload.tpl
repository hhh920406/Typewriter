<form action = {$postUrl} id = "Form_Upload" name = "Form_Upload" encType = "multipart/form-data"  method = "post" target = "Hidden_Frame">
    <input type = "hidden" id = "Hidden_Token" name = "token" value = {$token}></input>
    <input type = "hidden" id = "Hidden_Method" name = "method" value = "photo.insert"></input>
    <div class = "inlineBlock">
        <select id = "Select_Album" name = "album_id">
            {foreach item = album from = $albums}
            <option value = {$album->AlbumID}>{$album->Name}</option>
            {/foreach}
        </select>
    </div>
    <a href = {$url}&tab=new>新建相册</a>
    <div class = "uploadDiv">
        <input id = "File_Upload"
               name = "upload[]"
               type = "file"
               multiple = "true"
               label = "上传文件"
               accept = "image/gif,image/png,image/bmp"
               onchange = "Form_Upload.submit()">
        </input>
        <div class = "uploadTextDiv" onclick = "File_Upload.click()">
            上传照片
        </div>
    </div>
</form>
<hr/>
<div id = "Div_Status" class = "resultDiv"></div>
<iframe id = "Hidden_Frame" class = "display: none" name = "Hidden_Frame" onload = "showResult()">
</iframe>