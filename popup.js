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

function updateCheckbox() {
  chrome.storage.sync.get('comment', function(item) {
    if (item.comment) {
	  checkbox_comment.checked = true;
	} else {
	  checkbox_comment.checked = false;
	}
  });
  chrome.storage.sync.get('renpin', function(item) {
    if (item.renpin) {
	  checkbox_renpin.checked = true;
	} else {
	  checkbox_renpin.checked = false;
	}
  });
}

function setCheckboxComment() {
  chrome.storage.sync.set({'comment': checkbox_comment.checked});
}

function setCheckboxRenpin() {
  chrome.storage.sync.set({'renpin': checkbox_renpin.checked});
}

window.onload = function() {
  loadUserID();
  updateCheckbox();
  button_save.onclick = saveUserID;
  checkbox_comment.onclick = setCheckboxComment;
  checkbox_renpin.onclick = setCheckboxRenpin;
}