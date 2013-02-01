{if $photoNum == 0}
相册中没有图片
{else}
<script src = "js/ajax.js"></script>
<script src = "js/querystring.js"></script>
<script src = "js/photo_frame.js"></script>
<div class = "pagerDiv">
    <a id = "Link_Prev" href = {$pageURL}&photopos={$prevPos}>
        上一张
    </a>
    [{$photoPos + 1}/{$photoNum}]
    <a id = "Link_Next" href = {$pageURL}&photopos={$nextPos}>
        下一张
    </a>
    <div class = "operationDiv">
        <a href = # onclick = "deletePhoto()">删除</a>
    </div>
</div>
<div id = "Test_Div"></div>
<input type = "hidden" id = "Hidden_Album_ID" value = {$albumID}></input>
<input type = "hidden" id = "Hidden_Photo_ID" value = {$photo->PhotoID}></input>
<input type = "hidden" id = "Hidden_Indice" value = {$photo->Indice}></input>
<div class = "imageDiv">
    <img id = "Image_Image" src = {$photo->PhotoPath}></img>
</div>
<div class = "descriptionDiv">
    <input id = "Text_Description" type = "text" class = "descriptionInput" onblur = "updatePhoto()" value = {$photo->EditDescription}></input>
</div>
{/if}