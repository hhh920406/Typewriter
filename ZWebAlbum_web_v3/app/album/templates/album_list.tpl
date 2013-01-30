{foreach item = album from = $albums}
<div class = "albumDiv">
    <img width = 200px height = 150px src = {$album->PhotoPath}></img>
    {$album->Name}<br/>
</div>
{/foreach}