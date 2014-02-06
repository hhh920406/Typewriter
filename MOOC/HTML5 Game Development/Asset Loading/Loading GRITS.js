var InitialLoadPhase = function(){
    loadAssets(inputScripts,function(){window.alert('Files loaded!');});
    window.alert('Files loaded!');
};

var inputScripts = [
    "/media/img/gamedev/robowalk/robowalk00.png"
];

loadAssets(inputScripts, function() {
    window.alert('Loaded');
});
