var gCachedAssets = {};

function loadAssets(assetList, callbackFcn) {
    var count = 0;
    for (var i = 0; i < assetList.length; ++i) {
        var assetName = assetList[i];
        if (gCachedAssets[assetName] == null) {
            var img = new Image();
            img.onload = function () {
                if (++count >= assetList.length) {
                    callbackFcn();
                }
            };
            img.src = assetName;
            gCachedAssets[assetName] = img;
        } else {
            if (++count >= assetList.length) {
                callbackFcn();
            }
        }
    }
}