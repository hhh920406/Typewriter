<div class = "inlineBlock">
    <select id = "Select_Album">
        {foreach item = album from = $albums}
        <option value = {$album->AlbumID}>{$album->Name}</option>
        {/foreach}
    </select>
</div>
<a href = {$url}&tab=new>新建相册</a>
<div class = "uploadDiv">
    <input id = "File_Upload"
           type = "file"
           multiple = "true"
           label = "上传文件"
           accept = "image/gif,image/png,image/bmp"
           onchange = "upload()">
    </input>
    <div class = "uploadTextDiv" onclick = "File_Upload.click()">
        上传照片
    </div>
</div>
<hr/>