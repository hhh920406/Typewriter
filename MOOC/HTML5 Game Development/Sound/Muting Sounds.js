    togglemute: function() {
        if (gSM._mainNode.gain.value === 0) {
            gSM._mainNode.gain.value = 1;
        } else {
            gSM._mainNode.gain.value = 0;
        }
    },