var gCachedAssets = {};

function loadAssets(assetList, callbackFcn) {
    var loadBatch = {
        count: 0,
        total: assetList.length,
        cb: callbackFcn
    };
    for(var i = 0; i < assetList.length; i++) {
        if(gCachedAssets[assetList[i]] == null) {
            var assetType = getAssetTypeFromExtension(assetList[i]);
            if (assetType === 0) {
                var img = new Image();
                img.onload = function () {
                    onLoadedCallback(img, loadBatch);
                };
                img.src = assetList[i];
                gCachedAssets[assetList[i]] = img;
            } else if (assetType === 1) {
                var script = document.createElement('script');
                script.type = "text/javascript";
                script.onload = function (){
                    onLoadedCallback(script, loadBatch);
                };
                script.src = assetList[i];
                var head = document.getElementsByTagName("head")[0];
                head.appendChild(script);
                gCachedAssets[assetList[i]] = script;
            }
        } else {
            onLoadedCallback(gCachedAssets[assetList[i]], loadBatch);
        }
    }
}

function onLoadedCallback(asset, batch) {
    batch.count++;
    if(batch.count == batch.total) {
        batch.cb(asset);
    }
}

function getAssetTypeFromExtension(fname) {
    if(fname.indexOf('.jpg') != -1 || fname.indexOf('.jpeg') != -1 || fname.indexOf('.png') != -1 || fname.indexOf('.gif') != -1 || fname.indexOf('.wp') != -1) {
        return 0;
    }
    if(fname.indexOf('.js') != -1 || fname.indexOf('.json') != -1) {
        return 1;
    }
    return -1;
}

