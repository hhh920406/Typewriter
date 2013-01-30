<div class = "title">
    <a href = {$url}>全部相册</a>&gt;
    {$album->Name}
    <hr/>
</div>
{foreach item = photo from = $photos}
<div class = "albumDiv">
    <a href = {$url}&albumid={$photoID->PhotoID}>
        <div class = "photoDiv">
            <img width = 200px height = 150px src = {$photo->PhotoPath}></img>
        </div>
    </a>
    <div class = "nameDiv">
        {$photo->Description}
    </div>
</div>
{/foreach}