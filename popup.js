var ids = null;

function saveUserID() {
  var idText = area_id.value;
  ids = idText.split("\n");
  chrome.storage.sync.set({'ids': ids});
}

function loadUserID() {
  chrome.storage.sync.get('ids', function(item) {
    if (item.ids) {
      ids = item.ids;
	  area_id.value = ids.join("\n");
	}
  });
}

function updateStartButton() {
  chrome.storage.sync.get('start', function(item) {
    if (item.start) {
	  button_start.innerText = "运行中";
	  button_start.className = "running";
	} else {
	  button_start.innerText = "已停止";
	  button_start.className = "stop";
	}
  });
}

function toggleStart() {
  chrome.storage.sync.get('start', function(item) {
    if (item.start) {
	  chrome.storage.sync.set({'start': false});
	} else {
	  chrome.storage.sync.set({'start': true});
	}
    updateStartButton();
  });
}

window.onload = function() {
  loadUserID();
  button_save.onclick = saveUserID;
  button_start.onclick = toggleStart;
  updateStartButton();
}