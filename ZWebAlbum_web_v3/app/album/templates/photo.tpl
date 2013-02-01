<div class = "title">
    <a href = {$url}>全部相册</a>&gt;
    <a href = {$url}&albumid={$album->AlbumID}>{$album->Name}</a>&gt;
    浏览照片
    <hr/>
</div>
<div class = "imageDiv">
    <iframe id = "Frame_Image"
            scrolling = "no"
            class = "imageFrame"
            onLoad="tuneHeight()"
            src = {$frameURL} >
    </iframe>
</div>