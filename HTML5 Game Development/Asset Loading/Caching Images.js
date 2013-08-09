var gCachedAssets = {};

function loadAsset(assetName, callbackFcn) {
    if (gCachedAssets[assetName]) {
        callbackFcn(gCachedAssets[assetName]);
        return;
    }
    var img = new Image();
    img.onload = function () {
        callbackFcn(img);
    };
    img.src = assetName;
    gCachedAssets[assetName] = img;
}

