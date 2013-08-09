    stopAll: function() {
        gSM._mainNode.disconnect();
		var gainNode = gSM._context.createGainNode();
        gSM._mainNode.connect(gSM._context.destination);
    },