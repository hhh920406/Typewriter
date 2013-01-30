{foreach item = album from = $albums}
<div class = "albumDiv">
    <a href = {$url}&albumid={$album->AlbumID}>
        <div class = "photoDiv">
            <img width = 200px height = 150px src = {$album->PhotoPath}></img>
        </div>
    </a>
    <div class = "nameDiv">
        {$album->Name}
    </div>
</div>
{/foreach}