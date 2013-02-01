<div class = "title">
    <a href = {$url}>全部相册</a>&gt;
    {$album->Name}
    <hr/>
</div>
<div class = "infoDiv">
    <div class = "operationDiv">
        <a href = # onclick = "deleteAlbum()">删除相册</a>
    </div>
    <input id = "Text_Name" type = "text" class = "titleInput"  onblur = "updateAlbum()" value = {$album->EditName}></input>
    <input id = "Text_Description" type = "text" class = "descriptionInput"  onblur = "updateAlbum()" value = {$album->EditDescription}></input>
</div>
<div id = "Test_Div"></div>
<input type = "hidden" id = "Hidden_ID" value = {$album->AlbumID}></input>
<input type = "hidden" id = "Hidden_Type" value = {$album->Type}></input>
<input type = "hidden" id = "Hidden_Indice" value = {$album->Indice}></input>
<div class = "pagerDiv">
{include file = "pager.tpl"}
</div>
{$pageCount = 0}
{foreach item = photo from = $photos}
<div class = "albumDiv">
    <a href = {$url}&albumid={$album->AlbumID}&photopos={($page - 1) * $itemPerPage + $pageCount}>
        {$pageCount = $pageCount + 1}
        <div class = "photoDiv">
            <img width = 200px height = 150px src = {$photo->PhotoPath}></img>
        </div>
    </a>
    <div class = "nameDiv">
        {$photo->Description}
    </div>
</div>
{/foreach}
<div class = "pagerDiv">
{include file = "pager.tpl"}
</div>