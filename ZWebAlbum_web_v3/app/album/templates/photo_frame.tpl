<script src = "js/photo_frame.js"></script>
<div class = "pagerDiv">
    <a id = "Link_Prev" href = {$pageURL}&photopos={$prevPos}>
        上一张
    </a>
    [{$photoPos + 1}/{$photoNum}]
    <a id = "Link_Next" href = {$pageURL}&photopos={$nextPos}>
        下一张
    </a>
</div>
<div class = "imageDiv">
    <img id = "Image_Image" src = {$photo->PhotoPath}></img>
</div>
<div class = "descriptionDiv">
    {$photo->Description}
</div>